//
//  Object.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_Object_h
#define T3nsors_Object_h

#define FOR(n,N) for ( int n=0; n<N; n++ )
#define FRO(n,i,N) for ( int n=i; n<N; n++ )
#define LOOP(N) for ( int __n=0; __n<N; __n++ )

#include <cstdio>

namespace T3 {
    class Object {
    public:
        Object* parent;
        Object(Object* parent=0) {
            this->parent = parent;
        }
        
        static int mod(int a, int p) {
            return (p + a % p) % p;
        }
        
        void toss() {
            if ( parent == 0 or parent == NULL )
                printf("Tossed to root!\n");
            else
                parent->toss();
        }
    };
}

#endif
