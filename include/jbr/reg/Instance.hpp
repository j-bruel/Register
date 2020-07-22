//!
//! @file Register.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_REGISTER_INSTANCE_HPP
# define JBR_CREGISTER_REGISTER_INSTANCE_HPP

# include <jbr/reg/Rights.hpp>
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
        explicit Instance(const char *path) : mPath(path) { checkPathValidity(); }
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
        //!
        //! @brief Check if a register is valid. The register is corrupt if the format is broken, missing mandatory field or wild characters.
        //! @param xmlDocument XML documentation to save.
        //! @warning This function does not need to be called after open function.
        //! @throw Raise if the register is invalid.
        //!
        void        verify(tinyxml2::XMLDocument &xmlDocument) const noexcept(false);
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
        //! @brief Extract register rights.
        //! @return Current register rights.
        //! @throw Raise if impossible to extract the data from the register.
        //!
        [[nodiscard]]
        jbr::reg::Rights    rights() const noexcept(false);
        //!
        //! @brief Check if a register is openable. The register is not openable if the fields read or open from register/header/rights nodes is false.
        //! @return Openable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        bool                isOpenable() const noexcept(false);
        //!
        //! @brief Check if a register is copyable. The register is not copyable if the fields read or copy from register/header/rights nodes is false.
        //! @return Copyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        bool                isCopyable() const noexcept(false);
        //!
        //! @brief Check if a register is movable. The register is not movable if the fields write, read or copy from register/header/rights nodes is false.
        //! @return Movable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        bool                isMovable() const noexcept(false);
        //!
        //! @brief Check if a register is destroyable. The register is not destroyable if the fields read or destroy from register/header/rights nodes is false.
        //! @return Destroyable status.
        //! @throw Raise if impossible to extract the rights data from the register.
        //!
        [[nodiscard]]
        bool                isDestroyable() const noexcept(false);

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
        void    createHeader(const std::optional<jbr::reg::Rights> &rights) const noexcept(false);

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
                            tinyxml2::XMLElement *version, const jbr::reg::Rights &rights) const noexcept(false);
        //!
        //! @brief Query a boolean into a xml element field.
        //! @param xmlElement XML element to insert the boolean.
        //! @param status Boolean to insert.
        //! @throw If the element is set and the query failed.
        //!
        void    queryRightToXMLElement(tinyxml2::XMLElement *xmlElement, bool *status) const noexcept(false);
    };
}

#endif //JBR_CREGISTER_REGISTER_INSTANCE_HPP
