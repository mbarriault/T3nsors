//
//  field.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_field_h
#define T3nsors_field_h

#include "tuple.h"

namespace T3 {
    class field : public array<double> {
    public:
        tuple N;
        field(tuple);
        field(tuple,array<double>);
        double& operator()(int,...);
        double operator()(int,...) const;
        field operator*(const double& a) const {
            return field(N, ((array<double>*)(this))->multiply(a));
        }
        field& operator+=(const field& x) {
            increment((array<double>)x);
            return *this;
        }
#define field_BINARY(name, op) \
        field operator op (const field& x) { \
            return field(N, name(x)); \
        }
        field_BINARY(add, +);
        field_BINARY(subtract, -);
        field_BINARY(multiply, *);
        field_BINARY(divide, /);
        
        double L2(int);
    };
}

T3::field operator*(const double&, const T3::field&);
std::ostream& operator<<(std::ostream&, T3::field);
T3::field LC(double,T3::field*,...);

//_LC_PROTOTYPE(T3::field);

#endif
