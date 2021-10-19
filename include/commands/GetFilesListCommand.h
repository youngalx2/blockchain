#pragma once
#include "../Command.h"
#include "../Color.h"

class GetFilesListCommand : public Command
{
public:
    GetFilesListCommand();
    void Execute(int socketId, const char * cmd) override;
private:
    char *receive=NULL;
};