//
//  Cartesian.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Cartesian_h
#define T3nsors_Cartesian_h

#include "Connection.h"
#include "Scalar.h"
#include "Vector.h"

namespace T3 {
    class Cartesian : public Connection {
    public:
        Cartesian(int,int,double,double,...);
        Vector operator()(Scalar);
        Scalar operator*(Vector);
        Vector operator&(Vector);
        double Int(Field,int);
    };
}

std::ostream& operator<<(std::ostream&, T3::Cartesian);

#endif
