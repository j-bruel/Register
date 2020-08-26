//!
//! @file set_test.cpp
//! @author jbruel
//! @date 25/08/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("jbr::reg::Instance::set")
{

    SUBCASE("Basic set.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_set.reg");

        reg->set(jbr::reg::Variable("Basic set", "Basic value"));

        std::ifstream   ifs("basic_set.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
                         "    <header>\n"
                         "        <version>1.0.0</version>\n"
                         "    </header>\n"
                         "    <body>\n"
                         "        <variable>\n"
                         "            <key>Basic set</key>\n"
                         "            <value>Basic value</value>\n"
                         "        </variable>\n"
                         "    </body>\n"
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Multiple set.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./multiple_sets.reg");

        reg->set(jbr::reg::Variable("Basic set", "Basic value"));
        reg->set(jbr::reg::Variable("Multiple set", "Basic values"));
        reg->set(jbr::reg::Variable("Some var ...", ""));
        reg->set(jbr::reg::Variable("ut", "Basic value"));
        reg->set(jbr::reg::Variable(" sjdo dij idj d dd    ", "   ::  - (r ybh n n   d"));

        std::ifstream   ifs("multiple_sets.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
                         "    <header>\n"
                         "        <version>1.0.0</version>\n"
                         "    </header>\n"
                         "    <body>\n"
                         "        <variable>\n"
                         "            <key> sjdo dij idj d dd    </key>\n"
                         "            <value>   ::  - (r ybh n n   d</value>\n"
                         "        </variable>\n"
                         "        <variable>\n"
                         "            <key>ut</key>\n"
                         "            <value>Basic value</value>\n"
                         "        </variable>\n"
                         "        <variable>\n"
                         "            <key>Some var ...</key>\n"
                         "            <value/>\n"
                         "        </variable>\n"
                         "        <variable>\n"
                         "            <key>Multiple set</key>\n"
                         "            <value>Basic values</value>\n"
                         "        </variable>\n"
                         "        <variable>\n"
                         "            <key>Basic set</key>\n"
                         "            <value>Basic value</value>\n"
                         "        </variable>\n"
                         "    </body>\n"
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Set with a replace.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./replace.reg");

        reg->set(jbr::reg::Variable("Basic set", "Basic value"));
        reg->set(jbr::reg::Variable("Basic set", "New value"));
        reg->set(jbr::reg::Variable("Multiple set", "Basic values"));
        reg->set(jbr::reg::Variable("Basic set", "Hey !"));
        reg->set(jbr::reg::Variable("Some var ...", ""));
        reg->set(jbr::reg::Variable("Basic set", "Finally ..."));

        std::ifstream   ifs("replace.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
                         "    <header>\n"
                         "        <version>1.0.0</version>\n"
                         "    </header>\n"
                         "    <body>\n"
                         "        <variable>\n"
                         "            <key>Some var ...</key>\n"
                         "            <value/>\n"
                         "        </variable>\n"
                         "        <variable>\n"
                         "            <key>Multiple set</key>\n"
                         "            <value>Basic values</value>\n"
                         "        </variable>\n"
                         "        <variable>\n"
                         "            <key>Basic set</key>\n"
                         "            <value>Finally ...</value>\n"
                         "        </variable>\n"
                         "    </body>\n"
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Set with a replace (no replace rights).")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./replace_not_allow.reg");
        std::string     msg;

        reg->set(jbr::reg::Variable("Basic set", "Basic value"));
        try {
            reg->set(jbr::reg::Variable("Basic set", "New value"), false);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Cannot replace the already existing variable 'New value' from ./replace_not_allow.reg register.");

        std::ifstream   ifs("replace_not_allow.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
                         "    <header>\n"
                         "        <version>1.0.0</version>\n"
                         "    </header>\n"
                         "    <body>\n"
                         "        <variable>\n"
                         "            <key>Basic set</key>\n"
                         "            <value>Basic value</value>\n"
                         "        </variable>\n"
                         "    </body>\n"
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_set.reg");
        std::ofstream   regInvalid("./invalid_set.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            reg->set(jbr::reg::Variable("Basic set", "Basic value"));
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_set.reg");
    }


}
