//
//  Set.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Set_h
#define T3nsors_Set_h

#include "Tensor.h"
#include <iostream>

namespace T3 {
    class Set : public Array<Tensor> {
    public:
        Set(int,...);
        Set operator*(const real& a) const {
            Set other = *this;
            other.expand(a);
            return other;
        }
        Set& operator+=(const Set& x) {
            increment(x);
            return *this;
        }
    };
}

T3::Set LC(real,T3::Set*,...);

#endif
