//
//  Cartesian.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Cartesian.h"
#include <cmath>

T3::Cartesian::Cartesian(int d, int n, real x0, real xn, ...) {
    Tensor::dim = d;
    Tensor::N = Tuple(d);
    push_back(Partial::Cartesian(0, n, x0, xn, this));
    Tensor::N[0] = back().n;
    va_list args;
    va_start(args, xn);
    FRO(i,1,d) {
        x0 = va_arg(args, real);
        xn = va_arg(args, real);
        push_back(Partial::Cartesian(i, at(0), x0, xn, this));
        Tensor::N[i] = back().n;
    }
    va_end(args);
}

T3::Vector T3::Cartesian::operator()(T3::Scalar x) {
    Vector dx;
    FOR(i, Tensor::dim) {
        dx[i] = at(i)((Field)x);
    }
    dx.parent = x.parent;
    dx.fix();
    return dx;
}

T3::Scalar T3::Cartesian::operator*(T3::Vector x) {
    Scalar dx;
    FOR(i, Tensor::dim) {
        dx += at(i)(x[i]);
    }
    dx.parent = x.parent;
    dx.fix();
    return dx;
}

T3::Vector T3::Cartesian::operator&(T3::Vector x) {
    Vector dx;
    FOR(i, Tensor::dim) {
        dx[i] = at(mod(i+1,Tensor::dim))(x[i+2]) - at(mod(i+2,Tensor::dim))(x[i+1]);
    }
    dx.parent = x.parent;
    dx.fix();
    return dx;
}

T3::Scalar T3::Cartesian::Lap(T3::Scalar x) {
    Scalar dx;
    FOR(i, Tensor::dim)
        dx += at(i).two(x);
    dx.parent = x.parent;
    return dx;
}

real T3::Cartesian::Int(Field x, int p) {
    real l2x = 0.;
    FOR(o, size()) l2x += pow(x[o], p);
    l2x = pow(l2x/size(), 1./p);
    return l2x;
}

std::ostream& operator<<(std::ostream& out, T3::Cartesian x) {
    for ( T3::Partial& D : x )
        out << D << "\n";
    return out;
}

