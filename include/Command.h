#pragma once
#include <string>

class Command
{
    public:
        Command();
        virtual ~Command();
        virtual void Execute(int socketId, const char * cmd) = 0;
        static std::string ExtractCommand(char *cmd);
};