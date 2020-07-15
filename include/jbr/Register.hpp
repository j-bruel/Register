//!
//! @file Register.hpp
//! @author jbruel
//! @date 13/07/20
//!

#ifndef JBR_CREGISTER_REGISTER_HPP
# define JBR_CREGISTER_REGISTER_HPP

# include <jbr/reg/Instance.hpp>
# include <memory>

//!
//! @namespace jbr
//!
namespace jbr
{

    //!
    //! @brief Register type definition.
    //!
    using Register = std::unique_ptr<jbr::reg::Instance>;

}

#endif //JBR_CREGISTER_REGISTER_HPP
