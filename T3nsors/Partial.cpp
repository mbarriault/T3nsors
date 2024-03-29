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

T3::Partial::Partial(int p, real a, int n, real d, Object* parent) : p(p), a(a), n(n), d(d), Object(parent) {
    b = a + n*d;
    bnd = bounds_edge;
}

T3::Partial::Partial(int p, real a, real b, int n, Object* parent) : p(p), a(a), b(b), n(n), Object(parent) {
    d = (b-a)/n;
    bnd = bounds_edge;
}

T3::Partial::Partial(int p, real a, real d, real b, Object* parent) : p(p), a(a), d(d), b(b), Object(parent) {
    n = int((b-a)/d);
    bnd = bounds_edge;
}

T3::Partial T3::Partial::Cartesian(int p, int n, real a, real b, Object* parent) {
    Partial D(p, a, b, n, parent);
    D.n += 1;
    D.bnd = bounds_edge;
    return D;
}

T3::Partial T3::Partial::Cartesian(int p, real d, real a, real b, Object* parent) {
    Partial E(p, a, d, b, parent);
    E.n += 1;
    E.bnd = bounds_edge;
    return E;
}

T3::Partial T3::Partial::Azimuth(int p, int n, Object* parent) {
    Partial D(p, 0., M_PI, n, parent);
    D.a += D.d/2;
    D.b -= D.d/2;
//    D.n -= 1;
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

real T3::Partial::operator()(int i) const {
    return a + mod(i, n)*d;
}

void T3::Partial::write(H5::Group& grp) {
    real data[3];
    data[0] = a;
    data[1] = b;
    data[2] = d;
    hsize_t d = 3;
    grp.createDataSet( 
                itos(p).c_str(), 
                H5::PredType::NATIVE_DOUBLE, 
                H5::DataSpace(1, &d)
                       ).write(data, H5::PredType::NATIVE_DOUBLE);
}

T3::Field T3::Partial::operator()(const T3::Field& x) const {
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
            dx[i+(C-1)*dc] = (x[i]-x[i+(C-2)*dc])/(2*d);
        }
        else {
            dx[i] = (x[i+dc]-x[i])/d;
            dx[i+(C-1)*dc] = (x[i+(C-1)*dc]-x[i+(C-2)*dc])/d;
        }
        if ( C > 2 ) PFRO(c,1,C-1)
            dx[i+c*dc] = (x[i+(c+1)*dc]-x[i+(c-1)*dc])/(2*d);
        else if ( C > 1 )
            dx[i] = dx[i+dc] = (x[i+dc]-x[i])/d;
        else
            dx[i] = 0.;
    }
    return dx;
}

T3::Field T3::Partial::two(const T3::Field& x) const {
    Field dx(x.N, x.parent);
    int dg = x.N.Pr(p+1);
    int dc = x.N.Pr(p);
    int G = x.N.Pr()/dg;
    int C = x.N[p];
    FOR(g,G) FOR(m,dc) {
        int i = g*dg + m;
        if ( bnd == bounds_bounce ) {
            dx[i] = 2*(x[i+dc]-x[i])/(d*d);
            dx[i+(C-1)*dc] = 2*(x[i+(C-1)*dc]-x[i+(C-2)*dc])/(d*d);
        }
        else if ( bnd == bounds_periodic ) {
            dx[i] = (x[i+(C-1)*dc] - 2*x[i] + x[i+dc])/(d*d);
            dx[i+(C-1)*dc] = (x[i+(C-2)*dc] - 2*x[i+(C-1)*dc] + x[i])/(d*d);
        }
        else {
            dx[i] = (x[i] - 2*x[i+dc] + x[i+2*dc])/(d*d);
            dx[i+(C-1)*dc] = (x[i+(C-3)*dc] - 2*x[i+(C-2)*dc] + x[i+(C-1)*dc])/(d*d);
        }
        if ( C > 2 ) PFRO(c,1,C-1)
            dx[i+c*dc] = (x[i+(c-1)*dc] - 2*x[i+c*dc] + x[i+(c+1)*dc])/(d*d);
        else if ( C > 1 )
            dx[i] = dx[i+dc] = 0.;
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
