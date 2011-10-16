//
//  array.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_array_h
#define T3nsors_array_h

#include <vector>
#include <ostream>
#include <initializer_list>

#define FOR(n,N) for ( unsigned int n=0; n<N; n++ )
#define FRO(n,i,N) for ( int n=i; n<N; n++ )
#define LOOP(N) for ( unsigned int __n=0; __n<N; __n++ )

namespace T3 {
    template <class T>
    class array : public std::vector<T> {
    public:
        array() : std::vector<T>() {}
//        array(std::initializer_list<T> init) : std::vector<T>(init) {}
        T& operator[](int i) {
            i = mod(i, (int)this->size());
            return this->at(i);
        }
        
        const T operator[](int i) const {
            i = (int)((i % this->size() + this->size()) % this->size());
            return this->at(i);
        }
        
#define BINARY(name,op) \
        array<T> name(const array<T>& other) { \
            array<T> added = *this; \
            for ( int i=0; i<this->size(); i++ ) \
                added[i] = added[i] op other[i]; \
            return added; \
        }
        BINARY(add,+);
        BINARY(subtract,-);
        BINARY(multiply,*);
        BINARY(divide,/);
        
        array<T>& increment(const array<T>& other) {
            FOR(i,this->size())
                (*this)[i] += other[i];
            return *this;
        }
        
        array<T> multiply(const double& a) {
            array<T> other = *this;
            for ( T& t : other )
                t *= a;
            return other;
        }
        
        array<T>* parent;
        
        static int mod(int a, int p) {
            return (p + a % p) % p;
        }
    };
}

template<class T>
std::ostream& operator<<(std::ostream& out, T3::array<T>& L) {
    for ( T& t : L )
        out << t << "\t";
    out << std::flush;
    return out;
}

#define _LC_PROTOTYPE(type) \
type _LC(double a, type* x, ...) { \
    type M = a * (*x); \
    va_list args; \
    va_start(args, x); \
    while ( (a = va_arg(args, double)) ) { \
        x = va_arg(args, type*); \
        M += a * (*x); \
    } \
    return M; \
}

template<class T>
T _LC(double a, T& M, va_list args) {
    T* x;
    while ( (a = va_arg(args, double)) ) {
        x = va_arg(args, T*);
        M += (*x) * a;
    }
    va_end(args);
    return M;
}

template<class T>
T _LC(double a, T* x, ...) {
    T M = (*x) * a;
    va_list args;
    va_start(args, x);
    return _LC<T>(a, M, args);
}

#define LC_SHORTCUT(type,...) _LC<type>(__VA_ARGS__, NULL);

#endif
