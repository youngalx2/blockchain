#pragma once
#include "../BlockchainCommand.h"

class ReplaceBlockchainCommand : public BlockchainCommand
{
public:
    ReplaceBlockchainCommand(std::shared_ptr<Blockchain> blockchain);
    void Execute(int socketId, const char * cmd) override;
};