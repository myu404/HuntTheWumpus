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
    class Arrow final : public Denizen
    {
    public:
        Arrow(int arrowInstance, Context& providers);
        ~Arrow() override = default;

        int GetPriority() const override { return 2; }

        Arrow(const Arrow&) = delete;
        Arrow(Arrow&&) = delete;
        Arrow& operator=(const Arrow&) = delete;
        Arrow& operator=(Arrow&&) = delete;
    };
}
