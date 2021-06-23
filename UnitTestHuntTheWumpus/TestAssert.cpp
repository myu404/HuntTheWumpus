/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

#include <TestHarness.h>

#include "CustomAssert.h"

namespace TestHuntTheWumpus
{
    TEST(CustomAssertSuite, True_NoExceptionThrown)
    {
        bool expectedException = false;

        try
        {
            std::string text = "HuntTheWumpus";
            HuntTheWumpus::assert(text == "HuntTheWumpus", __FILE__, __LINE__);
        }
        catch (const std::runtime_error&)
        {
            expectedException = true;
        }

        CHECK(!expectedException);
    }

    TEST(CustomAssertSuite, False_ExceptionThrown)
    {
        bool expectedException = false;

        try
        {
            std::string text = "HuntTheHunter";
            HuntTheWumpus::assert(text == "HuntTheWumpus", __FILE__, __LINE__);
        }
        catch (const std::runtime_error&)
        {
            expectedException = true;
        }

        CHECK(expectedException);
    }
}