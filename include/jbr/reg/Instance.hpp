//!
//! @file Register.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_REGISTER_INSTANCE_HPP
# define JBR_CREGISTER_REGISTER_INSTANCE_HPP

# include <jbr/reg/perm/Rights.hpp>
# include <jbr/reg/Variable.hpp>
# include <tinyxml2.h>
# include <filesystem>
# include <string>
# include <optional>

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{
    //!
    //! @class Manager
    //! @note Forward declaration
    //!
    class Manager;

    //!
    //! @class Instance
    //! @brief Smart memory, allowing to interact and persist data in an architectural, dynamic and simplified way.
    //!
    class Instance final
    {
        friend jbr::reg::Manager; //!< Register manager is allow to use the private member functions.

    private:
        std::string mPath; //!< Register location.

    public:
        //!
        //! @brief Default register constructor.
        //! @warning Not available.
        //!
        Instance() = delete;
        //!
        //! @brief Register instance constructor. A instance must be create with a path.
        //! @param path Register location.
        //! @throw Exception raise if the register path is invalid.
        //!
        explicit Instance(const char *path);
        //!
        //! @brief Register instance constructor. A instance must be create with a path.
        //! @param path Register location.
        //! @throw Exception raise if the register path is invalid.
        //!
        explicit Instance(std::string &&path) : mPath(std::move(path)) { checkPathValidity(); }
        //!
        //! @brief Copy constructor
        //! @warning Not usable.
        //!
        Instance(const Instance &) = delete;
        //!
        //! @brief Equal overload operator.
        //! @warning Not usable.
        //!
        Instance    &operator=(const Instance &) = delete;
        //!
        //! @brief Register instance destructor.
        //!
        ~Instance() = default;

    public:
        //!
        //! @brief Check if a register is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @warning This function does not need to be called after open function.
        //! @throw Raise if the register is invalid.
        //!
        void        verify() const noexcept(false);

    private:
        //!
        //! @brief Check if a register is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @param xmlDocument XML documentation to save.
        //! @warning This function does not need to be called after open function.
        //! @throw Raise if the register is invalid.
        //!
        void        verify(tinyxml2::XMLDocument &xmlDocument) const noexcept(false);

    public:
        //!
        //! @brief Check if a register exist. Only check if the register file exist on system.
        //! @return True if exist, false if not.
        //! @warning This function does not check if the register is corrupt or valid. This function only check if the file exist.
        //!
        [[nodiscard]]
        inline bool exist() const noexcept { return (std::filesystem::exists(mPath)); }

    public:
        //!
        //! @brief Extract the register localization.
        //! @return Register location.
        //!
        [[nodiscard]]
        const std::string   &localization() const noexcept { return (mPath); }

    public:
        //!
        //! @brief Copy a existing register to a new one.
        //! @param pathTo New register path, where the current register will be copyed.
        //! @throw Raise if impossible to copy the register.
        //!
        void            copy(const char *pathTo) const noexcept(false);
        //!
        //! @brief Move a existing register. Can be use as a rename register function.
        //! @param pathTo New register path, where the current register will be moved.
        //! @throw Raise if impossible to move the register.
        //!
        void            move(const char *pathTo) noexcept(false);
        //!
        //! @brief Rename a existing register. This is a alias to the 'move' function'.
        //! @param newPath New register path, where the current register will be moved.
        //! @throw Raise if impossible to rename the register.
        //!
        inline void    rename(const char *newPath) noexcept (false) { move(newPath); }

    public:
        //!
        //! @brief Extract register rights.
        //! @return Current register rights.
        //! @throw Raise if impossible to extract the data from the register.
        //!
        [[nodiscard]]
        jbr::reg::perm::Rights  rights() const noexcept(false);

    private:
        //!
        //! @brief Extract register rights according xml document.
        //! @param xmlDocument XML documentation to save.
        //! @return Current register rights.
        //! @throw Raise if impossible to extract the data from the register.
        //!
        [[nodiscard]]
        jbr::reg::perm::Rights  rights(tinyxml2::XMLDocument &xmlDocument) const noexcept(false);

    public:
        //!
        //! @brief Apply new rights on the register.
        //! @param rights New rights to apply.
        //! @throw Raise if invalid register or if the action is not allow.
        //!
        void                applyRights(const jbr::reg::perm::Rights &rights) const noexcept(false);

    public:
        //!
        //! @brief Check if a register is readable. The register is not readable if the fields read from register/header/rights nodes is false.
        //! @return Readable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isReadable() const noexcept { return (isReadable(rights())); }
        //!
        //! @brief Check if a register is openable. The register is not openable if the fields read or open from register/header/rights nodes is false.
        //! @return Openable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isOpenable() const noexcept(false) { return (isOpenable(rights())); }
        //!
        //! @brief Check if a register is writable. The register is not writable if the fields write from register/header/rights nodes is false.
        //! @return Writable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isWritable() const noexcept(false) { return (isWritable(rights())); }
        //!
        //! @brief Check if a register is copyable. The register is not copyable if the fields read or copy from register/header/rights nodes is false.
        //! @return Copyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isCopyable() const noexcept(false) { return (isCopyable(rights())); }
        //!
        //! @brief Check if a register is movable. The register is not movable if the fields write, read or copy from register/header/rights nodes is false.
        //! @return Movable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isMovable() const noexcept(false) { return (isMovable(rights())); }
        //!
        //! @brief Check if a register is destroyable. The register is not destroyable if the fields read or destroy from register/header/rights nodes is false.
        //! @return Destroyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isDestroyable() const noexcept(false) { return (isDestroyable(rights())); }

    private:
        //!
        //! @brief Check if a register is readable. The register is not readable if the fields read from register/header/rights nodes is false.
        //! @param xmlDocument Register file to use to check rights.
        //! @return Readable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isReadable(tinyxml2::XMLDocument &xmlDocument) const noexcept { return (isReadable(rights(xmlDocument))); }
        //!
        //! @brief Check if a register is openable. The register is not openable if the fields read or open from register/header/rights nodes is false.
        //! @param xmlDocument Register file to use to check rights.
        //! @return Openable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isOpenable(tinyxml2::XMLDocument &xmlDocument) const noexcept(false) { return (isOpenable(rights(xmlDocument))); }
        //!
        //! @brief Check if a register is writable. The register is not writable if the fields write from register/header/rights nodes is false.
        //! @param xmlDocument Register file to use to check rights.
        //! @return Writable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isWritable(tinyxml2::XMLDocument &xmlDocument) const noexcept(false) { return (isWritable(rights(xmlDocument))); }
        //!
        //! @brief Check if a register is copyable. The register is not copyable if the fields read or copy from register/header/rights nodes is false.
        //! @param xmlDocument Register file to use to check rights.
        //! @return Copyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isCopyable(tinyxml2::XMLDocument &xmlDocument) const noexcept(false) { return (isCopyable(rights(xmlDocument))); }
        //!
        //! @brief Check if a register is movable. The register is not movable if the fields write, read or copy from register/header/rights nodes is false.
        //! @param xmlDocument Register file to use to check rights.
        //! @return Movable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isMovable(tinyxml2::XMLDocument &xmlDocument) const noexcept(false) { return (isMovable(rights(xmlDocument))); }
        //!
        //! @brief Check if a register is destroyable. The register is not destroyable if the fields read or destroy from register/header/rights nodes is false.
        //! @param xmlDocument Register file to use to check rights.
        //! @return Destroyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isDestroyable(tinyxml2::XMLDocument &xmlDocument) const noexcept(false) { return (isDestroyable(rights(xmlDocument))); }

    private:
        //!
        //! @brief Check if a register is readable. The register is not readable if the fields read from register/header/rights nodes is false.
        //! @param rights Current register rights to check.
        //! @return Readable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isReadable(const jbr::reg::perm::Rights &rights) const noexcept { return (rights.mRead); }
        //!
        //! @brief Check if a register is openable. The register is not openable if the fields read or open from register/header/rights nodes is false.
        //! @param rights Current register rights to check.
        //! @return Openable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isOpenable(const jbr::reg::perm::Rights &rights) const noexcept { return (rights.mRead && rights.mOpen); }
        //!
        //! @brief Check if a register is writable. The register is not writable if the fields write from register/header/rights nodes is false.
        //! @param rights Current register rights to check.
        //! @return Writable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isWritable(const jbr::reg::perm::Rights &rights) const noexcept { return (rights.mWrite); }
        //!
        //! @brief Check if a register is copyable. The register is not copyable if the fields read or copy from register/header/rights nodes is false.
        //! @param rights Current register rights to check.
        //! @return Copyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isCopyable(const jbr::reg::perm::Rights &rights) const noexcept { return (rights.mRead && rights.mCopy); }
        //!
        //! @brief Check if a register is movable. The register is not movable if the fields write, read or copy from register/header/rights nodes is false.
        //! @param rights Current register rights to check.
        //! @return Movable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isMovable(const jbr::reg::perm::Rights &rights) const noexcept { return (rights.mWrite && rights.mRead && rights.mMove); }
        //!
        //! @brief Check if a register is destroyable. The register is not destroyable if the fields read or destroy from register/header/rights nodes is false.
        //! @param rights Current register rights to check.
        //! @return Destroyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        inline bool isDestroyable(const jbr::reg::perm::Rights &rights) const noexcept { return (rights.mRead && rights.mDestroy); }

    public:
        //!
        //! @brief Set a variable into the register.
        //! @param variable Variable to set.
        //! @param replaceIfExist Tell if the variable must be replace if the variable already exist.
        //!
        void    set(const jbr::reg::Variable &variable, bool replaceIfExist = true) const noexcept(false);
        //!
        //! @brief Extract a register variable.
        //! @param key Variable key to find and extract from the register.
        //! @return Register variable.
        //! @throw Raise if impossible to extract the variable.
        //!
        [[nodiscard]]
        jbr::reg::Variable  get(const char *key) const noexcept(false);

    private:
        //!
        //! @brief Override variable value if she already exist and if this is allow.
        //! @param xmlDocument Reference XML documentation (register).
        //! @param variable Variable to set.
        //! @param body Internal xml document pointer to the 'body' section.
        //! @param replaceIfExist Tell if the variable must be replace if the variable already exist.
        //! @return Status if a variable has been overrided.
        //! @throw If the override is not allow and the variable already exist.
        //!
        [[nodiscard]]
        bool    overrideVariable(tinyxml2::XMLDocument &xmlDocument, const jbr::reg::Variable &variable,
                                 tinyxml2::XMLElement *body, bool replaceIfExist) const noexcept(false);
        //!
        //! @brief Extract all rights from a variable.
        //! @param nodeRights Rights node from a variable.
        //! @return All variables rights.
        //! @throw Raise if impossible to extract rights.
        //!
        jbr::reg::var::perm::Rights getVariableRightsFromNode(tinyxml2::XMLNode *nodeRights) const noexcept(false);

    public:
        //!
        //! @brief Check if a variable exist on this current register.
        //! @param variable Variable to check into this register.
        //! @return Variable existing status.
        //! @throw Raise if impossible to load the register file.
        //!
        [[nodiscard]]
        bool    variableExist(const jbr::reg::Variable &variable) const  noexcept(false);

    private:
        //!
        //! @brief Check if the register path is valid.
        //! @throw Raise if the register path is invalid.
        //!
        void    checkPathValidity() const noexcept(false);

    private:
        //!
        //! @brief Create a new element according a xml document.
        //! @param xmlDocument A Document binds together all the functionality.
        //! @param elementName Name of the new element.
        //! @return Created element.
        //! @throw Throw a exception when the sub element can't be created.
        //!
        [[nodiscard]]
        tinyxml2::XMLElement    *newXMLElement(tinyxml2::XMLDocument *xmlDocument, const char *elementName) const noexcept(false);
        //!
        //! @brief Extract a sub element from a xml node.
        //! @param node Parent node.
        //! @param subNodeName Name of the sub node to extract.
        //! @return Extract element.
        //! @throw Throw a exception when the sub node can't be extracted.
        //!
        [[nodiscard]]
        tinyxml2::XMLElement    *getSubXMLElement(tinyxml2::XMLNode *node, const char *subNodeName) const noexcept(false);
        //!
        //! @brief Extract the body xml element from xml document class.
        //! @param xmlDocument Reference XML documentation (register).
        //! @return Body xml element.
        //! @throw Raise a exception if the file loading is impossible.
        //!
        [[nodiscard]]
        tinyxml2::XMLElement    *getBodyXMLElement(tinyxml2::XMLDocument &xmlDocument) const noexcept(false);

    private:
        //!
        //! @brief Save xml file with error handling.
        //! @param xmlDocument XML documentation to save.
        //! @throw Raise a exception if the file saving is impossible.
        //!
        void    saveXMLFile(tinyxml2::XMLDocument &xmlDocument) const noexcept(false);
        //!
        //! @brief Load xml file with error handling.
        //! @param xmlDocument XML documentation to load.
        //! @throw Raise a exception if the file loading is impossible.
        //!
        void    loadXMLFile(tinyxml2::XMLDocument &xmlDocument) const noexcept(false);

    private:
        //!
        //! @brief Create the header of the new target register.
        //! @param rights Register rights.
        //! @throw Raise a exception if the file saving is impossible.
        //!
        void    createHeader(const std::optional<jbr::reg::perm::Rights> &rights) const noexcept(false);

    private:
        //!
        //! @brief Write rights information's on register.
        //! @param reg XML document object.
        //! @param nodeHeader Header node from register.
        //! @param version Version node from register.
        //! @param rights Register rights.
        //! @warning This function must be call into a process, no check on pointers, object validity are done. File must be saved after call.
        //! @throw Exception raise if parameters are invalid.
        //!
        void    writeRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeHeader,
                            tinyxml2::XMLElement *version, const jbr::reg::perm::Rights &rights) const noexcept(false);
        //!
        //! @brief Write variable rights information's on register.
        //! @param reg XML document object.
        //! @param nodeBody Body node from register.
        //! @param variableValue Value node from register into variable main node.
        //! @param rights Register variable rights.
        //! @warning This function must be call into a process, no check on pointers, object validity are done. File must be saved after call.
        //! @throw Exception raise if parameters are invalid.
        //!
        void    writeRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeBody,
                                      tinyxml2::XMLElement *variableValue, const jbr::reg::var::perm::Rights &rights) const noexcept(false);
        //!
        //! @brief Update variable rights information's on register.
        //! @param reg XML document object.
        //! @param nodeBody Body node from register.
        //! @param variableValue Value node from register into variable main node.
        //! @param rights Register variable rights.
        //! @warning This function must be call into a process, no check on pointers, object validity are done. File must be saved after call.
        //! @throw Exception raise if parameters are invalid.
        //!
        void    updateRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeVariable,
                                       tinyxml2::XMLElement *variableValue, const jbr::reg::var::perm::Rights &rights) const noexcept(false);
        //!
        //! @brief Query a boolean into a xml element field.
        //! @param xmlElement XML element to insert the boolean.
        //! @param status Boolean to insert.
        //! @throw If the element is set and the query failed.
        //!
        void    queryRightToXMLElement(const tinyxml2::XMLElement *xmlElement, bool *status) const noexcept(false);
    };
}

#endif //JBR_CREGISTER_REGISTER_INSTANCE_HPP
