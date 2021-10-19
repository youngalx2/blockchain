#include "include/BlockchainCommand.h"

BlockchainCommand::BlockchainCommand(std::shared_ptr<Blockchain> blockchain)
    : blockchain(blockchain)
{}

BlockchainCommand::~BlockchainCommand()
{}