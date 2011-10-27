//
//  Connection.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Connection_h
#define T3nsors_Connection_h

#include "Array.h"
#include "Partial.h"
#include "Scalar.h"
#include "Vector.h"

namespace T3 {
    class Connection : public Array<Partial> {
    public:
        virtual Vector operator()(const Scalar&) const = 0;
        virtual Scalar operator*(const Vector&) const = 0;
        virtual Vector operator&(const Vector&) const = 0;
        virtual Scalar Lap(const Scalar&) const = 0;
        virtual real Int(const Field&,int) const = 0;
    };
}

#endif
