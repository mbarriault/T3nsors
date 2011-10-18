//
//  Field.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Field_h
#define T3nsors_Field_h

#include "Tuple.h"

namespace T3 {
    class Field : public Array<double> {
    public:
        Tuple N;
        Field(Tuple,Object*parent=NULL);
        Field(Tuple,Array<double>);
        double& operator()(int,...);
        double operator()(int,...) const;
        double& operator[](int);
        double operator[](int) const;
        Field operator*(const double& a) const {
            Field other = *this;
            other.expand(a);
            return other;
        }
        Field& operator*=(const double& a) {
            expand(a);
            return *this;
        }
        Field& operator+=(const Field& x) {
            increment(x);
            return *this;
        }
#define Field_BINARY(name, op) \
        Field operator op (const Field& x) { \
            return Field(N, name(x)); \
        }
        Field_BINARY(add, +);
        Field_BINARY(subtract, -);
        
        double L2(int);
    };
}

T3::Field operator-(T3::Field);
T3::Field operator*(const double&, const T3::Field&);
std::ostream& operator<<(std::ostream&, T3::Field);
T3::Field LC(double,T3::Field*,...);

//_LC_PROTOTYPE(T3::Field);

#endif
