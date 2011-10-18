//
//  Partial.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Partial_h
#define T3nsors_Partial_h

#include "Object.h"
#include "Field.h"
#include <ostream>

namespace T3 {
    enum bounds {
        bounds_edge,
        bounds_bounce,
        bounds_periodic
    };
    
    class Partial : public Object {
    public:
        real a,b,d;
        int n;
        int p;
        bounds bnd;
        
        Partial();
        Partial(int,real,int,real,Object*parent=0); // a, n, d
        Partial(int,real,real,int,Object*parent=0); // a, b, n
        Partial(int,real,real,real,Object*parent=0); // a, d, b
        
        static Partial Cartesian(int,int,real,real,Object*parent=0);
        static Partial Cartesian(int,Partial,real,real,Object*parent=0);
        static Partial Azimuth(int,int,Object*parent=0);
        static Partial Azimuth(int,Partial,Object*parent=0);
        static Partial Polar(int,int,Object*parent=0);
        real operator()(int);
        
        Field operator()(Field);
    };
}

std::ostream& operator<<(std::ostream&, T3::Partial);

#endif
