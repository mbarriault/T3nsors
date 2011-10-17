//
//  coordinates.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-16.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_coordinates_h
#define T3nsors_coordinates_h

#include "array.h"
#include "tuple.h"

namespace T3 {
    class coordinates : public array<double> {
    public:
        tuple N;
        coordinates();
        static coordinates Cartesian(int, int, double, double, ...);
        static coordinates Polar(int, int, double, double);
        static coordinates Axel_R(int, int, double, double);
        static coordinates Axel_A(int, int, double, double);
    };
}

#endif
