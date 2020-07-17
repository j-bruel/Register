//!
//! @file open_test.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>


TEST_CASE("jbr::reg::Manager::open")
{

    SUBCASE("Open a register with a empty path.")
    {
        std::string msg;

        try {
            (void)jbr::reg::Manager::open("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To open a register the path must not be empty.");
    }

    SUBCASE("Basic register open on current directory.")
    {
        std::ofstream   reg("./ut_open_one_register");

        reg << "<register>\n"
        "    <header>\n"
        "        <version>1.0.0</version>\n"
        "        <rights>\n"
        "            <read>true</read>\n"
        "            <write>true</write>\n"
        "        </rights>\n"
        "    </header>\n"
        "    <body>\n"
        "    </body>\n"
        "</register>\n";
        reg.close();
        CHECK_NOTHROW((void)jbr::reg::Manager::open("./ut_open_one_register"));
        std::filesystem::remove("./ut_open_one_register");
    }

    SUBCASE("Open few register in same scope.")
    {
        CHECK_NOTHROW((void)jbr::reg::Manager::create("./ut_open_1"));
        CHECK_NOTHROW((void)jbr::reg::Manager::create("../ut_open_2"));
        CHECK_NOTHROW((void)jbr::reg::Manager::create("ut_open_3"));
        std::filesystem::create_directory("./nextDirectory");
        CHECK_NOTHROW((void)jbr::reg::Manager::create("./nextDirectory/ut_open_4"));

        std::ofstream   reg("./ut_open_5");

        reg << "<register>\n"
        "    <header>\n"
        "        <version>1.0</version>\n"
        "        <rights>\n"
        "            <read>true</read>\n"
        "            <write>true</write>\n"
        "        </rights>\n"
        "    </header>\n"
        "    <body>\n"
        "    </body>\n"
        "</register>\n";
        reg.close();
        CHECK_NOTHROW((void)jbr::reg::Manager::open("./ut_open_1"));
        CHECK_NOTHROW((void)jbr::reg::Manager::open("../ut_open_2"));
        CHECK_NOTHROW((void)jbr::reg::Manager::open("ut_open_3"));
        CHECK_NOTHROW((void)jbr::reg::Manager::open("./nextDirectory/ut_open_4"));
        CHECK_NOTHROW((void)jbr::reg::Manager::open("./ut_open_5"));
        std::filesystem::remove("./ut_open_1");
        std::filesystem::remove("../ut_open_2");
        std::filesystem::remove("ut_open_3");
        std::filesystem::remove_all("./nextDirectory");
        std::filesystem::remove("./ut_open_5");
    }

    SUBCASE("Open a not existing register.")
    {
        std::string msg;

        try {
            (void)jbr::reg::Manager::open("./ut_not_exist");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_not_exist does not exist. You must create it before.");
    }

    SUBCASE("Open a corrupted register with random data into it.")
    {
        std::ofstream   reg("./ut_open_random");
        std::string     msg;

        reg << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_random");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./ut_open_random");
    }

    SUBCASE("Open a corrupted register with 'register' node not found.")
    {
        std::ofstream   reg("./ut_open_register_node_not_found");
        std::string     msg;

        reg << "<toto>\n"
        "</toto>\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_register_node_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Error while extract the sub node, the result is null. The sub node register does not exist.");
        std::filesystem::remove("./ut_open_register_node_not_found");
    }

    SUBCASE("Open a corrupted register with 'header' node not found.")
    {
        std::ofstream   reg("./ut_open_header_node_not_found");
        std::string     msg;

        reg << "<register>\n"
        "</register>\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_header_node_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Error while extract the sub node, the result is null. The sub node header does not exist.");
        std::filesystem::remove("./ut_open_header_node_not_found");
    }

}
