#pragma once
#include "../Command.h"
#include "../Color.h"

class ListFilesCommand : public Command
{
public:
    ListFilesCommand();
    void Execute(int socketId, const char * cmd) override;
private:
    char *bufferResult;
    void ListCommand(char bufferResult[]);
};