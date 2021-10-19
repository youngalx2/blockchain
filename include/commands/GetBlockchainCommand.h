#pragma once
#include "../BlockchainCommand.h"
#include "../Color.h"

class GetBlockchainCommand : public BlockchainCommand
{
public:
    GetBlockchainCommand(std::shared_ptr<Blockchain> blockchain);
    void Execute(int socketId, const char * cmd) override;
};