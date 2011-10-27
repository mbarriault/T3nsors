//
//  Array.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Array_h
#define T3nsors_Array_h

#include <vector>
#include <ostream>
#include <cstdarg>
//#include <initializer_list>
#include "Object.h"

namespace T3 {
    template <class T>
    class Array : public std::vector<T>, public Object {
    public:
        Array(Object* parent=0) : std::vector<T>() , Object(parent) {}
//        Array(std::initializer_list<T> init) : std::Vector<T>(init) {}
        T& operator[](int i) {
            return this->at( mod(i, (int)this->size()) );
        }
        
        const T operator[](int i) const {
            return this->at( mod(i, (int)this->size()) );
        }
        
#define BINARY(name,op) \
        Array<T> name(const Array<T>& other) { \
            Array<T> added = *this; \
            _Pragma("omp parallel for") \
            for ( int i=0; i<this->size(); i++ ) \
                added[i] = added[i] op other[i]; \
            return added; \
        }
        BINARY(add,+);
        BINARY(subtract,-);
        
        Array<T>& increment(const Array<T>& other) {
            PFOR(i,this->size())
                (*this)[i] += other[i];
            return *this;
        }
        
        Array<T>& expand(const real& a) {
            for ( T& t : *this )
                t *= a;
            return *this;
        }
    };
}

template<class T>
std::ostream& operator<<(std::ostream& out, T3::Array<T>& L) {
    for ( T& t : L )
        out << t << "\t";
    out << std::flush;
    return out;
}

template<class T>
T _LC(real a, T& M, va_list args) {
    T* x;
    while ( (a = va_arg(args, real)) and (x = va_arg(args, T*)) ) {
        M += (*x) * a;
    }
    va_end(args);
    return M;
}

template<class T>
T _LC(real a, T* x, ...) {
    T M = (*x) * a;
    va_list args;
    va_start(args, x);
    return _LC<T>(a, M, args);
}

#endif
