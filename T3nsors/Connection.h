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
        virtual Vector operator()(Scalar) = 0;
        virtual Scalar operator*(Vector) = 0;
        virtual Vector operator&(Vector) = 0;
        virtual Scalar Lap(Scalar) = 0;
        virtual real Int(Field,int) = 0;
    };
}

#endif
