//
//  Stream.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Stream_h
#define T3nsors_Stream_h

#include "Tensor.h"
#include "Partial.h"
#include <deque>
#include <string>

namespace T3 {
    class Stream : public std::deque<Tensor>, public Object {
    public:
        static int nt_min;
        static int nt_max;
        static Partial t;
        std::string id;
        Stream(Tensor,Object*parent=NULL);
        Stream(Tensor,std::string="",Object*parent=NULL);
        ~Stream();
        Stream& dump(bool=false);
        Tensor& operator()(int);
        Tensor operator()(int) const;
        Stream& operator+=(const Tensor&);
        Stream& operator&=(const Tensor&);
    };
}

#endif
