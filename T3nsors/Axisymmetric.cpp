//
//  Axisymmetric.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Axisymmetric.h"
#include <cmath>

T3::Axisymmetric::Axisymmetric(int n, real r0, real rn) {
    Tensor::dim = 3;
    Tensor::N = Tuple(3);
/*    Tensor::N[0] = n+1;
    push_back(Partial::Cartesian(0, n, r0, rn, this));
    push_back(Partial::Azimuth(1, back(), this));
    Tensor::N[1] = back().n;
    push_back(Partial::Polar(2, 1, this));
    Tensor::N[2] = 1;*/
    
    Partial Del = Partial::Azimuth(1, n, this);
    push_back(Partial::Cartesian(0, r0*Del.d, r0, rn, this));
    push_back(Del);
    push_back(Partial::Polar(2, 1, this));
    FOR(a,3) Tensor::N[a] = at(a).n;
}

T3::Vector T3::Axisymmetric::operator()(T3::Scalar x) {
    Vector dx;
    dx[0] = at(0)((Field)x);
    dx[1] = at(1)((Field)x);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dx[1](i,j,0) /= at(0)(i);
    dx.parent = x.parent;
    dx.fix();
    return dx;
}

T3::Scalar T3::Axisymmetric::operator*(T3::Vector x) {
    Scalar dx;
    dx += at(0)(x[0]);

    Field dxu = at(1)(x[1]);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dxu(i,j,0) /= at(0)(i);
    dx += dxu;
    
    Field xu = x[0];
    FOR(i,x.N[0]) FOR(j,x.N[1]) xu(i,j,0) /= at(0)(i) / 2.;
    dx += xu;
    
    xu = x[1];
    FOR(i,x.N[0]) FOR(j,x.N[1]) xu(i,j,0) /= at(0)(i) * sin( at(1)(j) ) / cos( at(1)(j) );
    dx += xu;
    
    dx.parent = x.parent;
    dx.fix();
    return dx;
}

T3::Vector T3::Axisymmetric::operator&(T3::Vector x) {
    Vector cx;
    
    Field dx = at(1)(x[2]);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dx(i,j,0) /= at(0)(i);
    cx[0] += dx;
    
    dx = at(2)(x[1]);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dx(i,j,0) /= -at(0)(i) * sin( at(1)(j) );
    cx[0] += dx;
    
    dx = at(2)(x[0]);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dx(i,j,0) /= at(0)(i) * sin( at(1)(j) );
    cx[1] += dx;
    
    dx = -at(0)(x[2]);
    cx[1] += dx;
    
    dx = at(0)(x[1]);
    cx[2] += dx;
    
    dx = at(1)(x[0]);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dx(i,j,0) /= -at(0)(i);
    cx[2] += dx;
    
    FOR(i,x.N[0]) FOR(j,x.N[1]) x[2](i,j,0) /= at(0)(i);
    cx[1] += -x[2];
    
    FOR(i,x.N[0]) FOR(j,x.N[1]) x[2](i,j,0) /= sin( at(1)(j) ) / cos( at(1)(j) );
    cx[0] += x[2];
    
    FOR(i,x.N[0]) FOR(j,x.N[1]) x[1](i,j,0) /= at(0)(i);
    cx[2] += x[1];
    
    cx.parent = x.parent;
    cx.fix();
    return cx;
}

T3::Scalar T3::Axisymmetric::Lap(T3::Scalar x) {
    Scalar dx;
    dx += at(0).two(x);
    
    Field dux = at(1).two(x);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dux(i,j,0) /= at(0)(i)*at(0)(i);
    dx += dux;
    
    dux = at(0)(x);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dux(i,j,0) /= at(0)(i)/2;
    dx += dux;
    
    dux = at(1)(x);
    FOR(i,x.N[0]) FOR(j,x.N[1]) dux(i,j,0) /= at(0)(i)*at(0)(i)*sin(at(1)(j))/cos(at(1)(j));
    dx += dux;
    
    dx.parent = parent;
    return dx;
}

real T3::Axisymmetric::Int(Field x, int p) {
    real l2x = 0.;
    FOR(i, at(0).n) FOR(j, at(1).n) l2x += pow(x(i,j,0), p) * pow(at(0)(i), 2.) * sin( at(1)(j) ) * at(0).d * at(1).d;
    l2x *= 2*M_PI;
    l2x /= 4./3*M_PI*pow(at(0).b-at(0).a, 3.);
    l2x = pow(l2x, 1./p);
    return l2x;
}

std::ostream& operator<<(std::ostream& out, T3::Axisymmetric x) {
    for ( T3::Partial& D : x )
        out << D << "\n";
    return out;
}

