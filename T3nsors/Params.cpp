//
//  Params.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-19.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Params.h"

std::ostream& operator<<(std::ostream& out, T3::Params P) {
    T3::Params::iterator p;
    for (p = P.begin(); p != P.end(); ++p) {
        out << p->first << "\t = " << p->second << std::endl;
    }
//    for ( const std::pair<std::string, real>& p : P )
//        out << p.first << "\t = " << p.second << std::endl;
    return out;
}

