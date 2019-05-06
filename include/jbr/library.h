//!
//! @file include/jbr/library.h
//! @author jbruel
//! @date 29/04/19
//!

#ifndef JBR_CREGISTER_LIBRARY_H
# define JBR_CREGISTER_LIBRARY_H

//!
//! @note EXPORTED for any platform
//!
# ifdef _WIN32
#  ifdef WIN_EXPORT
#   define EXPORTED  __declspec( dllexport )
#  else
#   define EXPORTED  __declspec( dllimport )
#  endif
# else
#  define EXPORTED
# endif

extern "C"
{
    EXPORTED void hello();
}

#endif //JBR_CREGISTER_LIBRARY_H