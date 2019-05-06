//!
//! @file reg/factorial.cpp
//! @author jbruel
//! @date 29/04/19
//!

#include "jbr/reg/factorial.hpp"

int factorial(int number)
{
    int result = 1;
    
    for (int i = 1; i <= number; ++i)
        result *= i;
    return (result);
}
