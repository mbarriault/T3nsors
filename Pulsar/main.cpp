//
//  main.cpp
//  Pulsar
//
//  Created by Michael Barriault on 11-10-19.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#define SLINK \
Scalar& Psi = (Scalar&)at(0).back(); \
Vector& E = (Vector&)at(1).back(); \
Vector& B = (Vector&)at(2).back();
#define LINK \
Scalar& Psi = (Scalar&)x.at(0); \
Vector& E = (Vector&)x.at(1); \
Vector& B = (Vector&)x.at(2);
#define DLINK \
Scalar& dPsi = (Scalar&)dx.at(0); \
Vector& dE = (Vector&)dx.at(1); \
Vector& dB = (Vector&)dx.at(2);
#define D2LINK \
Scalar& dPsi2 = (Scalar&)dx2.at(0); \
Vector& dE2 = (Vector&)dx2.at(1); \
Vector& dB2 = (Vector&)dx2.at(2);

#include <T3nsors/T3nsors.h>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace T3;

Params PulsarParams(real, real, real, real, real, real, real);

class Pulsar : public System {
public:
    Axisymmetric Nabla;
    Partial& r;
    Partial& theta;
    Params P;
    real c;
    int n;
    timeval before;
    
    Stream rho, J;
    Stream EB, divB;
    Stream S;
    
    Pulsar(int n, real s, int rot, std::string iid, Params P) : P(P), Nabla(Axisymmetric(n, P["Rs"]/P["Omega"], P["RLC"]/P["Omega"])), r(Nabla[0]) , theta(Nabla[1]) {
        Del = &Nabla;
        real T = rot*2*M_PI/P["Omega"];
        t = Partial(0, 0., s*Nabla[0].d, T, this);
        //Stream::Del = &Del;
        id = mkdir(iid + timecoord());
        epsilon = 0.5/Nabla[0].d;
        c = P["alpha"]/(t(-1) * P["mu"]*P["mu"]/pow(r(0),6.) * (1 + pow(P["Omega"]*r(0), 2.) ) );
        push_back(Stream(Scalar(), "Psi", this));
        push_back(Stream(Vector(), "E", this));
        push_back(Stream(Vector(), "B", this));
        
        std::ofstream info((id + "/info.txt").c_str(), std::ios::out);
        info << id << std::endl;
        info << Tensor::N << std::endl;
        info << t << std::endl;
        info << *Del << std::endl;
        info << P << std::endl;
    }
    
    void Initialize() { SLINK
        Set x = Source(*this, Tensor::N[0]);
        
        Psi = x[0];
        E = x[1];
        B = x[2];
        
        rho = Stream(CalcRho(*this), "rho", this);
        J = Stream(CalcJ(*this), "J", this);
        EB = Stream(CalcEB(*this), "EB", this);
        divB = Stream(CalcDivB(*this), "divB", this);
        S = Stream(CalcS(*this), "S", this);
        
        n = 0;
    }
    
    Set Source(Set x, int in=1) { LINK
        PFRO(i,0,in) FOR(j,Tensor::N[1]) FOR(k,Tensor::N[2]) {
            Psi(i,j,k) = 0.;
            B(0)(i,j,k) = 2*P["mu"]*cos(theta(j)) / pow(r(i),3.);
            B(1)(i,j,k) = P["mu"]*sin(theta(j)) / pow(r(i),3.);
            B(2)(i,j,k) = 0.;
            E(0)(i,j,k) = P["Omega"]*P["mu"]*pow(sin(theta(j)),2.) / pow(r(i),2.);
            E(1)(i,j,k) = -P["Omega"]*P["mu"]*sin(2*theta(j)) / pow(r(i),2.);
            E(2)(i,j,k) = 0.;
        }
        if ( P["zeta"] > 0 ) {
            Vector E_B = E|B;
            E = LC(1., &E, -P["zeta"], &E_B, NULL);
//            E = E - E|B;
            // Counter - count number of times above "threshold value"
        }
        Scalar B2 = B*B;
        Scalar E2 = E*E;
        Scalar V = B2-E2;
        FOR(o,Tensor::N.Pr()) if ( V[o] < 0 ) FOR(a,3) E(a)[o] *= 0.99*sqrt(B2[o]/E2[o]);
        return x;
    }
    
    Scalar CalcRho(Set x) { LINK
        Scalar rho = Nabla*E;
        FOR(o,Tensor::N.Pr()) rho[o] /= 4*M_PI;
        return rho;
    }
    
    Vector CalcJ(Set x) { LINK
        Scalar rho = CalcRho(x);
        Vector S = CalcS(x);
        Scalar B2 = B*B;
        Vector J;
        FOR(a,3) FOR(o,Tensor::N.Pr()) J(a)[o] = 4*M_PI*rho[o]/(B2[o]+1e-12)*S(a)[o];
        return J;
    }
    
