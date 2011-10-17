//
//  main.cpp
//  T3Test
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <T3nsors/T3nsors.h>
using namespace T3;

int main (int argc, const char * argv[])
{
    //Cartesian Del(3, 5, 0., 1., 0., 1., 0., 1.);
    Axisymmetric Del(50, 1., 2.);
    Tuple& N = Tensor::N;
    std::cout << N << std::endl;
    std::cout << Del << std::endl;
    
    Partial& r = Del[0];
    Partial& theta = Del[1];

    Vector y;
    FOR(i,N[0]) FOR(j,N[1]) y(0)(i,j,0) = r(i)*sin(theta(j));
    FOR(i,N[0]) FOR(j,N[1]) y(1)(i,j,0) = r(i)*cos(theta(j));
    FOR(i,N[0]) FOR(j,N[1]) y(2)(i,j,0) = r(i)*sin(theta(j))*cos(theta(j));
    
    Scalar Dy;
    FOR(i,N[0]) FOR(j,N[1]) Dy(i,j,0) = (2-pow(cos(theta(j)),2.))/sin(theta(j));

    Vector Cy;
    FOR(i,N[0]) FOR(j,N[1]) Cy(0)(i,j,0) = 3*pow(cos(theta(j)),2.) - 1;
    FOR(i,N[0]) FOR(j,N[1]) Cy(1)(i,j,0) = -2*sin(theta(j))*cos(theta(j));
    FOR(i,N[0]) FOR(j,N[1]) Cy(2)(i,j,0) = cos(theta(j));
    
    Scalar y2;
    FOR(i,N[0]) FOR(j,N[1]) y2(i,j,0) = pow(r(i),2.)*(1 + pow(sin(theta(j))*cos(theta(j)), 2.) );
    
    Vector z;
    FOR(i,N[0]) FOR(j,N[1]) z(0)(i,j,0) = r(i)*cos(theta(j));
    FOR(i,N[0]) FOR(j,N[1]) z(1)(i,j,0) = -r(i)*sin(theta(j));
    FOR(i,N[0]) FOR(j,N[1]) z(2)(i,j,0) = r(i)*sin(theta(j))*cos(theta(j));
    
    Vector yz;
    FOR(i,N[0]) FOR(j,N[1]) yz(0)(i,j,0) = r(i)*r(i)*sin(theta(j))*cos(theta(j))*(sin(theta(j))+cos(theta(j)));
    FOR(i,N[0]) FOR(j,N[1]) yz(1)(i,j,0) = r(i)*r(i)*sin(theta(j))*cos(theta(j))*(cos(theta(j))-sin(theta(j)));
    FOR(i,N[0]) FOR(j,N[1]) yz(2)(i,j,0) = -r(i)*r(i);
    
    Scalar E1 = Del*y - Dy;
    Vector E2 = (Del&y) - Cy;
    Scalar E3 = y*y - y2;
    Vector E4 = (y&y);
    Vector E5 = yz - (y&z);
    
    std::cout << Del.Int(E1[0]) << std::endl;
    std::cout << Del.Int(E2[0]) << std::endl;
    std::cout << Del.Int(E2[1]) << std::endl;
    std::cout << Del.Int(E2[2]) << std::endl;
    std::cout << Del.Int(E3[0]) << std::endl;
    std::cout << Del.Int(E4[0]) << std::endl;
    std::cout << Del.Int(E4[1]) << std::endl;
    std::cout << Del.Int(E4[2]) << std::endl;
    std::cout << Del.Int(E5[0]) << std::endl;
    std::cout << Del.Int(E5[1]) << std::endl;
    std::cout << Del.Int(E5[2]) << std::endl;

    return 0;
}

