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
        virtual Vector operator()(Scalar) {
            return Vector();
        }
        virtual Scalar operator*(Vector) {
            return Scalar();
        }
        virtual Vector operator&(Vector) {
            return Vector();
        }
        virtual double Int(Field,int) {
            return 0.;
        }
    };
}

#endif
