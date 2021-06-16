#pragma once

#include "Denizen.h"

#include "Cave.h"
#include "Context.h"

#include "RandomProvider.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace HuntTheWumpus
{
    enum class DungeonMove
    {
        Move,
        Shoot
    };

    class IDungeon
    {
    public:
        
        IDungeon() = default;
        virtual ~IDungeon() = default;

        virtual const std::shared_ptr<Cave> &FindCave(int caveId) = 0;
        virtual void Move(const DenizenIdentifier &identifier, int destinationCave) = 0;
        virtual void MoveDenizenRandomly( const DenizenIdentifier &identifier ) = 0;

        IDungeon(const IDungeon &) = default;
        IDungeon(IDungeon &&) = default;
        IDungeon &operator=(const IDungeon &) = default;
        IDungeon &operator=(IDungeon &&) = default;
    };

    class Dungeon final : public IDungeon
    {
    public:

        explicit Dungeon(Context &providers);
        ~Dungeon() override = default;

        const std::shared_ptr<Cave> &FindCave(int caveId) override;
        void Move(const DenizenIdentifier &identifier, int destinationCave) override;
        void MoveDenizenRandomly( const DenizenIdentifier &identifier ) override;

        void MakeMove(DungeonMove operation, const std::vector<int> &destinationIds);
        static bool LegalMove(const std::shared_ptr<Denizen> &denizen, int destinationCave);

        Dungeon(const Dungeon &) = delete;
        Dungeon(Dungeon &&) = delete;
        Dungeon &operator=(const Dungeon &) = delete;
        Dungeon &operator=(Dungeon &&) = delete;

    private:

        template<class Denizen> void MakeDenizen(int instance)
        {
            auto newDenizen = std::make_shared<Denizen>(instance, m_providers);

            auto DenizenPlaced = false;

            while (!DenizenPlaced)
            {
                const auto DenizenCave = m_providers.m_random.MakeRandomCave();

                // Verify that cave does not have a like Denizen in it.
                if(m_caves[DenizenCave]->HasDenizen(newDenizen->GetIdentifier()))
                {
                    continue;
                }

                AddToCave(newDenizen, DenizenCave, false);

                DenizenPlaced = true;
            }
        }

        void MoveDenizenRandomly( const std::shared_ptr<Denizen> &denizen );

        void Initialize(Context &providers);
        void MakeTunnels();
        void AddToCave(const std::shared_ptr<Denizen> &denizen, int caveId, bool observeEntrance);

        Context &m_providers;
        std::unordered_map<DenizenIdentifier, std::shared_ptr<Denizen>, DenizenIdentifierHasher> m_caveDenizens;
        std::unordered_map<int, std::shared_ptr<Cave>> m_caves;
    };
}
