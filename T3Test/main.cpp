//
//  main.cpp
//  T3Test
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include <iostream>
#include <T3nsors/T3nsors.h>
using namespace T3;

int main (int argc, const char * argv[])
{
    tuple a(2, 3, 4);
    field x(a), y(a);
    
    x(0,0) = 5.;
    y(0,0) = -3.;
    y(1,-1) = 2.;
    field z = LC(1., &x, 2., &y);
    std::cout << z << std::endl;
    return 0;
}

