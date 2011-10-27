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
        Axisymmetric(int,real,real);
        Vector operator()(const Scalar&) const;
        Scalar operator*(const Vector&) const;
        Vector operator&(const Vector&) const;
        Scalar Lap(const Scalar&) const;
        real Int(const Field&,int=2) const;
    };
}

std::ostream& operator<<(std::ostream&, T3::Axisymmetric);

#endif
