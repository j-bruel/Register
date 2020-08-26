//!
//! @file get_test.cpp
//! @author jbruel
//! @date 25/08/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>

TEST_CASE("jbr::reg::Instance::get")
{

    SUBCASE("Basic get variable (only one variable exist).")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_get.reg");

//        reg->set(jbr::reg::Variable("basic_get", "value"));
//        CHECK(std::string(reg->get("basic_get").read()) == "value");
        jbr::reg::Manager::destroy(reg);
    }

}
