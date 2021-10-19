#pragma once
#include <vector>

class StringHelper
{
public:
    static std::vector<std::string> splitBySpace(const std::string str);
    static std::vector<std::string> split(const std::string str, const char *delimiter);
};