//
//  field.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "field.h"
#include <cmath>

T3::field::field(tuple N) : N(N) {
    assign(N.Pr(), 0.);
}

T3::field::field(tuple N, array<double> L) : N(N), array<double>(L) {
    
}

double& T3::field::operator()(int a, ...) {
	va_list vl;
	va_start(vl,a);
	T3::tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(vl,int);
		o[i] = a;
	}
    va_end(vl);
	return at(N.map(o));
}

double T3::field::operator()(int a, ...) const {
	va_list vl;
	va_start(vl,a);
	T3::tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(vl,int);
		o[i] = a;
	}
    va_end(vl);
	return at(N.map(o));
}

double T3::field::L2(int p) {
    double l2x = 0.;
    FOR(o, size()) l2x += pow(at(o), p);
    l2x = pow(l2x/size(), 1./p);
    return l2x;
}

T3::field operator*(const double& a, const T3::field& x) {
    return x * a;
}

std::ostream& operator<<(std::ostream& out, T3::field x) {
    if ( x.N.size() == 2 ) {
        FOR(i, x.N[0]) {
            FOR(j, x.N[1]) out << x(i,j) << "\t";
            out << "\n";
        }
    }
    else {
        out << *(T3::array<double>*)(&x);
    }
    return out;
}

T3::field LC(double a, T3::field* x, ...) {
    T3::field M = (*x) * a;
    va_list args;
    va_start(args, x);
    return _LC<T3::field>(a, M, args);
}
