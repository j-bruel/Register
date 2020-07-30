//!
//! @file Variable.hpp
//! @author jbruel
//! @date 30/07/19
//!

#ifndef JBR_CREGISTER_REGISTER_VARIABLE_HPP
# define JBR_CREGISTER_REGISTER_VARIABLE_HPP

# include <jbr/reg/var/perm/Rights.hpp>
# include <jbr/reg/exception.hpp>
# include <optional>

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{

    //!
    //! @class Variable
    //! @brief Register variable data structure.
    //!
    class   Variable final
    {
    private:
        std::string                 mName; //!< Register variable name.
        std::string                 mValue; //!< Register variable value.
        jbr::reg::var::perm::Rights mRights; //!< Register variable rights associated.

    public:
        //!
        //! @brief Default constructor.
        //! @warning Not available.
        //!
        Variable() = delete;
        //!
        //! @brief Register variable constructor.
        //! @param name Register variable name.
        //! @param value Register variable value.
        //! @param rights Register variable rights associated.
        //!
        explicit Variable(std::string &&name, std::string &&value = "", const std::optional<jbr::reg::var::perm::Rights> &rights = std::nullopt);
        //!
        //! @brief Copy constructor.
        //!
        Variable(const Variable &) = default;
        //!
        //! @brief Equal operator overload.
        //! @return Register variable data structure load according original class.
        //!
        Variable    &operator=(const Variable &) = default;
        //!
        //! @brief Default destructor.
        //!
        ~Variable() = default;

    public:
        //!
        //! @brief Read the variable value. Extract the value of this variable.
        //! @return Variable value.
        //!
        [[nodiscard]]
        inline const char   *read() const noexcept { return (mValue.c_str()); }
        //!
        //! @brief Update the variable value. Set the variable value to a new data.
        //! @param value New data to set into the variable value.
        //!
        inline void         update(std::string &&value) noexcept { mValue = value; }
        //!
        //! @brief Rename the variable name.
        //! @param name New variable name.
        //! @throw Raise if the new variable name is empty.
        //!
        void                rename(std::string &&name) noexcept(false);
    };
}

#endif //JBR_CREGISTER_REGISTER_VARIABLE_HPP
