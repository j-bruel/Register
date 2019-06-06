//!
//! @file exist_create.cpp
//! @author jbruel
//! @date 05/06/19
//!

#include <jbr/Register.hpp>
#include <doctest.h>
#include <iostream>
#include <string>

TEST_CASE("Register::exist")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        CHECK(!mRegister.exist(""));
    }

    SUBCASE("exist")
    {
        mRegister.create("./exist");
        CHECK(mRegister.exist("./exist"));
        std::filesystem::remove("./exist");
    }

    SUBCASE("not exist")
    {
        CHECK(!mRegister.exist("./not_exist"));
    }

}
