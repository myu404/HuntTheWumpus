#pragma once

#include "TestHelperGameState.h"
#include "TestHelperRandomProvider.h"
#include "TestHelperDungeon.h"
#include "UserNotification.h"

#include "Context.h"

namespace TestHuntTheWumpus
{
    struct TestEnvironment
    {
        TestEnvironment();

        TestRandomProvider m_provider;
        HuntTheWumpus::UserNotification m_notifier;
        TestGameState m_state;

        HuntTheWumpus::Context m_context { m_notifier, m_provider, m_state };

        TestDungeon m_dungeon;
    };
}