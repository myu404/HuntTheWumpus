/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

#pragma once

#include "Denizen.h"

namespace HuntTheWumpus
{
    class Pit final : public Denizen
    {
    public:
        Pit(int pitInstance, Context& providers);
        ~Pit() override = default;

        int GetPriority() const override { return 4; }

        bool ObserveCaveEntrance(const std::shared_ptr<Denizen>& trigger) override;
        void ReportPresence() const override;

        Pit(const Pit&) = delete;
        Pit(Pit&&) = delete;
        Pit& operator=(const Pit&) = delete;
        Pit& operator=(Pit&&) = delete;
    };
}
