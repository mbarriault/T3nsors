//
//  Vector.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Vector.h"

T3::Vector::Vector() : Tensor(1, this) {
    
}

T3::Vector::Vector(Tensor x) : Tensor(x) {
    
}

T3::Scalar T3::Vector::operator*(const Vector& v) const {
    const Vector& u = *this;
    Scalar uv;
    FOR(i,Vector::dim) FOR(o,u.N.Pr())
        uv[0][o] += u[i][o]*v[i][o];
    return uv;
}

T3::Vector T3::Vector::operator&(const Vector& v) const {
    const Vector& u = *this;
    Vector uv;
    int d = Vector::dim;
    int N = u.N.Pr();
    FOR(i,d) FOR(o,N) {
        uv[i][o] = u[mod(i+1,d)][o]*v[mod(i+2,d)][o] - u[mod(i+2,d)][o]*v[mod(i+1,d)][o];
    }
    return uv;
}
