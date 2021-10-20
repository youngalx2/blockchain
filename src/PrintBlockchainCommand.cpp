#include "../include/commands/PrintBlockchainCommand.h"

PrintBlockchainCommand::PrintBlockchainCommand(std::shared_ptr<Blockchain> blockchain)
    : BlockchainCommand(blockchain)
{}

void PrintBlockchainCommand::Execute(int socketId, const char * cmd)
{
    this->blockchain->printChain();
}