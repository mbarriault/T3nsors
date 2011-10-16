//
//  tuple.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "tuple.h"

T3::tuple::tuple(int n, ...) {
    va_list args;
    va_start(args, n);
    LOOP(n)
        push_back(va_arg(args, int));
}

/*T3::tuple::tuple(std::initializer_list<int> init) : array<int>(init) {
    for ( const int& t : init )
        push_back(t);
}*/

int T3::tuple::Si(int a) const {
	if ( a== -1 ) a = (int)size();
	int s = 0;
	FOR(i,a) s += at(i);
	return s;
}

int T3::tuple::Pr(int a) const {
	if ( a== -1 ) a = (int)size();
	int p = 1;
	FOR(i,a) p *= at(i);
	return p;
}

int T3::tuple::map(T3::tuple O) const {
	int o = 0;
	FOR(i,size()) {
        int A = mod(O[i], at(i));
		for ( int j=i-1; j>=0; j-- )
			A *= at(j);
		o += A;
	}
	return o;
}

T3::tuple T3::tuple::map(int o) const {
	tuple O((int)this->size());
	FOR(i,size()) {
		O[i] = o;
		FOR(j,i) O[i] -= O[j]*Pr(j);
		O[i] /= Pr(i);
		O[i] %= at(i);
	}
	return O;
}

