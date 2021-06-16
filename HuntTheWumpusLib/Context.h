#pragma once

namespace HuntTheWumpus
{
    class UserNotification;
    class IRandomProvider;
    class IGameStateChange;

    struct Context
    {
        UserNotification &m_notification;
        IRandomProvider &m_random;
        IGameStateChange &m_change;
    };
}