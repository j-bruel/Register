//!
//! @file Variable.hpp
//! @author jbruel
//! @date 07/06/19
//!

#ifndef JBR_CREGISTER_REGISTER_VARIABLE_HPP
# define JBR_CREGISTER_REGISTER_VARIABLE_HPP

# include <string>
# include <jbr/Register.hpp>

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{

    //!
    //! @class Variable
    //! @brief Unique register variable.
    //!
    class Variable : private jbr::Register
    {
    private:
        std::string mPath; //!< Register path handle for this variable.

    public:
        //!
        //! @brief Register variable constructor.
        //! @warning Not usable.
        //!
        Variable() = delete;
        //!
        //! @brief Register variable constructor with register owner path.
        //! @param registerPath Owner register path.
        //!
        explicit Variable(const std::string &registerPath);
        //!
        //! @brief Copy constructor
        //! @warning Not usable.
        //!
        Variable(const Variable &) = delete;
        //!
        //! @brief Equal overload operator.
        //! @warning Not usable.
        //!
        Variable    &operator=(const Variable &) = delete;
        //!
        //! @brief Register variable class destructor.
        //!
        ~Variable() = default;

    public:
        //!
        //! @brief Set (create or update) a variable from the current target register.
        //! @param key Target key to create or update.
        //! @param value Value link to the key.
        //!
        void        set(const std::string &key, const std::string &value);
        //!
        //! @brief Extract a variable from the target register.
        //! @param key Key to extract.
        //! @return Value link to the key extracted.
        //!
        std::string get(const std::string &key);
        //!
        //! @brief Remove a key from the target register.
        //! @param key Key to extract.
        //!
        void        remove(const std::string &key);
        //!
        //! @brief Check if a key exist on the target register.
        //! @param key Key to check.
        //! @return Key status, true if exist.
        //!
        bool        available(const std::string &key);

    };
}

#endif //JBR_CREGISTER_REGISTER_VARIABLE_HPP
