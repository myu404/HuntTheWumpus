/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

#include "TestHelperTestEnvironment.h"
#include <TestHarness.h>

namespace TestHuntTheWumpus
{
    TestEnvironment::TestEnvironment()
    {
        // Add in default notifications
        m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::CaveEntered, [](const int) {});
        m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::NeighboringCaves, [](const std::vector<int>&) {});
        m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveBat, [&] {});
        m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObservePit, [&] {});
        m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveWumpus, [&] {});
        m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveMiss, [&]() { });
        m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::WumpusAwoken, [&] { });
    }

    TEST(TestHelperenvironmentSuite, UserNotification_ExceptionHandling_Parameterless_MissingNotification)
    {
        TestEnvironment env;
        bool expectedException = false;
        bool notExpectedException = false;

        try
        {
            env.m_notifier.Notify(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove);
        }
        catch (const std::out_of_range&)
        {
            expectedException = true;
        }
        catch (const std::bad_function_call&)
        {
            notExpectedException = true;
        }

        CHECK(expectedException);

        CHECK(!notExpectedException);
    }

    TEST(TestHelperenvironmentSuite, UserNotification_ExceptionHandling_Parameterless_WrongFunctionCallSignature)
    {
        TestEnvironment env;
        bool expectedException = false;
        bool notExpectedException = false;

        env.m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, [](const int) {});

        try
        {
            env.m_notifier.Notify(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove);
        }
        catch (const std::out_of_range&)
        {
            notExpectedException = true;
        }
        catch (const std::bad_function_call&)
        {
            expectedException = true;
        }

        CHECK(expectedException);

        CHECK(!notExpectedException);
    }

    TEST(TestHelperenvironmentSuite, UserNotification_ExceptionHandling_SingleParameter_MissingNotification)
    {
        TestEnvironment env;
        bool expectedException = false;
        bool notExpectedException = false;

        try
        {
            env.m_notifier.Notify(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, 1);
        }
        catch (const std::out_of_range&)
        {
            expectedException = true;
        }
        catch (const std::bad_function_call&)
        {
            notExpectedException = true;
        }

        CHECK(expectedException);

        CHECK(!notExpectedException);
    }

    TEST(TestHelperenvironmentSuite, UserNotification_ExceptionHandling_SingleParameterInt_WrongFunctionCallSignature)
    {
        TestEnvironment env;
        bool expectedException = false;
        bool notExpectedException = false;

        env.m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, [](const std::vector<int>&) {});

        try
        {
            env.m_notifier.Notify(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, 1);
        }
        catch (const std::out_of_range&)
        {
            notExpectedException = true;
        }
        catch (const std::bad_function_call&)
        {
            expectedException = true;
        }

        CHECK(expectedException);

        CHECK(!notExpectedException);
    }

    TEST(TestHelperenvironmentSuite, UserNotification_ExceptionHandling_SingleParameterVector_WrongFunctionCallSignature)
    {
        TestEnvironment env;
        bool expectedException = false;
        bool notExpectedException = false;

        env.m_notifier.AddCallback(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, [](const int) {});

        try
        {
            env.m_notifier.Notify(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, { 1, 2 });
        }
        catch (const std::out_of_range&)
        {
            notExpectedException = true;
        }
        catch (const std::bad_function_call&)
        {
            expectedException = true;
        }

        CHECK(expectedException);

        CHECK(!notExpectedException);
    }
}