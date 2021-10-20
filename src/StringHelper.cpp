#include <sstream>
#include "../include/StringHelper.h"

std::vector<std::string> StringHelper::splitBySpace(const std::string str)
{
    std::stringstream ss(str);
    std::string arg;
    std::vector<std::string> args;

    while (ss >> arg)
    {
        args.push_back(arg);
    }

    return args;
}

std::vector<std::string> StringHelper::split(const std::string str, const char *delimiter)
{
    std::vector<std::string> result;
    size_t last = 0; size_t next = 0;
    while ((next = str.find(delimiter, last)) != std::string::npos)
    {
        result.push_back(str.substr(last, next-last));
        last = next + 1; 
    }
    result.push_back(str.substr(last));
    return result;
}