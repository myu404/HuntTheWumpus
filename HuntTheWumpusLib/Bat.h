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
    class Bat final : public Denizen
    {
    public:
        Bat(int batInstance, Context& providers);
        ~Bat() override = default;

        bool ObserveCaveEntrance(const std::shared_ptr<Denizen>& trigger) override;
        void ReportPresence() const override;

        int GetPriority() const override { return 5; }

        Bat(const Bat&) = delete;
        Bat(Bat&&) = delete;
        Bat& operator=(const Bat&) = delete;
        Bat& operator=(Bat&&) = delete;
    };
}
