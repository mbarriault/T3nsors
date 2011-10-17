//
//  Partial.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-17.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Partial.h"
#include <cmath>

T3::Partial::Partial() {
    
}

T3::Partial::Partial(int p, double a, int n, double d, Object* parent) : p(p), a(a), n(n), d(d), Object(parent) {
    b = a + n*d;
    bnd = bounds_edge;
}

T3::Partial::Partial(int p, double a, double b, int n, Object* parent) : p(p), a(a), b(b), n(n), Object(parent) {
    d = (b-a)/n;
    bnd = bounds_edge;
}

T3::Partial::Partial(int p, double a, double d, double b, Object* parent) : p(p), a(a), d(d), b(b), Object(parent) {
    n = int((b-a)/d);
    bnd = bounds_edge;
}

T3::Partial T3::Partial::Cartesian(int p, int n, double a, double b, Object* parent) {
    Partial D(p, a, b, n, parent);
    D.n += 1;
    D.bnd = bounds_edge;
    return D;
}

T3::Partial T3::Partial::Cartesian(int p, Partial D, double a, double b, Object* parent) {
    Partial E(p, a, D.d, b, parent);
    E.n += 1;
    E.bnd = bounds_edge;
    return E;
}

T3::Partial T3::Partial::Azimuth(int p, int n, Object* parent) {
    Partial D(p, 0., M_PI, n, parent);
    D.a += D.d;
    D.b -= D.d;
    D.n -= 1;
    D.bnd = bounds_bounce;
    return D;
}

T3::Partial T3::Partial::Azimuth(int p, Partial D, Object* parent) {
    Partial E(p, 0., D.a*D.d, M_PI, parent);
    return Azimuth(p, E.n, parent);
}

T3::Partial T3::Partial::Polar(int p, int n, Object* parent) {
    Partial D(p, 0., n, 2*M_PI/n, parent);
    D.a += D.d;
    D.b -= D.d;
    D.bnd = bounds_periodic;
    return D;
}

double T3::Partial::operator()(int i) {
    return a + i*d;
}

T3::Field T3::Partial::operator()(T3::Field x) {
    Field dx(x.N, x.parent);
    int dg = x.N.Pr(p+1);
    int dc = x.N.Pr(p);
    int G = x.N.Pr()/dg;
    int C = x.N[p];
    FOR(g,G) FOR(m,dc) {
        int i = g*dg + m;
        if ( bnd == bounds_bounce ) {
            dx[i] = dx[i+(C-1)*dc] = 0.;
        }
        else if ( bnd == bounds_periodic ) {
            dx[i] = (x[i+dc]-x[i+(C-1)*dc])/(2*d);
        }
        else {
            dx[i] = (x[i+dc]-x[i])/d;
            dx[i+(C-1)*dc] = (x[i+(C-1)*dc]-x[i+(C-2)*dc])/d;
        }
        if ( C > 2 ) FRO(c,1,C-1)
            dx[i+c*dc] = (x[i+(c+1)*dc]-x[i+(c-1)*dc])/(2*d);
        else if ( C > 1 )
            dx[i] = dx[i+dc] = (x[i+dc]-x[i])/d;
        else
            dx[i] = 0.;
    }
    return dx;
}

std::ostream& operator<<(std::ostream& out, T3::Partial D) {
    out << "[ " << D.a << ", " << D.b << " ]\t";
    out << D.n << "\t";
    out << D.p << "\t";
    out << D.d << "\t";
    out << D.bnd << std::flush;
    return out;
}
