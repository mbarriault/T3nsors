//
//  main.cpp
//  WaveTest
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#define SLINK \
Scalar& u = (Scalar&)at(0).back(); \
Scalar& f = (Scalar&)at(1).back(); \
Vector& g = (Vector&)at(2).back();
#define LINK \
Scalar& u = (Scalar&)x.at(0); \
Scalar& f = (Scalar&)x.at(1); \
Vector& g = (Vector&)x.at(2);
#define DLINK \
Scalar& du = (Scalar&)dx.at(0); \
Scalar& df = (Scalar&)dx.at(1); \
Vector& dg = (Vector&)dx.at(2);
#define D2LINK \
Scalar& du2 = (Scalar&)dx2.at(0); \
Scalar& df2 = (Scalar&)dx2.at(1); \
Vector& dg2 = (Vector&)dx2.at(2);

#include <T3nsors/T3nsors.h>
#include <iostream>
#include <cmath>
using namespace T3;

class Wave : public System {
public:
    Cartesian Del;
    Partial& x;
    Partial& y;
    Wave(int n, double s, double T) : Del(2, n, -1., 1., -1., 1.) , x(Del[0]) , y(Del[1]) {
        System::t = Partial(0, 0., s*Del[0].d, T, this);
        Stream::t = System::t;
        epsilon = 0.5;
        push_back(Stream(Scalar(), "u", this));
        push_back(Stream(Scalar(), this));
        push_back(Stream(Vector(), this));
    }
    
    void Initialize() { SLINK
        double w = 2*M_PI / (Del[1].b-Del[0].a);
        
        FOR(i,Tensor::N[0]) FOR(j,Tensor::N[1]) {
            u(i,j) = cos(w*x(i));
            f(i,j) = -w*sin(w*x(i));
            g(0)(i,j) = w*sin(w*x(i));
        }
        
        std::cout << u << std::endl;
    }
    
    Set RHS(Set& x) { LINK
        Set dx = x; DLINK
        du = f;
        df = Del*g;
        dg = Del(f);
        
        Set dx2 = dx; D2LINK
        FOR(j,Tensor::N[1]) {
            df2(0,j) = 0.5*(df(0,j)+dg(0)(0,j));
            dg2(0)(0,j) = 0.5*(dg(0)(0,j)+df(0,j));
            df2(-1,j) = 0.5*(df(-1,j)-dg(0)(-1,j));
            dg2(0)(-1,j) = 0.5*(dg(0)(-1,j)-df(-1,j));
        }
        
        return dx2;
    }
    
    int Condition() {
        if ( at(0).back().t > t(-1) )
            return 1;
        else
            return 0;
    }
    
    void Cleanup() { SLINK
        std::cout << u << std::endl;
    }
};

int main (int argc, const char * argv[])
{
    Wave(10, 0.25, 10.).Run();
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

