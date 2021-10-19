#include "include/Command.h"

Command::Command()
{
}

Command::~Command()
{}

std::string Command::ExtractCommand(char * cmd)
{
    auto index = std::string(cmd).find(" ");
	return std::string(cmd).substr(0, index);
}