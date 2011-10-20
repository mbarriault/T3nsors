//
//  Params.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-19.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Params_h
#define T3nsors_Params_h

#include "Object.h"
#include <map>
#include <ostream>

namespace T3 {
    class Params : public std::map<std::string,real> {
    public:
    };
}

std::ostream& operator<<(std::ostream&,T3::Params);

#endif
