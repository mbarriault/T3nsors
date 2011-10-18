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
        double& operator()(int,...);
        double operator()(int,...) const;
        operator Field();
        Scalar& operator+=(Field x) {
            at(0).increment(x);
            return *this;
        }
    };
}

#endif
