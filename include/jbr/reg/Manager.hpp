//!
//! @file Manager.hpp
//! @author jbruel
//! @date 13/07/20
//!

#ifndef JBR_CREGISTER_REGISTER_MANAGER_HPP
# define JBR_CREGISTER_REGISTER_MANAGER_HPP

# include <jbr/Register.hpp>

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{

    //!
    //! @class Manager
    //! @brief Allow to manage a register.
    //!
    class Manager final
    {
    public:
        //!
        //! @brief Create a register according a input path.
        //! @param path Register path to create.
        //! @param rights Register rights.
        //! @warning The register must exist. Exception are raised in error cases.
        //! @throw Raise if impossible to create a register.
        //!
        [[nodiscard]]
        static jbr::Register create(const std::string &path, const std::optional<jbr::reg::Rights> &rights = std::nullopt) noexcept(false);
        //!
        //! @brief Open and check the validity of a existing register according a input path.
        //! @param path Register path to open.
        //! @throw Raise if impossible to open a register.
        //!
        [[nodiscard]]
        static jbr::Register open(const std::string &path) noexcept(false);
        //!
        //! @brief Check if a register exist. Only check if the register file exist on system.
        //! @param path Register path.
        //! @return True if exist, false if not.
        //! @warning This function does not check if the register is corrupt or valid. This function only check if the file exist.
        //!
        [[nodiscard]]
        static bool          exist(const std::string &path) noexcept;
        //!
        //! @brief Destroy a existing register. The target register will be removed definitively on the system.
        //! @param path Register path to destroy.
        //! @throw Raise if the register is not destroyable.
        //!
        static void          destroy(jbr::Register &reg) noexcept(false);
    };
}
#endif //JBR_CREGISTER_REGISTER_MANAGER_HPP
