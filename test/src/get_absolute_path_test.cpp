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
        std::filesystem::create_directory("./nextDirectory");
        CHECK(std::filesystem::current_path().string() + std::filesystem::path("/nextDirectory").make_preferred().string() == jbr::reg::getAbsolutePath("./nextDirectory/"));
        CHECK(std::filesystem::current_path().string() + std::filesystem::path("/nextDirectory").make_preferred().string() == jbr::reg::getAbsolutePath("nextDirectory/"));
        std::filesystem::remove_all("./nextDirectory");
    }

    //!
    //! @test Extract full path from current directory.
    //!
    SUBCASE("Get current directory")
    {
        CHECK(std::filesystem::current_path().string() == jbr::reg::getAbsolutePath("./"));
        CHECK(std::filesystem::current_path().string() == jbr::reg::getAbsolutePath("."));
        CHECK(std::filesystem::current_path().string() == jbr::reg::getAbsolutePath(".//"));
    }

    //!
    //! @test Extract full path with back directory ("..").
    //!
    SUBCASE("Get back directory")
    {
        CHECK(std::filesystem::canonical(std::filesystem::path("..")) == jbr::reg::getAbsolutePath(".."));
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
    //! @test Random characters. Throw on windows and not linux.
    //!
    SUBCASE("Random characters")
    {
        CHECK_THROWS(jbr::reg::getAbsolutePath("sdofuhoodfijdofhdiofjspdvbyz7687908754 7S897D 67D7 87987SQQ5 8°ù£% ° 3°EP 20 9682568 3PM udgfho ajré_yc "));
        CHECK_THROWS(jbr::reg::getAbsolutePath("IHD/egdèrR5662ç///éùếp')//°-'_èçjHGFDRgh/"));
        CHECK_THROWS(jbr::reg::getAbsolutePath("/IHD/egdèrR5662ç///éùếp')//°-'_èçjHGFDRgh/"));
    }

}
