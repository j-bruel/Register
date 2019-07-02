//!
//! @file Register.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_REGISTER_HPP
# define JBR_CREGISTER_REGISTER_HPP

# include <jbr/reg/Rights.hpp>
# include <tinyxml2.h>
# include <string>

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
    private:
        jbr::reg::Rights    mRights; //!< Register configuration rights.

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

/*    public:
        jbr::reg::Variable  operator[](const std::string &path) const;*/

    public:
        //!
        //! @brief Create a register according a input path.
        //! @param path Register path to create.
        //! @warning The register must exist. Exception are raised in error cases.
        //!
        void    create(const std::string &path) const;
        //!
        //! @brief Open and check the validity of a existing register according a input path.
        //! @param path Register path to open.
        //!
        void    open(const std::string &path);
        //!
        //! @brief Check if a register exist. Only check if the register file exist on system.
        //! @param path Register path.
        //! @return True if exist, false if not.
        //! @warning This function does not check if the register is corrupt or valid. This function only check if the file exist.
        //!
        bool    exist(const std::string &path) const noexcept;
        //!
        //! @brief Check if a register is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @param path Register path to check.
        //! @warning This function does not need to be called after open function.
        //!
        void    verify(const std::string &path);
        //!
        //! @brief Copy a existing register to a new one.
        //! @param pathFrom Register copied.
        //! @param pathTo New register path.
        //!
        void    copy(const std::string &pathFrom, const std::string &pathTo);
        //!
        //! @brief Move a existing register. Can be use as a rename register function.
        //! @param pathOld Old register path.
        //! @param pathNew New register path.
        //!
        void    move(const std::string &pathOld, const std::string &pathNew);
        //!
        //! @brief Destroy a existing register. The target register will be removed definitively on the system.
        //! @param path Register path to destroy.
        //!
        void    destroy(const std::string &path);

    private:
        //!
        //! @brief Create the header of the new target register.
        //! @param path Register path to create.
        //!
        void    createHeader(const std::string &path) const;

    private:
        //!
        //! @brief Check if a register rights is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @param path Register path to check.
        //!
        void    verifyRights(tinyxml2::XMLNode  *nodeHeader);
        //!
        //! @brief Check if a register is openable. The register is not openable if the fields read or open from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        inline bool isOpenable() const noexcept { return (mRights.mRead && mRights.mOpen); }
        //!
        //! @brief Check if a register is copyable. The register is not copyable if the fields read or copy from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        inline bool isCopyable() const noexcept { return (mRights.mRead && mRights.mCopy); }
        //!
        //! @brief Check if a register is movable. The register is not movable if the fields write, read or copy from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        inline bool isMovable() const noexcept { return (mRights.mWrite && mRights.mRead && mRights.mCopy); }
        //!
        //! @brief Check if a register is destroyable. The register is not destroyable if the fields write, read or destroy from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        inline bool isDestroyable() const noexcept { return (mRights.mWrite && mRights.mRead && mRights.mDestroy); }
    };
}

#endif //JBR_CREGISTER_REGISTER_HPP
