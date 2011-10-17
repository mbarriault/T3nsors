//
//  Scalar.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Scalar.h"

T3::Scalar::Scalar() : Tensor(0,this) {
}

T3::Scalar::Scalar(Field x) : Tensor(0,this) {
    at(0) = x;
    at(0).parent = this;
}

T3::Scalar::Scalar(Tensor x) : Tensor(x) {
    
}

double& T3::Scalar::operator()(int a, ...) {
	va_list args;
	va_start(args,a);
	T3::Tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(args,int);
		o[i] = a;
	}
    va_end(args);
	return at(0).at(N.map(o));
}

double T3::Scalar::operator()(int a, ...) const {
	va_list vl;
	va_start(vl,a);
	T3::Tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(vl,int);
		o[i] = a;
	}
    va_end(vl);
	return at(0).at(N.map(o));
}

T3::Scalar::operator Field() {
    return at(0);
}
