#include "UserNotification.h"
#include <iostream>

namespace HuntTheWumpus
{
    std::ostream& operator<<(std::ostream& out, const UserNotification::Notification& value)
    {
        static std::unordered_map<UserNotification::Notification, std::string> s_valueMap =
        {
            {UserNotification::Notification::ObserveWumpus, "ObserveWumpus"},
            {UserNotification::Notification::ObservePit, "ObservePit"},
            {UserNotification::Notification::ObserveBat, "ObserveBat"},
            {UserNotification::Notification::ObserveMiss, "ObserveMiss"},
            {UserNotification::Notification::ObserveOutOfArrows, "ObserveOutOfArrows"},
            {UserNotification::Notification::BatTriggered, "BatTriggered"},
            {UserNotification::Notification::PitTriggered, "PitTriggered"},
            {UserNotification::Notification::WumpusTriggered, "WumpusTriggered"},
            {UserNotification::Notification::WumpusAwoken, "WumpusAwoken"},
            {UserNotification::Notification::WumpusShot, "WumpusShot"},
            {UserNotification::Notification::HunterEaten, "HunterEaten"},
            {UserNotification::Notification::HunterShot, "HunterShot"},
            {UserNotification::Notification::CaveEntered, "CaveEntered"},
            {UserNotification::Notification::NeighboringCaves, "NeighboringCaves"},
            {UserNotification::Notification::ReportIllegalMove, "ReportIllegalMove"}
        };

        out << s_valueMap[value];
        return out;
    }

    void UserNotification::AddCallback(const Notification category, std::function<void()>&& callback)
    {
        m_callbacks.insert_or_assign(category, std::move(callback));
    }

    void UserNotification::AddCallback(const Notification category, std::function<void(int)>&& callback)
    {
        m_callbacks.insert_or_assign(category, std::move(callback));
    }

    void UserNotification::AddCallback(const Notification category, std::function<void(const std::vector<int>&)>&& callback)
    {
        m_callbacks.insert_or_assign(category, std::move(callback));
    }

    void UserNotification::Notify(const Notification category) const
    {
        const auto callback = m_callbacks.find(category);

        const auto* callbackFunc = std::get_if<std::function<void()>>(&callback->second);

        try
        {
            (*callbackFunc)();
        }
        catch (const std::bad_function_call& e)
        {
            std::cout << e.what() << ". The following callback is missing from UserNotification: " << callback->first << std::endl;
        }
        
    }

    template<typename Callback, typename CallbackArg> void DoCallback(const std::unordered_map<UserNotification::Notification, UserNotification::CallbackData>& callbacks, const UserNotification::Notification callbackId, const CallbackArg& arg)
    {
        const auto callback = callbacks.find(callbackId);

        const auto* callbackFunc = std::get_if<Callback>(&callback->second);

        try
        {
            (*callbackFunc)(arg);
        }
        catch (const std::bad_function_call& e)
        {
            std::cout << e.what() << ". The following callback is missing from UserNotification: " << callback->first << std::endl;
        }
    }

    void UserNotification::Notify(const Notification category, const int arg) const
    {
        DoCallback<std::function<void(int)>, int>(m_callbacks, category, arg);
    }

    void UserNotification::Notify(const Notification category, const std::vector<int>& arg) const
    {
        DoCallback<std::function<void(const std::vector<int> &)>, std::vector<int>>(m_callbacks, category, arg);
    }



}
