//
//  Scalar.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Scalar_h
#define T3nsors_Scalar_h

#include "Tensor.h"

namespace T3 {
    class Scalar : public Tensor {
    public:
        Scalar(Object*parent=NULL);
        Scalar(Field);
        Scalar(Tensor);
        real& operator[](int);
        real operator[](int) const;
        real& operator()(int,...);
        real operator()(int,...) const;
        operator Field();
        operator const Field() const;
        Scalar& operator+=(const Field& x) {
            at(0).increment(x);
            return *this;
        }
    };
}

#endif
