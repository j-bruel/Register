//!
//! @file register_validity.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>

TEST_CASE("Register::verify")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.verify("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To check if a register is corrupt the path must not be empty.");
    }

    SUBCASE("not existing")
    {
        std::string msg;

        try {
            mRegister.verify("./ut_not_exist");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to check the corruption status of a not existing register : ./ut_not_exist.");
    }

    /**
    * All usecase on validity function are done into the open function.
    */

}

/**

 #include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>


 TEST_CASE("Register::verify")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.verify("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To check if a register is corrupt the path must not be empty.");
    }

    SUBCASE("not existing")
    {
        std::string msg;

        try {
            mRegister.verify("./ut_not_exist");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to check the corruption status of a not existing register : ./ut_not_exist.");
    }
*/
    /**
     * All usecase on validity function are done into the open function.
     */
/*
}
*/