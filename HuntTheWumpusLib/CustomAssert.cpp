/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

#include "CustomAssert.h"
#include <stdexcept>
#include <sstream>


namespace HuntTheWumpus
{
    void assert(bool condition, const std::string filename, const int lineNumber, const std::string errorMessage)
    {
        if (!condition)
        {
            std::stringstream ss;
            ss << "Failed to meet pre-condition requirement at " << filename << ", line " << lineNumber << "." << errorMessage << std::endl;
            throw std::runtime_error(ss.str());
        }
    }
}

