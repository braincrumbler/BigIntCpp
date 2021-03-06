// $Id: bigint.cpp,v 1.74 2016-03-24 19:30:57-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const {
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const {
   ubigint result = uvalue + that.uvalue;
   return result;
}

bigint bigint::operator- (const bigint& that) const {
   ubigint result = uvalue - that.uvalue;
   return result;
}

bigint bigint::operator* (const bigint& that) const {
    //cases for 0 (needs to be converted to c++)
//    if ((value.size() == 1 && that.value.get(0) == 0) ||
//        (that.value.size() == 1 && that.value.get(0) == 0)) {
//        return new BigInt(0);
//    }
    if (is_negative == that.is_negative) {
        //Same sign multiplication
        return bigint (uvalue * that.uvalue, false);
    }
    else return bigint (uvalue *that.uvalue, true);
}

bigint bigint::operator/ (const bigint& that) const {
   bigint result = uvalue / that.uvalue;
   return result;
}

bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   return result;
}

bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   return out << "bigint(" << (that.is_negative ? "'-'" : "'+'")
              << that.uvalue << ")";
}

