//!
//! @file isCopyable_test.cpp
//! @author jbruel
//! @date 23/07/20
//!

#include <jbr/Register.hpp>
#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("jbr::reg::Instance::isCopyable")
{

    SUBCASE("Valid copyable register.")
    {
        jbr::Register reg = jbr::reg::Manager::create("./valid_copyable.reg");

        CHECK(reg->isCopyable());
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Not copyable register.")
    {
        jbr::Register       reg1 = jbr::reg::Manager::create("./valid_not_copyable1.reg", jbr::reg::Rights(true, true, true, false, true, true));
        jbr::Register       reg2 = jbr::reg::Manager::create("./valid_not_copyable2.reg", jbr::reg::Rights(false, true, true, true, true, true));

        CHECK(!reg1->isCopyable());
        CHECK(!reg2->isCopyable());
        jbr::reg::Manager::destroy(reg1);
        std::filesystem::remove("./valid_not_copyable2.reg");
    }

    SUBCASE("Invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_copyable.reg");
        std::ofstream   regInvalid("./invalid_copyable.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            (void)reg->isCopyable();
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_copyable.reg");
    }

}
