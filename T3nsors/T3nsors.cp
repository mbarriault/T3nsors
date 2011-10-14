/*
 *  T3nsors.cp
 *  T3nsors
 *
 *  Created by Michael Barriault on 11-10-14.
 *  Copyright (c) 2011 University of Guelph. All rights reserved.
 *
 */

#include <iostream>
#include "T3nsors.h"
#include "T3nsorsPriv.h"

void T3nsors::HelloWorld(const char * s)
{
	 T3nsorsPriv *theObj = new T3nsorsPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void T3nsorsPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

