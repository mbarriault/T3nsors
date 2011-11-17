//
//  System.h
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#ifndef T3nsors_System_h
#define T3nsors_System_h

#include "Stream.h"
#include "Set.h"

namespace T3 {
    class System : public Array<Stream> {
    protected:
        void Evolve();
        Set Dissipate(const Set&);
    public:
        Partial t;
        Connection* Del;
        real epsilon;
        virtual Set RHS(Set&) = 0;
        virtual int Condition() = 0;
        virtual void Initialize() {
            epsilon = 0.;
        }
        virtual void PreEvolve() {}
        virtual void PostEvolve() {}
        virtual void Cleanup() {}
        int Run();
        operator Set();
    };
}

#endif
