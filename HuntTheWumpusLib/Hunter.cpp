#include "Hunter.h"

#include "Arrow.h"

#include "Cave.h"
#include "Context.h"
#include "UserNotification.h"
#include "GameStateObservation.h"

namespace HuntTheWumpus
{
    Hunter::Hunter(Context& providers)
        : Denizen({ Category::Hunter, 0 }, { true, false, false, true, true }, providers)
    {
        for (auto arrowIdx = 0; arrowIdx < 5; ++arrowIdx)
        {
            m_arrows.emplace_back(std::make_shared<Arrow>(arrowIdx, providers));
        }
    }

    void Hunter::EnterCave(const std::shared_ptr<Cave>& cave)
    {
        Denizen::EnterCave(cave);

        m_providers.m_notification.Notify(UserNotification::Notification::CaveEntered, cave->GetCaveId());

        const auto neighbors = cave->GetConnectedIds();

        m_providers.m_notification.Notify(UserNotification::Notification::NeighboringCaves, neighbors);
    }

    std::shared_ptr<Arrow> Hunter::GetArrow()
    {
        auto result = m_arrows.back();
        m_arrows.pop_back();

        return result;
    }

    bool Hunter::ObserveCaveEntrance(const std::shared_ptr<Denizen>& trigger)
    {
        if (trigger->Properties().m_fatalToHunter)
        {
            if (trigger->Properties().m_fatalToWumpus)
            {
                // This is an arrow, as those are fatal to both.
                m_providers.m_notification.Notify(UserNotification::Notification::HunterShot);
            }
            else
            {
                // This is the Wumpus entering.
                m_providers.m_notification.Notify(UserNotification::Notification::HunterEaten);
            }

            m_providers.m_change.GameOver(false);

            return true;
        }

        return false;
    }

}