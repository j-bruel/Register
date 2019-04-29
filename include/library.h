#ifndef CREGISTER_LIBRARY_H
#define CREGISTER_LIBRARY_H

// Define EXPORTED for any platform
#ifdef _WIN32
# ifdef WIN_EXPORT
#   define EXPORTED  __declspec( dllexport )
# else
#   define EXPORTED  __declspec( dllimport )
# endif
#else
# define EXPORTED
#endif

extern "C"
{
EXPORTED void hello();
}

#endif