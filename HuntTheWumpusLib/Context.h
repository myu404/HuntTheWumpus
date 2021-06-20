/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

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