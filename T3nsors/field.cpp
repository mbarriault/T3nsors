//
//  Field.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Field.h"
#include <cmath>

T3::Field::Field(Tuple N, Object* parent) : N(N) {
    this->parent = parent;
    assign(N.Pr(), 0.);
}

T3::Field::Field(Tuple N, Array<double> L) : N(N), Array<double>(L) {
    
}

double& T3::Field::operator()(int a, ...) {
	va_list args;
	va_start(args,a);
	T3::Tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(args,int);
		o[i] = a;
	}
    va_end(args);
	return at(N.map(o));
}

double T3::Field::operator()(int a, ...) const {
	va_list vl;
	va_start(vl,a);
	T3::Tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(vl,int);
		o[i] = a;
	}
    va_end(vl);
	return at(N.map(o));
}

double& T3::Field::operator[](int o) {
    return (*(Array<double>*)(this))[o];
}

double T3::Field::operator[](int o) const {
    double val = (*(Array<double>*)(this))[o];
    if ( val != val ) {
        printf("Found a NaN!");
        parent->toss();
    }
    return val;
}

double T3::Field::L2(int p) {
    double l2x = 0.;
    FOR(o, size()) l2x += pow(at(o), p);
    l2x = pow(l2x/size(), 1./p);
    return l2x;
}

T3::Field operator-(T3::Field x) {
    for ( double& i : x )
        i *= -1;
    return x;
}

T3::Field operator*(const double& a, const T3::Field& x) {
    return x * a;
}

std::ostream& operator<<(std::ostream& out, T3::Field x) {
    if ( x.N.size() == 2 ) {
        FOR(i, x.N[0]) {
            FOR(j, x.N[1]) out << x(i,j) << "\t";
            out << "\n";
        }
    }
    else {
        out << *(T3::Array<double>*)(&x);
    }
    return out;
}

T3::Field LC(double a, T3::Field* x, ...) {
    T3::Field M = (*x) * a;
    va_list args;
    va_start(args, x);
    return _LC<T3::Field>(a, M, args);
}
