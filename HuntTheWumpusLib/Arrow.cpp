/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

#include "Arrow.h"

namespace HuntTheWumpus
{
    Arrow::Arrow(const int arrowInstance, Context &providers)
        : Denizen(DenizenIdentifier{ Category::Arrow, arrowInstance }, { false, true, true, false, false }, providers)
    {       
    }
}