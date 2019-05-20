#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

# if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#  include "doctest.h"
# else
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#   include "doctest.h"
#  pragma GCC diagnostic pop
# endif