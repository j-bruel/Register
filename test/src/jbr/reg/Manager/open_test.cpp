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

    SUBCASE("Open a corrupted register with 'version' field not found.")
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
            (void)jbr::reg::Manager::open("./ut_open_version_field_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Error while extract the sub node, the result is null. The sub node version does not exist.");
        std::filesystem::remove("./ut_open_version_field_not_found");
    }

    SUBCASE("Open a corrupted register with 'version' field not set.")
    {
        std::ofstream   reg("./ut_open_version_field_not_set");
        std::string     msg;

        reg << "<register>\n"
        "    <header>\n"
        "        <version></version>\n"
        "        <rights>\n"
        "            <read>1</read>\n"
        "            <write>0</write>\n"
        "        </rights>\n"
        "    </header>\n"
        "    <body>\n"
        "    </body>\n"
        "</register>\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_version_field_not_set");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Field version from register/header nodes not set or invalid.");
        std::filesystem::remove("./ut_open_version_field_not_set");
    }

    SUBCASE("Open a register with 'right' node not set.")
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
            (void)jbr::reg::Manager::open("./ut_open_rights_node_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg.empty());
        std::filesystem::remove("./ut_open_rights_node_not_found");
    }

    SUBCASE("Open a register with 'right/read' node not set.")
    {
        std::ofstream   reg("./ut_open_read_field_not_found");
        std::string     msg;

        reg << "<register>\n"
        "    <header>\n"
        "        <version>1.0.0</version>\n"
        "        <rights>\n"
        "            <write>true</write>\n"
        "        </rights>\n"
        "    </header>\n"
        "    <body>\n"
        "    </body>\n"
        "</register>\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_read_field_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg.empty());
        std::filesystem::remove("./ut_open_read_field_not_found");
    }

    SUBCASE("Open a corrupted register with 'right/read' field missing.")
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
            (void)jbr::reg::Manager::open("./ut_open_read_field_missing");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Field read from register/header/rights nodes is invalid, error code : 17.");
        std::filesystem::remove("./ut_open_read_field_missing");
    }

    SUBCASE("Open a corrupted register with 'right/read' invalid field.")
    {
        std::ofstream   reg("./ut_open_read_field_invalid");
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
            (void)jbr::reg::Manager::open("./ut_open_read_field_invalid");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Field read from register/header/rights nodes is invalid, error code : 16.");
        std::filesystem::remove("./ut_open_read_field_invalid");
    }

    SUBCASE("Open a register with 'right/write' field not found.")
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
            (void)jbr::reg::Manager::open("./ut_open_write_field_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg.empty());
        std::filesystem::remove("./ut_open_write_field_not_found");
    }

    SUBCASE("Open a corrupted register with 'right/write' field missing.")
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
            (void)jbr::reg::Manager::open("./ut_open_write_field_missing");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Field write from register/header/rights nodes is invalid, error code : 17.");
        std::filesystem::remove("./ut_open_write_field_missing");
    }

    SUBCASE("Open a corrupted register with 'right/write' invalid field.")
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
            (void)jbr::reg::Manager::open("./ut_open_write_field_invalid");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register corrupted. Field write from register/header/rights nodes is invalid, error code : 16.");
        std::filesystem::remove("./ut_open_write_field_invalid");
    }

    SUBCASE("Open a corrupted register with 'body' node not found.")
    {
        std::ofstream   reg("./ut_open_body_node_not_found");
        std::string     msg;

        reg << "<register>\n"
        "    <header>\n"
        "        <version>1.0</version>\n"
        "        <rights>\n"
        "            <read>1</read>\n"
        "            <write>true</write>\n"
        "        </rights>\n"
        "    </header>\n"
        "</register>\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_body_node_not_found");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Error while extract the sub node, the result is null. The sub node body does not exist.");
        std::filesystem::remove("./ut_open_body_node_not_found");
    }

    SUBCASE("Open a register without the reading right.")
    {
        std::ofstream   reg("./ut_open_no_read_right_register");
        std::string     msg;

        reg << "<register>\n"
        "    <header>\n"
        "        <version>1.0</version>\n"
        "        <rights>\n"
        "            <read>false</read>\n"
        "            <write>true</write>\n"
        "        </rights>\n"
        "    </header>\n"
        "    <body>\n"
        "    </body>\n"
        "</register>\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_no_read_right_register");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_open_no_read_right_register is not openable. Please check the register rights, read and open must be allowed.");
        std::filesystem::remove("./ut_open_no_read_right_register");
    }

    SUBCASE("Open a register without the right to open it.")
    {
        std::ofstream   reg("./ut_open_no_open_right_register");
        std::string     msg;

        reg << "<register>\n"
        "    <header>\n"
        "        <version>1.0</version>\n"
        "        <rights>\n"
        "            <read>true</read>\n"
        "            <write>true</write>\n"
        "            <open>false</open>\n"
        "        </rights>\n"
        "    </header>\n"
        "    <body>\n"
        "    </body>\n"
        "</register>\n";
        reg.close();
        try {
            (void)jbr::reg::Manager::open("./ut_open_no_open_right_register");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_open_no_open_right_register is not openable. Please check the register rights, read and open must be allowed.");
        std::filesystem::remove("./ut_open_no_open_right_register");
    }

    SUBCASE("Open a register with read, write and open rights correctly set to true.")
    {
        std::ofstream   reg("./ut_open_full_right_set_register");
        std::string     msg;

        reg << "<register>\n"
        "    <header>\n"
        "        <version>1.0</version>\n"
        "        <rights>\n"
        "            <read>true</read>\n"
        "            <write>true</write>\n"
        "            <open>true</open>\n"
        "            <copy>false</copy>\n"
        "            <move>false</move>\n"
        "            <destroy>false</destroy>\n"
        "        </rights>\n"
        "    </header>\n"
        "    <body>\n"
        "    </body>\n"
        "</register>\n";
        reg.close();
        CHECK_NOTHROW((void)jbr::reg::Manager::open("./ut_open_full_right_set_register"));
        std::filesystem::remove("./ut_open_full_right_set_register");
    }

}