    Vector CalcS(Set x) { LINK
        Vector S = (E&B);
        FOR(a,3) FOR(o,Tensor::N.Pr()) S(a)[o] /= 4*M_PI;
        return S;
    }
    
    Scalar CalcEB(Set x) { LINK
        return E*B;
    }
    
    Scalar CalcDivB(Set x) { LINK
        return Nabla*B;
    }
    
    Set RHS(Set& x) { LINK
        x = Source(x);
        Set dx = x; DLINK
        Scalar divB = CalcDivB(x);
        Vector J = CalcJ(x);
        Vector curlB = (Nabla&B);
        Vector curlE = (Nabla&E);
        Vector gradPsi = Nabla(Psi);
        
        Vector F1;
        Vector F2;
        if ( c > 0 ) {
            Scalar EB = CalcEB(x);
            FOR(a,3) PFOR(o, Tensor::N.Pr() ) {
                F1(a)[o] = fabs(EB[o]) * E(a)[o] + EB[o] * B(a)[o];
                F2(a)[o] = fabs(EB[o]) * B(a)[o] + EB[o] * E(a)[o];
            }
        }
        
        dPsi = LC(-P["k"], &Psi, 1., &divB, NULL);
        dE = LC(1., &curlB, -4*M_PI, &J, -c, &F1, NULL);
        dB = LC(-1., &curlE, 1., &gradPsi, -c, &F2, NULL);
        
        Set dx2 = dx; D2LINK
        /*PFOR(j,Tensor::N[1]) FOR(k,Tensor::N[2]) {
            dPsi2(0,j,k) = 0.5*( dPsi(0,j,k) + dB(0)(0,j,k) );
            dE2(1)(0,j,k) = 0.5*( dE(1)(0,j,k) - dB(2)(0,j,k) );
            dE2(2)(0,j,k) = 0.5*( dE(2)(0,j,k) + dB(1)(0,j,k) );
            dB2(0)(0,j,k) = 0.5*( dB(0)(0,j,k) + dPsi(0,j,k) );
            dB2(1)(0,j,k) = 0.5*( dB(1)(0,j,k) + dE(2)(0,j,k) );
            dB2(2)(0,j,k) = 0.5*( dB(2)(0,j,k) - dE(1)(0,j,k) );
        }*/
        PFOR(j,Tensor::N[1]) FOR(k,Tensor::N[2]) {
            dPsi2(-1,j,k) = 0.5*( dPsi(-1,j,k) - dB(0)(-1,j,k) );
            dE2(1)(-1,j,k) = 0.5*( dE(1)(-1,j,k) + dB(2)(-1,j,k) );
            dE2(2)(-1,j,k) = 0.5*( dE(2)(-1,j,k) - dB(1)(-1,j,k) );
            dB2(0)(-1,j,k) = 0.5*( dB(0)(-1,j,k) - dPsi(-1,j,k) );
            dB2(1)(-1,j,k) = 0.5*( dB(1)(-1,j,k) - dE(2)(-1,j,k) );
            dB2(2)(-1,j,k) = 0.5*( dB(2)(-1,j,k) + dE(1)(-1,j,k) );
        }
        
        return dx2;
    }
    
    void PreEvolve() {
        before = gettime();
    }
    
    void PostEvolve() { SLINK
        Set x = Source(*this);
        E = x[1];
        B = x[2];
        rho &= CalcRho(*this);
        J &= CalcJ(*this);
        EB &= CalcEB(*this);
        S &= CalcS(*this);
        divB &= CalcDivB(*this);
        
        std::cout << "Time remaining: " << timerem(before, t.n-n) << "\r" << std::flush;
        n++;
    }
    
    int Condition() {
        if ( at(0).back().t > t(-1) )
            return 1;
        else
            return 0;
    }
    
    void Cleanup() {
        clear();
        rho.dump(true);
        J.dump(true);
        EB.dump(true);
        S.dump(true);
        divB.dump(true);
    }
};

Params PulsarParams(real Rs, real RLC, real k, real mu, real Omega, real alpha, real zeta) {
    Params P;
    P["Rs"] = Rs;
    P["RLC"] = RLC;
    P["k"] = k;
    P["mu"] = mu;
    P["Omega"] = Omega;
    P["alpha"] = alpha;
    P["zeta"] = zeta;
    return P;
}

int main (int argc, const char * argv[]) {
	if ( argc > 1 ) {
		int w = atoi(argv[1]);
		real Omega = 0.125*w;
        Pulsar(18, 0.25, 20, "pulsar-static", PulsarParams(0.2, 4., 1., 1., Omega, 0., 1.)).Run();
	}
	else {
        for ( real Omega = 0.25; Omega <= 0.75; Omega += 0.125 )
            Pulsar(18, 0.25, 20, "pulsar-static", PulsarParams(0.2, 4., 1., 1., Omega, 0., 1.)).Run();
    }
    return 0;
}

