//!
//! @file Register.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_REGISTER_HPP
# define JBR_CREGISTER_REGISTER_HPP

#include <string>

//!
//! @namespace jbr
//!
namespace jbr
{
    //!
    //! @class Register
    //! @brief Smart memory, allowing to interact and persist data in an architectural, dynamic and simplified way.
    //!
    class Register
    {
    public:
        //!
        //! @brief Register constructor.
        //!
        Register() = default;
        //!
        //! @brief Copy constructor
        //! @warning Not usable.
        //!
        Register(const Register &) = delete;
        //!
        //! @brief Equal overload operator.
        //! @warning Not usable.
        //!
        Register    &operator=(const Register &) = delete;
        //!
        //! @brief Register class destructor.
        //!
        ~Register() = default;

    public:
        //!
        //! @brief Create a register according a input path.
        //! @param path Register path to create.
        //! @warning The register must exist. Exception are raised in error cases.
        //!
        void    create(const std::string &path);
    };
}

#endif //JBR_CREGISTER_REGISTER_HPP
