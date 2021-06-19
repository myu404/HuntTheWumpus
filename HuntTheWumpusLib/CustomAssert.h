#pragma once
#include <stdexcept>
#include <sstream>

void assert(bool condition, const std::string filename, const int lineNumber)
{
    std::stringstream ss;
    ss << "Failed to meet pre-condition requirement at " << filename << ", line " << lineNumber << std::endl;
    if (!condition) throw std::runtime_error(ss.str());
}
