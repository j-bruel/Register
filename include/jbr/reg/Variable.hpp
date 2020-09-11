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
        //! @brief Read the variable key. Extract the key of this variable.
        //! @return Variable key.
        //! @throw Raise if the variable does not have to rights.
        //!
        [[nodiscard]]
        const char *key() const noexcept(false);
        //!
        //! @brief Read the variable value. Extract the value of this variable.
        //! @return Variable value.
        //! @throw Raise if the variable does not have to rights.
        //!
        [[nodiscard]]
        const char   *read() const noexcept(false);
        //!
        //! @brief Update the variable value. Set the variable value to a new data.
        //! @param value New data to set into the variable value.
        //! @throw Raise if the variable does not have to rights.
        //!
        void         update(std::string &&value) noexcept(false);
        //!
        //! @brief Rename the variable name.
        //! @param name New variable name.
        //! @throw Raise if the new variable name is empty or if the variable does not have to rights.
        //!
        void         rename(std::string &&name) noexcept(false);
        //!
        //! @brief Extract variable rights information's.
        //! @return Variable rights.
        //!
        [[nodiscard]]
        inline jbr::reg::var::perm::Rights  rights() const noexcept { return (mRights); }
        //!
        //! @brief Update access rights to the variable.
        //! @param rights New rights to apply.
        //! @throw Raise if current read does not allow it.
        //!
        void    reaccess(const jbr::reg::var::perm::Rights &rights) noexcept(false);

    public:
        //!
        //! @brief Check if the variable is readable. The variable is not readable if the fields read from register/body/variable/rights nodes is false.
        //! @return Readable status.
        //! @throw Raise if impossible to extract the rights data from the variable.
        //!
        [[nodiscard]]
        inline bool isReadable() const noexcept { return (mRights.mRead); }
        //!
        //! @brief Check if the variable is writable. The variable is not writable if the fields write from register/body/variable/rights nodes is false.
        //! @return Writable status.
        //! @throw Raise if impossible to extract the rights data from the variable.
        //!
        [[nodiscard]]
        inline bool isWritable() const noexcept { return (mRights.mWrite); }
        //!
        //! @brief Check if the variable is updatable. The variable is not updatable if the fields write or update from register/body/variable/rights nodes is false.
        //! @return Updatable status.
        //! @throw Raise if impossible to extract the rights data from the variable.
        //!
        [[nodiscard]]
        inline bool isUpdatable() const noexcept { return (mRights.mWrite && mRights.mUpdate); }
        //!
        //! @brief Check if the variable is renamable. The variable is not renamable if the fields write, update or rename from register/body/variable/rights nodes is false.
        //! @return Renamable status.
        //! @throw Raise if impossible to extract the rights data from the variable.
        //!
        [[nodiscard]]
        inline bool isRenamable() const noexcept { return (mRights.mWrite && mRights.mUpdate && mRights.mRename); }
        //!
        //! @brief Check if the variable is copyable. The variable is not copyable if the fields read or copy from register/body/variable/rights nodes is false.
        //! @return Copyable status.
        //! @throw Raise if impossible to extract the rights data from the variable.
        //!
        [[nodiscard]]
        inline bool isCopyable() const noexcept { return (mRights.mRead && mRights.mCopy); }
        //!
        //! @brief Check if the variable is removable. The variable is not removable if the fields read or remove from register/body/variable/rights nodes is false.
        //! @return Removable status.
        //! @throw Raise if impossible to extract the rights data from the variable.
        //!
        [[nodiscard]]
        inline bool isRemovable() const noexcept { return (mRights.mRead && mRights.mRemove); }
    };

}

#endif //JBR_CREGISTER_REGISTER_VARIABLE_HPP
