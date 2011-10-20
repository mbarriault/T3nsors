//
//  Vector.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Vector_h
#define T3nsors_Vector_h

#include "Tensor.h"
#include "Scalar.h"

namespace T3 {
    class Vector : public Tensor {
    public:
        Vector();
        Vector(Tensor);
        Scalar operator*(const Vector&) const;
        Vector operator&(const Vector&) const;
        Vector operator|(const Vector&) const;
    };
}

#endif
