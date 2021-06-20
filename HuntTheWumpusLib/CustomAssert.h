/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

#pragma once
#include <stdexcept>
#include <sstream>


namespace HuntTheWumpus
{
    void assert(bool condition, const std::string filename, const int lineNumber, const std::string errorMessage = "");
}

