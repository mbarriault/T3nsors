//
//  Stream.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Stream.h"
#include "System.h"
#include <iostream>

int T3::Stream::nt_min(3);
int T3::Stream::nt_max(5);
T3::Partial T3::Stream::t(Partial::Cartesian(0, 10, 0., 1.));
T3::Connection* T3::Stream::Del(NULL);

T3::Stream::Stream(T3::Tensor x, std::string id, Object* parent) {
    this->parent = parent;
    this->id = id;
    x.t = 0;
    x.parent = this;
    push_back(x);
    H5::H5File* file = new H5::H5File((parent->id + "/" + id + ".hdf").c_str(), H5F_ACC_TRUNC);
    
    file->createGroup("/coords");
    for ( Partial& D : *Del )
        D.write(file);
    file->createGroup("/data");
    delete file;
}

T3::Stream::~Stream() {
    dump(true);
    clear();
}

T3::Stream& T3::Stream::dump(bool all) {    H5::H5File* file;
    file = new H5::H5File((parent->id + "/" + id + ".hdf").c_str(), H5F_ACC_RDWR);
    unsigned long N = size() < nt_min ? 0 : size()-(1-all)*nt_min;
    LOOP(N) {
        front().write(file);
        pop_front();
    }
    delete file;
    return *this;
}

T3::Tensor& T3::Stream::operator()(int i) {
    i = mod(i, (int)size());
    return at(i);
}

T3::Tensor T3::Stream::operator()(int i) const {
    i = mod(i, (int)size());
    return at(i);
}

T3::Stream& T3::Stream::operator&=(const T3::Tensor& x) {
    if ( size() > nt_max ) dump();
    real t0 = 0.;
    if ( size() > 0 )
        t0 = back().t;
    push_back(x);
    back().t = t0 + t.d;
    back().parent = this;
    return *this;
}

T3::Stream& T3::Stream::operator+=(const T3::Tensor& x) {
    (*this) &= (back() + x);
    return *this;
}

