#include <limits>
#include <cmath>

//Collection of macros to handle comparisons between two floating point numbers
#define CMPFLOAT_EQUAL(a, b) (std::abs(a - b) <= std::numeric_limits<float>::epsilon())
#define CMPFLOAT_NEQUAL(a, b) (!(CMPFLOAT_EQUAL(a, b)))
#define CMPFLOAT_GREATER(a, b) ((a - b) > std::numeric_limits<float>::epsilon())
#define CMPFLOAT_LESS(a, b) ((a - b) < (0 - std::numeric_limits<float>::epsilon()))
#define CMPFLOAT_EGREATER(a, b) (!(CMPFLOAT_LESS(a, b)))
#define CMPFLOAT_ELESS(a, b) (!(CMPFLOAT_GREATER(a, b)))