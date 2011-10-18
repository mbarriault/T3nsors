//
//  Stream.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Stream.h"

int T3::Stream::nt_min(3);
int T3::Stream::nt_max(5);
T3::Partial T3::Stream::t(Partial::Cartesian(0, 10, 0., 1.));

T3::Stream::Stream(T3::Tensor x, std::string id) : id(id) {
    x.t = 0;
    push_back(x);
}

T3::Stream::~Stream() {
    dump(true);
    clear();
}

T3::Stream& T3::Stream::dump(bool all) {
    unsigned long N = size() < nt_min ? 0 : size()-(1-all)*nt_min;
    LOOP(N) {
        // PRINT front() HERE
        pop_front();
    }
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
    double t0 = 0.;
    if ( size() > 0 )
        t0 = back().t + t.d;
    push_back(x);
    back().t = t0;
    return *this;
}

T3::Stream& T3::Stream::operator+=(const T3::Tensor& x) {
    *this &= (back() + x);
    return *this;
}
