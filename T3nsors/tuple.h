//
//  Tuple.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Tuple_h
#define T3nsors_Tuple_h

#include "Array.h"

namespace T3 {
    class Tuple : public Array<int> {
    public:
        Tuple(int, ...);
//        Tuple(std::initializer_list<int>);
        
        int Si(int=-1) const;
        int Pr(int=-1) const;
        Tuple map(int) const;
        int map(Tuple) const;
    };
}

#endif
