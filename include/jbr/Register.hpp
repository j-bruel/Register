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
# include <optional>

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{
    //!
    //! @class Variable
    //! @note Forward declaration
    //!
    class Variable;
}

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

    public:
        //!
        //! @brief Variable extractor operator.
        //! @param path Register path used.
        //! @return Variable class.
        //!
        jbr::reg::Variable  operator[](const std::string &path);

    public:
        //!
        //! @brief Create a register according a input path.
        //! @param path Register path to create.
        //! @param rights Register rights.
        //! @warning The register must exist. Exception are raised in error cases.
        //!
        void    create(const std::string &path, const std::optional<jbr::reg::Rights> &rights = std::nullopt) const noexcept(false);
        //!
        //! @brief Open and check the validity of a existing register according a input path.
        //! @param path Register path to open.
        //!
        void    open(const std::string &path) noexcept(false);
        //!
        //! @brief Check if a register exist. Only check if the register file exist on system.
        //! @param path Register path.
        //! @return True if exist, false if not.
        //! @warning This function does not check if the register is corrupt or valid. This function only check if the file exist.
        //!
        [[nodiscard]]
        static bool exist(const std::string &path) noexcept;
        //!
        //! @brief Check if a register is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @param path Register path to check.
        //! @warning This function does not need to be called after open function.
        //!
        void    verify(const std::string &path) noexcept(false);
        //!
        //! @brief Copy a existing register to a new one.
        //! @param pathFrom Register copied.
        //! @param pathTo New register path.
        //!
        void    copy(const std::string &pathFrom, const std::string &pathTo) noexcept(false);
        //!
        //! @brief Move a existing register. Can be use as a rename register function.
        //! @param pathOld Old register path.
        //! @param pathNew New register path.
        //!
        void    move(const std::string &pathOld, const std::string &pathNew) noexcept(false);
        //!
        //! @brief Destroy a existing register. The target register will be removed definitively on the system.
        //! @param path Register path to destroy.
        //!
        void    destroy(const std::string &path) noexcept(false);

    public:
        //!
        //! @brief Extract register rights information's.
        //! @param path Register path.
        //! @return Register rights.
        //!
        jbr::reg::Rights    rights(const std::string &path) noexcept(false);
        //!
        //! @brief Apply new rights on a register.
        //! @param path Register path.
        //! @param rights New rights to apply.
        //!
        void                applyRights(const std::string &path, const jbr::reg::Rights &rights) noexcept(false);

    protected:
        //!
        //! @static
        //! @brief Extract a sub element from a xml node.
        //! @param node Parent node.
        //! @param subNodeName Name of the sub node to extract.
        //! @return Extract element.
        //! @throw Throw a exception when the sub node can't be extracted.
        //!
        static tinyxml2::XMLElement    *getSubXMLElement(tinyxml2::XMLNode *node, const char *subElementName) noexcept(false);
        //!
        //! @static
        //! @brief Create a new element according a xml document.
        //! @param xmlDocument A Document binds together all the functionality.
        //! @param elementName Name of the new element.
        //! @return Created element.
        //! @throw Throw a exception when the sub element can't be created.
        //!
        static tinyxml2::XMLElement *newXMLElement(tinyxml2::XMLDocument *xmlDocument, const char *elementName) noexcept(false);
        //!
        //! @static
        //! @brief Load xml file with error handling.
        //! @param xmlDocument XML documentation to load.
        //! @param filePath XML file path to load.
        //! @throw Raise a exception if the file loading is impossible.
        //!
        static void loadXMLFile(tinyxml2::XMLDocument &xmlDocument, const char *filePath) noexcept(false);
        //!
        //! @static
        //! @brief Save xml file with error handling.
        //! @param xmlDocument XML documentation to save.
        //! @param filePath XML file path to save.
        //! @throw Raise a exception if the file saving is impossible.
        //!
        static void saveXMLFile(tinyxml2::XMLDocument &xmlDocument, const char *filePath) noexcept(false);

    private:
        //!
        //! @brief Create the header of the new target register.
        //! @param path Register path to create.
        //! @param rights Register rights.
        //!
        void    createHeader(const std::string &path, const std::optional<jbr::reg::Rights> &rights) const noexcept(false);

    private:
        //!
        //! @brief Check if a register rights is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @param path Register path to check.
        //!
        void    verifyRights(tinyxml2::XMLNode *nodeHeader) noexcept(false);
        //!
        //! @brief Write rights information's on register.
        //! @param reg XML document object.
        //! @param nodeHeader Header node from register.
        //! @param version Version node from register.
        //! @param rights Register rights.
        //! @warning This function must be call into a process, no check on pointers, object validity are done. File must be saved after call.
        //!
        void    writeRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeHeader,
                            tinyxml2::XMLElement *version, const jbr::reg::Rights &rights) const noexcept(false);
        //!
        //! @brief Query a boolean into a xml element field.
        //! @param xmlElement XML element to insert the boolean.
        //! @param status Boolean to insert.
        //! @throw If the element is set and the query failed.
        //!
        static void queryRightToXMLElement(tinyxml2::XMLElement *xmlElement, bool *status) noexcept(false);

    private:
        //!
        //! @brief Check if a register is openable. The register is not openable if the fields read or open from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        [[nodiscard]]
        inline bool isOpenable() const noexcept { return (mRights.mRead && mRights.mOpen); }
        //!
        //! @brief Check if a register is copyable. The register is not copyable if the fields read or copy from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        [[nodiscard]]
        inline bool isCopyable() const noexcept { return (mRights.mRead && mRights.mCopy); }
        //!
        //! @brief Check if a register is movable. The register is not movable if the fields write, read or copy from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        [[nodiscard]]
        inline bool isMovable() const noexcept { return (mRights.mWrite && mRights.mRead && mRights.mMove); }
        //!
        //! @brief Check if a register is destroyable. The register is not destroyable if the fields read or destroy from register/header/rights nodes is false.
        //! @param path Register path to check.
        //! @warning Verify must be called before or other method how set all register rights.
        //!
        [[nodiscard]]
        inline bool isDestroyable() const noexcept { return (mRights.mRead && mRights.mDestroy); }
    };
}

#endif //JBR_CREGISTER_REGISTER_HPP
