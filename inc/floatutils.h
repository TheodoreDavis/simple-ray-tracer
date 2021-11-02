#ifndef _FLOATUTILS_
#define _FLOATUTILS_

#include <limits>
#include <cstdlib>
#include <cmath>

//Collection of macros to handle comparisons between two floating point numbers
#define FLOAT_EQUAL(a, b) (std::abs(a - b) <= std::numeric_limits<float>::epsilon())
#define FLOAT_NEQUAL(a, b) (!(FLOAT_EQUAL(a, b)))
#define FLOAT_GREATER(a, b) ((a - b) > std::numeric_limits<float>::epsilon())
#define FLOAT_LESS(a, b) ((a - b) < (0 - std::numeric_limits<float>::epsilon()))
#define FLOAT_EGREATER(a, b) (!(FLOAT_LESS(a, b)))
#define FLOAT_ELESS(a, b) (!(FLOAT_GREATER(a, b)))

#define FLOAT_RAND (rand()/(RAND_MAX+1.0))
#define FLOAT_RAND_RANGE(min,max) (FLOAT_RAND * (max - min) + min)

#define FLOAT_SQUARE(a) (a*a)

#endif
