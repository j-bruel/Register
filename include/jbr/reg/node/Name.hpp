//!
//! @file name.hpp
//! @author jbruel
//! @date 27/07/19
//!

#ifndef JBR_CREGISTER_REGISTER_NODE_NAME_HPP
# define JBR_CREGISTER_REGISTER_NODE_NAME_HPP

namespace jbr::reg::node::name
{
    static constexpr char *reg = "register";
    static constexpr char *header = "header";

    namespace _header
    {
        static constexpr char *version = "version";
        static constexpr char *rights = "rights";
        namespace _rights
        {
            static constexpr char *read = "read";
            static constexpr char *write = "write";
            static constexpr char *open = "open";
            static constexpr char *copy = "copy";
            static constexpr char *move = "move";
            static constexpr char *destroy = "destroy";
        }
    }
    static constexpr char *body = "body";
}

#endif //JBR_CREGISTER_REGISTER_NODE_NAME_HPP
