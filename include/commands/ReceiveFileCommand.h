#pragma once
#include "../Command.h"
#include "../Color.h"

class ReceiveFileCommand : public Command
{
public:
    ReceiveFileCommand();
    void Execute(int socketId, const char * cmd) override;
};