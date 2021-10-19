#pragma once
#include "../BlockchainCommand.h"
#include "../Color.h"

class CreateTransactionCommand : public BlockchainCommand
{
public:
    CreateTransactionCommand(std::shared_ptr<Blockchain> blockchain);
    void Execute(int socketId, const char * cmd) override;
};