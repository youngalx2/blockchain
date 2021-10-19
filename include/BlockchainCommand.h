#pragma once
#include "Blockchain.h"
#include "Command.h"

class BlockchainCommand : public Command
{
public:
    BlockchainCommand(std::shared_ptr<Blockchain> blockchain);
    virtual ~BlockchainCommand();

    virtual void Execute(int socketId, const char * cmd) = 0;
protected:
    std::shared_ptr<Blockchain> blockchain;
};
