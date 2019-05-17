//!
//! @file jbr/reg/HelloWorld.hpp
//! @author jbruel
//! @date 29/04/19
//!

#ifndef CREGISTER_JBR_REG_HELLO_WORLD_HPP
# define CREGISTER_JBR_REG_HELLO_WORLD_HPP

# include <string>

//!
//! @namespace jbr
//!
namespace jbr
{
//!
//! @namespace reg
//!
namespace reg
{

    //!
    //! @class HelloWorld
    //! @brief A useful class that contains utilities helpful to "Hello, World!" programs.
    //!
    class HelloWorld
    {
    private:
        std::string mHello; //!< My hello.
        std::string mWorld; //!< My world.

    public:
        //!
        //! @brief Constructor for HelloWorld class. Initializes class members hello_ and world_ with their respective values.
        //!
        HelloWorld();
        //!
        //! @brief Copy constructor.
        //! @warning Not used.
        //!
        HelloWorld(const HelloWorld &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @warning Not used.
        //!
        const HelloWorld    &operator=(const HelloWorld &) = delete;
        //!
        //! @brief Default destructor.
        //!
        ~HelloWorld() = default;

    public:
        //!
        //! @brief Get for member variable mHello.
        //! @return The mHello string.
        //!
        inline const std::string    &hello() const { return (mHello); }
        //!
        //! @brief Get for member variable mWorld.
        //! @return The mWorld string.
        //!
        inline const std::string     &world() const { return (mWorld); }
        //!
        //! @brief Generate a random number.
        //! @return The random number 4000.
        //!
        inline int                  generateRandomNumber() const { return (4'000); }
        //!
        //! @brief A function defined and implemented purely in the header file.
        //! @param number The original integer.
        //! @return divided by 2 using integer division if number is even; else return 3.
        //!
        int                         headerFunction(int number) const;
    };

}
}

#endif // !CREGISTER_JBR_REG_HELLO_WORLD_HPP
