//
//  Tensor.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Tensor_h
#define T3nsors_Tensor_h

#include "Field.h"
#include "Partial.h"
#include <H5Cpp.h>

namespace T3 {
    class Tensor : public Array<Field> {
    public:
        static Tuple N;
        static int dim;
        int rank;
        real t;
        
        Tensor(Object*parent=0);
        Tensor(int,Object*parent=0);
        Tensor(int,Array<Field>);
        Field& operator()(int,...);
        const Field operator()(int,...) const;
        void write(H5::Group&, Partial);
        
        Tensor operator*(const real& a) const {
            Tensor other = *this;
            other.expand(a);
            return other;
        }
        Tensor& operator*=(const real& a) {
            expand(a);
            return *this;
        }
        Tensor& operator+=(const Tensor& x) {
            increment(x);
            return *this;
        }
#define Tensor_BINARY(name, op) \
        Tensor operator op (const Tensor& x) { \
            return Tensor(rank, name(x)); \
        }
        Tensor_BINARY(add, +);
        Tensor_BINARY(subtract, -);
        void fix() {
            FOR(i,size())
                at(i).parent = this;
//            for  ( Field& F : *this )
//                F.parent = this;
        }
    };
}

T3::Tensor operator*(const real&, const T3::Tensor&);
T3::Tensor LC(real,T3::Tensor*,...);
std::ostream& operator<<(std::ostream&,T3::Tensor);

#endif
