//!
//! @file Variable.hpp
//! @author jbruel
//! @date 07/06/19
//!

#ifndef JBR_CREGISTER_REGISTER_VARIABLE_HPP
# define JBR_CREGISTER_REGISTER_VARIABLE_HPP

# include <jbr/Register.hpp>

//!
//! @namespace jbr
//!
namespace jbr::reg
{

    //!
    //! @class Variable
    //! @brief Unique register variable.
    //!
    class Variable : private jbr::Register
    {
    private:
        std::string mPath;

    public:
        //!
        //! @brief Register variable constructor.
        //! @warning Not usable.
        //!
        Variable() = delete;
        //!
        //! @brief Register variable constructor with register owner path.
        //! @param registerPath Owner register path.
        //!
        Variable(const std::string &registerPath);
        //!
        //! @brief Copy constructor
        //! @warning Not usable.
        //!
        Variable(const Variable &) = delete;
        //!
        //! @brief Equal overload operator.
        //! @warning Not usable.
        //!
        Variable    &operator=(const Variable &) = delete;
        //!
        //! @brief Register variable class destructor.
        //!
        ~Variable() = default;

/*    public:
        void    operator=(const std::string &value) const;*/
    };

}

#endif //JBR_CREGISTER_REGISTER_VARIABLE_HPP
