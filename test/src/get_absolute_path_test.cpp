//!
//! @file get_absolute_path.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/reg/GetAbsolutePath.hpp>
#include <doctest.h>
#include <iostream>
#include <string>
#include <filesystem>

TEST_CASE("GetAbsolutePath")
{
    //!
    //! @test Extract full path from a simple next directory on current directory.
    //!
    SUBCASE("Get next directory")
    {
        CHECK(std::filesystem::current_path().string() + "/./nextDirectory/" == jbr::reg::getAbsolutePath("./nextDirectory/"));
        CHECK(std::filesystem::current_path().string() + "/nextDirectory/" == jbr::reg::getAbsolutePath("nextDirectory/"));
    }

    //!
    //! @test Extract full path from current directory.
    //!
    SUBCASE("Get current directory")
    {
        CHECK((std::filesystem::current_path().string() + "/./") == jbr::reg::getAbsolutePath("./"));
        CHECK((std::filesystem::current_path().string() + "/.") == jbr::reg::getAbsolutePath("."));
        CHECK((std::filesystem::current_path().string() + "/.//") == jbr::reg::getAbsolutePath(".//"));
    }

    //!
    //! @test Extract full path with back directory ("..").
    //!
    SUBCASE("Get back directory")
    {
        CHECK(std::filesystem::current_path().string() + "/.." == jbr::reg::getAbsolutePath(".."));
    }

    //!
    //! @test Empty path, exception should be raise.
    //!
    SUBCASE("Use empty input path")
    {
        CHECK_THROWS(jbr::reg::getAbsolutePath(""));
    }

    //!
    //! @test Path already absolute.
    //!
    SUBCASE("Already absolute")
    {
        CHECK(std::filesystem::current_path().string() == jbr::reg::getAbsolutePath(std::filesystem::current_path().string()));
    }

    //!
    //! @test Random characters.
    //!
    SUBCASE("Random characters")
    {
        CHECK((std::filesystem::current_path().string() + "/sdofuhoodfijdofhdiofjspdvbyz7687908754 7S897D 67D7 87987SQQ5 8°ù£% ° 3°EP 20 9682568 3PM udgfho ajré_yc ") == jbr::reg::getAbsolutePath("sdofuhoodfijdofhdiofjspdvbyz7687908754 7S897D 67D7 87987SQQ5 8°ù£% ° 3°EP 20 9682568 3PM udgfho ajré_yc "));
        CHECK((std::filesystem::current_path().string() + "/IHD/egdèrR5662ç///éùếp')//°-'_èçjHGFDRgh/") == jbr::reg::getAbsolutePath("IHD/egdèrR5662ç///éùếp')//°-'_èçjHGFDRgh/"));
        CHECK(("/IHD/egdèrR5662ç///éùếp')//°-'_èçjHGFDRgh/") == jbr::reg::getAbsolutePath("/IHD/egdèrR5662ç///éùếp')//°-'_èçjHGFDRgh/"));
    }

}
