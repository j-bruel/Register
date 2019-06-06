//!
//! @file register_open.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("Register::open")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.open("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To open a register the path must not be empty.");
    }

    SUBCASE("open one")
    {
        std::ofstream   reg("./ut_open_one_register");

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
        CHECK_NOTHROW(mRegister.open("./ut_open_one_register"));
        std::filesystem::remove("./ut_open_one_register");
    }

    SUBCASE("open few")
    {
        CHECK_NOTHROW(mRegister.create("./ut_open_1"));
        CHECK_NOTHROW(mRegister.create("../ut_open_2"));
        CHECK_NOTHROW(mRegister.create("ut_open_3"));
        std::filesystem::create_directory("./nextDirectory");
        CHECK_NOTHROW(mRegister.create("./nextDirectory/ut_open_4"));

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
        CHECK_NOTHROW(mRegister.open("./ut_open_1"));
        CHECK_NOTHROW(mRegister.open("../ut_open_2"));
        CHECK_NOTHROW(mRegister.open("ut_open_3"));
        CHECK_NOTHROW(mRegister.open("./nextDirectory/ut_open_4"));
        CHECK_NOTHROW(mRegister.open("./ut_open_5"));
        std::filesystem::remove("./ut_open_1");
        std::filesystem::remove("../ut_open_2");
        std::filesystem::remove("ut_open_3");
        std::filesystem::remove_all("./nextDirectory");
        std::filesystem::remove("./ut_open_5");
    }

    SUBCASE("not existing")
    {
        std::string msg;

        try {
            mRegister.open("./ut_not_exist");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_not_exist does not exist. You must create it before.");
    }

    SUBCASE("corrupt : random")
    {
        std::ofstream   reg("./ut_open_random");
        std::string     msg;

        reg << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        reg.close();
        try {
            mRegister.open("./ut_open_random");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./ut_open_random");
    }

    SUBCASE("corrupt : register node not found")
    {
        std::ofstream   reg("./ut_open_register_node_not_found");
        std::string     msg;

        reg << "<toto>\n"
               "</toto>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_register_node_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Did not find register node, the format is corrupt.");
        std::filesystem::remove("./ut_open_register_node_not_found");
    }

    SUBCASE("corrupt : header node not found")
    {
        std::ofstream   reg("./ut_open_header_node_not_found");
        std::string     msg;

        reg << "<register>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_header_node_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Did not find header node, the format is corrupt.");
        std::filesystem::remove("./ut_open_header_node_not_found");
    }

    SUBCASE("corrupt : version field not found")
    {
        std::ofstream   reg("./ut_open_version_field_not_found");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <rights>\n"
               "            <read>true</read>\n"
               "            <write>true</write>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_version_field_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
                CHECK(msg == "Register corrupted. Did not find version field from register/header nodes, mandatory field missing.");
        std::filesystem::remove("./ut_open_version_field_not_found");
    }

    SUBCASE("corrupt : rights node not found")
    {
        std::ofstream   reg("./ut_open_rights_node_not_found");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <version>1.0</version>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_rights_node_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Did not find rights node, the format is corrupt.");
        std::filesystem::remove("./ut_open_rights_node_not_found");
    }

    SUBCASE("corrupt : read field not found")
    {
        std::ofstream   reg("./ut_open_read_field_not_found");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <version>1.0</version>\n"
               "        <rights>\n"
               "            <write>true</write>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_read_field_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Did not find read field from register/header/rights nodes, mandatory field missing.");
        std::filesystem::remove("./ut_open_read_field_not_found");
    }

    SUBCASE("corrupt : read field missing")
    {
        std::ofstream   reg("./ut_open_read_field_missing");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <version>1.0</version>\n"
               "        <rights>\n"
               "            <read></read>\n"
               "            <write>true</write>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_read_field_missing");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
                CHECK(msg == "Register corrupted. Field read from register/header/rights nodes not set or invalid, error code : 17.");
        std::filesystem::remove("./ut_open_read_field_missing");
    }

    SUBCASE("corrupt : read field invalid")
    {
        std::ofstream   reg("./ut_open_read_field_invliad");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <version>1.0</version>\n"
               "        <rights>\n"
               "            <read>dsfdff</read>\n"
               "            <write>0</write>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_read_field_invliad");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Field read from register/header/rights nodes not set or invalid, error code : 16.");
        std::filesystem::remove("./ut_open_read_field_invliad");
    }

    SUBCASE("corrupt : write field not found")
    {
        std::ofstream   reg("./ut_open_write_field_not_found");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <version>1.0</version>\n"
               "        <rights>\n"
               "            <read>true</read>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_write_field_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Did not find write field from register/header/rights nodes, mandatory field missing.");
        std::filesystem::remove("./ut_open_write_field_not_found");
    }

    SUBCASE("corrupt : write field missing")
    {
        std::ofstream   reg("./ut_open_write_field_missing");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <version>1.0</version>\n"
               "        <rights>\n"
               "            <read>true</read>\n"
               "            <write></write>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_write_field_missing");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Field write from register/header/rights nodes not set or invalid, error code : 17.");
        std::filesystem::remove("./ut_open_write_field_missing");
    }

    SUBCASE("corrupt : write field invalid")
    {
        std::ofstream   reg("./ut_open_write_field_invalid");
        std::string     msg;

        reg << "<register>\n"
               "    <header>\n"
               "        <version>1.0</version>\n"
               "        <rights>\n"
               "            <read>1</read>\n"
               "            <write>dfqsdfsqd</write>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "    </body>\n"
               "</register>\n";
        reg.close();
        try {
            mRegister.open("./ut_open_write_field_invalid");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
                CHECK(msg == "Register corrupted. Field write from register/header/rights nodes not set or invalid, error code : 16.");
        std::filesystem::remove("./ut_open_write_field_invalid");
    }

}
