//!
//! @file name.hpp
//! @author jbruel
//! @date 27/07/19
//! @brief This is a dictionary of all nodes names from a register file.
//!

#ifndef JBR_CREGISTER_REGISTER_NODE_NAME_HPP
# define JBR_CREGISTER_REGISTER_NODE_NAME_HPP

//!
//! @namespace jbr::reg::node::name
//!
namespace jbr::reg::node::name
{
    //!
    //! @static
    //! @def reg
    //! @brief 'register' main node from a register file.
    //!
    static const char *reg = "register";
    //!
    //! @static
    //! @def header
    //! @brief 'register/header' node from a register file.
    //!
    static const char *header = "header";

    //!
    //! @namespace jbr::reg::node::name::_header
    //!
    namespace _header
    {
        //!
        //! @static
        //! @def version
        //! @brief 'register/header/version' field from a register file.
        //!
        static const char *version = "version";
        //!
        //! @static
        //! @def rights
        //! @brief 'register/header/rights' node from a register file.
        //!
        static const char *rights = "rights";
        //!
        //! @namespace jbr::reg::node::name::_header::_rights
        //!
        namespace _rights
        {
            //!
            //! @static
            //! @def read
            //! @brief 'register/header/rights/read' field from a register file.
            //!
            static const char *read = "read";
            //!
            //! @static
            //! @def write
            //! @brief 'register/header/rights/write' field from a register file.
            //!
            static const char *write = "write";
            //!
            //! @static
            //! @def open
            //! @brief 'register/header/rights/open' field from a register file.
            //!
            static const char *open = "open";
            //!
            //! @static
            //! @def copy
            //! @brief 'register/header/rights/copy' field from a register file.
            //!
            static const char *copy = "copy";
            //!
            //! @static
            //! @def move
            //! @brief 'register/header/rights/move' field from a register file.
            //!
            static const char *move = "move";
            //!
            //! @static
            //! @def destroy
            //! @brief 'register/header/rights/destroy' field from a register file.
            //!
            static const char *destroy = "destroy";
        }
    }
    //!
    //! @static
    //! @def body
    //! @brief 'register/body' node from a register file.
    //!
    static const char *body = "body";

    //!
    //! @namespace jbr::reg::node::name::_body
    //!
    namespace _body
    {
        //!
        //! @static
        //! @def variable
        //! @brief 'register/body/variable' field from a register file.
        //!
        static const char *variable = "variable";

        //!
        //! @namespace jbr::reg::node::name::_body::_variable
        //!
        namespace _variable
        {
            //!
            //! @static
            //! @def key
            //! @brief 'register/body/variable/key' field from a register file.
            //!
            static const char *key = "key";
            //!
            //! @static
            //! @def value
            //! @brief 'register/body/variable/value' field from a register file.
            //!
            static const char *value = "value";
            //!
            //! @static
            //! @def value
            //! @brief 'register/body/variable/rights' field from a register file.
            //!
            static const char *rights = "rights";
            //!
            //! @namespace jbr::reg::node::name::_body::_variable::_rights
            //!
            namespace _rights
            {
                //!
                //! @static
                //! @def read
                //! @brief 'register/body/variable/rights/read' field from a register file.
                //!
                static const char *read = "read";
                //!
                //! @static
                //! @def write
                //! @brief 'register/body/variable/rights/write' field from a register file.
                //!
                static const char *write = "write";
                //!
                //! @static
                //! @def open
                //! @brief 'register/body/variable/rights/update' field from a register file.
                //!
                static const char *update = "update";
                //!
                //! @static
                //! @def copy
                //! @brief 'register/body/variable/rights/rename' field from a register file.
                //!
                static const char *rename = "rename";
                //!
                //! @static
                //! @def move
                //! @brief 'register/body/variable/rights/copy' field from a register file.
                //!
                static const char *copy = "copy";
                //!
                //! @static
                //! @def destroy
                //! @brief 'register/body/variable/rights/remove' field from a register file.
                //!
                static const char *remove = "remove";
            }
        }
    }
}

#endif //JBR_CREGISTER_REGISTER_NODE_NAME_HPP
