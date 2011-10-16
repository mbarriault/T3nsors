//
//  tuple.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_tuple_h
#define T3nsors_tuple_h

#include "array.h"

namespace T3 {
    class tuple : public array<int> {
    public:
        tuple(int, ...);
//        tuple(std::initializer_list<int>);
        
        int Si(int=-1) const;
        int Pr(int=-1) const;
        tuple map(int) const;
        int map(tuple) const;
    };
}

#endif
