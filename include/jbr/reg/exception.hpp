//!
//! @file exception.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_EXCEPTION_HPP
# define JBR_CREGISTER_EXCEPTION_HPP

# include <exception>
# include <string>
# include <utility>

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{

    //!
    //! @class exception
    //! @brief Custom exception class for register error cases.
    //!
    class exception : public std::exception
    {
    private:
        std::string mMsg; //!< Exception message

    public:
        //!
        //! @brief Custom exception.
        //! @param msg Exception message.
        //!
        explicit exception(const std::string &msg) : mMsg(msg) {}
        //!
        //! @brief Exception throw destructor.
        //!
        ~exception() noexcept override = default;

    public:
        //!
        //! @brief What exception information.
        //! @return What message.
        //!
        const char  *what() const noexcept override { return (mMsg.c_str()); }
    };

}

#endif //JBR_CREGISTER_EXCEPTION_HPP
