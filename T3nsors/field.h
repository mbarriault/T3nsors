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
#include <H5Cpp.h>

namespace T3 {
    class Field : public Array<real> {
    public:
        Tuple N;
        Field(Tuple,Object*parent=NULL);
        Field(Tuple,Array<real>);
        void write(H5::Group&,std::string);
        real& operator()(int,...);
        real operator()(int,...) const;
        real& operator[](int);
        real operator[](int) const;
        Field operator*(const real& a) const {
            Field other = *this;
            other.expand(a);
            return other;
        }
        Field& operator*=(const real& a) {
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
        
        real L2(int);
    };
}

T3::Field operator-(T3::Field);
T3::Field operator*(const real&, const T3::Field&);
std::ostream& operator<<(std::ostream&, T3::Field);
T3::Field LC(real,T3::Field*,...);

//_LC_PROTOTYPE(T3::Field);

#endif
