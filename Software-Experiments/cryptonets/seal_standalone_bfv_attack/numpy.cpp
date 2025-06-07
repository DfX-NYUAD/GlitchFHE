#include "numpy.h"
#include <cstddef>

namespace numpy
{

size_t sizeCeilPowerOfTwo(size_t n)
{
    size_t counter=0;
    while (n)
    {
        counter++;
        n>>=1;
    }
    return counter;
}

} // numpy
