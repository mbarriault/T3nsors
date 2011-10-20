//
//  System.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "System.h"

T3::Partial T3::System::t(Partial::Cartesian(0, 10, 0., 1.));

void T3::System::Evolve() {
    PreEvolve();
    Set x1 = *this;
    Set dx1 = RHS(x1);
    if ( epsilon > 0 )
        dx1 += Dissipate(x1) * (-epsilon);
    Set x2 = LC(1., &x1, 0.5*t.d, &dx1, NULL);
    Set dx2 = RHS(x2);
    if ( epsilon > 0 )
        dx2 += Dissipate(x2) * (-epsilon);
    Set x3 = LC(1., &x1, 0.75*t.d, &dx2, NULL);
    Set dx3 = RHS(x3);
    if ( epsilon > 0 )
        dx3 += Dissipate(x3) * (-epsilon);
    
    Set dx = LC(2*t.d/9, &dx1, 3*t.d/9, &dx2, 4*t.d/9, &dx3, NULL);
    FOR(n,size()) at(n) += dx.at(n);
}

int T3::System::Run() {
    Initialize();
    while ( not Condition() ) {
        PreEvolve();
        Evolve();
        PostEvolve();
    }
    bool c = Condition();
    Cleanup();
    return c;
}

T3::System::operator Set() {
    Set s(0);
    for ( Stream& S : *this )
        s.push_back(S.back());
    return s;
}

T3::Set T3::System::Dissipate(const Set& U) {
    Set DU = U;
    FOR(n, DU.size()) FOR(j, DU.at(n).size()) {
        const Field& x = U.at(n).at(j);
        Field& dx = DU.at(n).at(j);
        FOR(o,dx.size()) dx[o] = 0.;
        FOR(a, Tensor::dim) {
            int dg = Tensor::N.Pr(a+1);
            int dc = Tensor::N.Pr(a);
            int G = Tensor::N.Pr()/dg;
            int C = Tensor::N[a];
            if ( C > 4 ) FOR(g,G) FOR(m,dc) {
                int i = g*dg + m;
                FRO(c,2,C-2)
                    dx[i+c*dc] += (x[i+(c-2)*dc]-4*x[i+(c-1)*dc]+6*x[i+c*dc]-4*x[i+(c+1)*dc]+x[i+(c+2)*dc])/16;
            }
        }
    }
    return DU;
}
