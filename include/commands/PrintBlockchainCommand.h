#pragma once
#include "../BlockchainCommand.h"
#include "../Color.h"

class PrintBlockchainCommand : public BlockchainCommand
{
public:
    PrintBlockchainCommand(std::shared_ptr<Blockchain> blockchain);
    void Execute(int socketId, const char * cmd) override;
};