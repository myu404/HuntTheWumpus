#include "TestHelperTestEnvironment.h"

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
}