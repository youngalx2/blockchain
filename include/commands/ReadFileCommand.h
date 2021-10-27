#pragma once
#include <iostream>
#include "../Command.h"
#include "../Color.h"

class ReadFileCommand : public Command {
public:
    ReadFileCommand();
    void Execute(int socketId, const char * cmd) override;
private:
    int GetFilesize(FILE* fileid);
};