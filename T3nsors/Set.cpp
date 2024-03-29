//
//  Set.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Set.h"

T3::Set::Set(int N, ...) {
    va_list args;
    va_start(args, N);
    LOOP(N) push_back(Tensor(va_arg(args,int), this));
    va_end(args);
}

T3::Set LC(real a, T3::Set* x, ...) {
    T3::Set M = (*x) * a;
    va_list args;
    va_start(args, x);
    return _LC<T3::Set>(a, M, args);
}
