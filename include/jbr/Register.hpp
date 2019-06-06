//!
//! @file Register.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_REGISTER_HPP
# define JBR_CREGISTER_REGISTER_HPP

# include <string>
# include <filesystem>

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
        void    create(const std::string &path) const;
        //!
        //! @brief Open a existing register according a input path.
        //! @param path Register path to open.
        //!
        void    open(const std::string &path) const;

    public:
        //!
        //! @brief Check if a register exist. Only check if the register file exist on system.
        //! @param path Register path.
        //! @return True if exist, false if not.
        //! @warning This function does not check if the register is corrupt or valid. This function only check if the file exist.
        //!
        bool    exist(const std::string &path) const noexcept;

    public:
        //!
        //! @brief Destroy a existing register. The target register will be removed definitively on the system.
        //! @param path Register path to destroy.
        //!
        void    destroy(const std::string &path) const;

    private:
        //!
        //! @brief Create the header of the new target register.
        //! @param path Register path to create.
        //!
        void    createHeader(const std::string &path) const;
        //!
        //! @brief Check if a register is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @param path Register path to check.
        //!
        void    validity(const std::string &path) const;
    };
}

#endif //JBR_CREGISTER_REGISTER_HPP
