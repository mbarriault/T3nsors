//
//  Tuple.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Tuple.h"

T3::Tuple::Tuple(int n, ...) {
    va_list args;
    va_start(args, n);
    LOOP(n)
        push_back(va_arg(args, int));
    va_end(args);
}

/*T3::Tuple::Tuple(std::initializer_list<int> init) : Array<int>(init) {
    for ( const int& t : init )
        push_back(t);
}*/

int T3::Tuple::Si(int a) const {
	if ( a== -1 ) a = (int)size();
	int s = 0;
	FOR(i,a) s += at(i);
	return s;
}

int T3::Tuple::Pr(int a) const {
	if ( a == -1 ) a = (int)size();
	int p = 1;
	FOR(i,a) p *= at(i);
	return p;
}

int T3::Tuple::map(const T3::Tuple& O) const {
	int o = 0;
	FOR(i,size()) {
        int A = mod(O[i], at(i));
		for ( int j=i-1; j>=0; j-- )
			A *= at(j);
		o += A;
	}
	return o;
}

T3::Tuple T3::Tuple::map(int o) const {
	Tuple O((int)this->size());
	FOR(i,size()) {
		O[i] = o;
		FOR(j,i) O[i] -= O[j]*Pr(j);
		O[i] /= Pr(i);
		O[i] %= at(i);
	}
	return O;
}

