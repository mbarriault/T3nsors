//
//  Axisymmetric.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Axisymmetric_h
#define T3nsors_Axisymmetric_h

#include "Connection.h"

namespace T3 {
    class Axisymmetric : public Connection {
    public:
        Axisymmetric(int,double,double);
        Vector operator()(Scalar);
        Scalar operator*(Vector);
        Vector operator&(Vector);
        double Int(Field,int=2);
    };
}

std::ostream& operator<<(std::ostream& out, T3::Axisymmetric x) {
    for ( T3::Partial& D : x )
        out << D << "\n";
    return out;
}

#endif
