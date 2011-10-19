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

typedef double real;

#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/time.h>
#include <cmath>
#include <unistd.h>

namespace T3 {
    class Object {
    public:
        Object* parent;
        std::string id;
        Object(Object* parent=0) {
            this->parent = parent;
        }
        
        void toss() {
            if ( parent == 0 or parent == NULL )
                printf("Tossed to root!\n");
            else
                parent->toss();
        }
        
        static int mod(int a, int p) {
            return (p + a % p) % p;
        }
        
        static std::string itos(int i) {
            std::ostringstream out;
            out << i;
            return out.str();
        }
        
        static std::string ftos(real x) {
            std::ostringstream out;
            out << x;
            return out.str();
        }
        
        static std::string mkdir(std::string dir) {
            std::string cmd = (std::string)"mkdir " + dir + " 2> /dev/null";
            while ( system(cmd.c_str()) ) {
                for ( unsigned long i = dir.size()-1; i>0; i-- ) {
                    dir[i]++;
                    if ( dir[i] < 58 ) break;
                    else dir[i] -= 10;
                }
                cmd = (std::string)"mkdir " + dir + " 2> /dev/null";
            }
            return dir;
        }
        
        static std::string timecoord() {
            time_t now;
            struct tm* timeinfo;
            time(&now);
            timeinfo = localtime(&now);
            char str[12];
            strftime(str, 9, "%U%w%H%M", timeinfo);
            return (std::string)str;
        }
        
        static timeval gettime() {
            timeval now;
            struct timezone tzp;
            gettimeofday(&now, &tzp);
            return now;
        }
        
        static long elapsed(timeval before) {
            timeval now = gettime();
            if ( before.tv_usec > now.tv_usec ) {
                now.tv_usec += 1e6;
                now.tv_sec--;
            }
            timeval lapsed;
            lapsed.tv_usec = now.tv_usec - before.tv_usec;
            lapsed.tv_sec = now.tv_sec - before.tv_sec;
            return lapsed.tv_usec + 1e6*lapsed.tv_sec;
        }
        
        static std::string timerem(timeval before, long multi) {
            std::ostringstream out;
            long lapsed = elapsed(before);
            long left = int((multi*lapsed)/1e6);
            if ( left > 86400 )
                out << left/86400 << "d ";
            if ( left > 3600 )
                out << (left%86400)/3600 << "h ";
            if ( left > 60 )
                out << (left%3600)/60 << "m ";
            out << left%60 << "s" << std::flush;
            return out.str();
        }
        
        static std::string pad(int n, int w) {
            std::ostringstream out;
            out << std::setw(w) << std::setfill('0') << n << std::flush;
            return out.str();
        }
        
        static std::string pad(real t, real T, real dt) {
            int n = -log10(dt)+2;
            int m = log10(T)+2;
            if ( n >= 0 ) n++;
            int w = n+m;
            if ( n < 0 ) n = 0;
            std::ostringstream out;
            out << std::setw(w) << std::setfill('0') << std::setprecision(n) << std::fixed << t;
            return out.str();
        }
    };
}

#endif
