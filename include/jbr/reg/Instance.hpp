//!
//! @file Register.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_REGISTER_INSTANCE_HPP
# define JBR_CREGISTER_REGISTER_INSTANCE_HPP

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
        //! @brief Extract the register localization.
        //! @return Register location.
        //!
        [[nodiscard]]
        const std::string   &localization() const noexcept { return (mPath); }

    private:
        //!
        //! @brief Check if the register path is valid.
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
        //! @brief Save xml file with error handling.
        //! @param xmlDocument XML documentation to save.
        //! @throw Raise a exception if the file saving is impossible.
        //!
        void    saveXMLFile(tinyxml2::XMLDocument &xmlDocument) const noexcept(false);

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
    };
}

#endif //JBR_CREGISTER_REGISTER_INSTANCE_HPP
