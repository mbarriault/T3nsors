//
//  Field.cpp
//  T3nsors
//
//  Created by Michael Barriault on 11-10-14.
//  Copyright (c) 2011 University of Guelph. All rights reserved.
//

#include "Field.h"
#include <cmath>

T3::Field::Field(Tuple N, Object* parent) : N(N) {
    this->parent = parent;
    assign(N.Pr(), 0.);
}

T3::Field::Field(Tuple N, Array<real> L) : N(N), Array<real>(L) {
    
}

void T3::Field::write(H5::H5File* file, std::string tid, int i) {
    const hsize_t* dim = (hsize_t*)&N[0];
    const real* data = &at(0);
    H5::DataSpace* dataspace = new H5::DataSpace((int)N.size(), dim);
    H5::DataSet* dataset = new H5::DataSet( file->createDataSet(((std::string)"/data/" + tid + "/" + itos(i)).c_str(), H5::PredType::NATIVE_DOUBLE, *dataspace) );
    dataset->write(data, H5::PredType::NATIVE_DOUBLE);
    delete dataspace;
    delete dataset;
}

real& T3::Field::operator()(int a, ...) {
	va_list args;
	va_start(args,a);
	T3::Tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(args,int);
		o[i] = a;
	}
    va_end(args);
	return at(N.map(o));
}

real T3::Field::operator()(int a, ...) const {
	va_list vl;
	va_start(vl,a);
	T3::Tuple o((int)N.size());
    o[0] = a;
	FRO(i,1,o.size()) {
		a = va_arg(vl,int);
		o[i] = a;
	}
    va_end(vl);
	return at(N.map(o));
}

real& T3::Field::operator[](int o) {
    return (*(Array<real>*)(this))[o];
}

real T3::Field::operator[](int o) const {
    real val = (*(Array<real>*)(this))[o];
    if ( val != val ) {
        printf("Found a NaN!");
        parent->toss();
    }
    return val;
}

real T3::Field::L2(int p) {
    real l2x = 0.;
    FOR(o, size()) l2x += pow(at(o), p);
    l2x = pow(l2x/size(), 1./p);
    return l2x;
}

T3::Field operator-(T3::Field x) {
    for ( real& i : x )
        i *= -1;
    return x;
}

T3::Field operator*(const real& a, const T3::Field& x) {
    return x * a;
}

std::ostream& operator<<(std::ostream& out, T3::Field x) {
    if ( x.N.size() == 2 ) {
        FOR(i, x.N[0]) {
            FOR(j, x.N[1]) out << x(i,j) << "\t";
            out << "\n";
        }
    }
    else {
        out << *(T3::Array<real>*)(&x);
    }
    return out;
}

T3::Field LC(real a, T3::Field* x, ...) {
    T3::Field M = (*x) * a;
    va_list args;
    va_start(args, x);
    return _LC<T3::Field>(a, M, args);
}
