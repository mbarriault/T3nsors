//
//  Tensor.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Tensor.h"
#include <cmath>

T3::Tuple T3::Tensor::N(Tuple(1,1));
int T3::Tensor::dim(1);

T3::Tensor::Tensor(Object* parent) : rank(0) {
    this->parent = parent;
    assign(1, Field(N,this));
}

T3::Tensor::Tensor(int rank, Object* parent) : rank(rank) {
    this->parent = parent;
    assign(pow(dim,rank), Field(N,this));
}

T3::Tensor::Tensor(int rank, Array<Field> L) : rank(rank), Array<Field>(L) {
    
}

T3::Field& T3::Tensor::operator()(int a, ...) {
    va_list args;
    va_start(args, a);
    int o = mod(a, dim);
    FRO(i,1,rank) {
        a = mod(va_arg(args, int), dim);
        o += a*pow(dim, i);
    }
    return at(o);
}

const T3::Field T3::Tensor::operator()(int a, ...) const {
    va_list args;
    va_start(args, a);
    int o = mod(a, dim);
    FRO(i,1,rank) {
        a = mod(va_arg(args, int), dim);
        o += a*pow(dim, i);
    }
    return at(o);
}

T3::Tensor operator*(const double& a, const T3::Tensor& x) {
    return x * a;
}

T3::Tensor LC(double a, T3::Tensor* x, ...) {
    T3::Tensor M = (*x) * a;
    va_list args;
    va_start(args, x);
    return _LC<T3::Tensor>(a, M, args);
}

std::ostream& operator<<(std::ostream& out, T3::Tensor x) {
    for ( T3::Field& f : x )
        out << f << "\n";
    return out;
}