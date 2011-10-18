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
        push_back(Stream(Scalar(), "u"));
        push_back(Stream(Scalar()));
        push_back(Stream(Vector()));
    }
    
    void Initialize() { SLINK
        double w = 2*M_PI / (Del[1].b-Del[0].a);
        
        FOR(i,Tensor::N[0]) FOR(j,Tensor::N[1]) {
            u(i,j) = cos(w*x(i));
            f(i,j) = -w*sin(w*x(i));
            g(0)(i,j) = w*sin(w*x(i));
        }
    }
    
    Set RHS(Set& x) { LINK
        Set dx = x; DLINK
        du = f;
        df = Del*g;
        dg = Del(f);
        std::cout << "Calculating!" << std::endl;
        return dx;
    }
    
    int Condition() {
        std::cout << "Condition!" << at(0).back().t << t(-1) << std::endl;
        if ( at(0).back().t > t(-1) )
            return 1;
        else
            return 0;
    }
};

int main (int argc, const char * argv[])
{
    Wave(10, 0.25, 10.).Run();
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

