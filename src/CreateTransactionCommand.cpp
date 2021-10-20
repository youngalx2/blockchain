#include <ctime>
#include "../include/commands/CreateTransactionCommand.h"
#include "../include/TransactionData.h"
#include "../include/StringHelper.h"

CreateTransactionCommand::CreateTransactionCommand(std::shared_ptr<Blockchain> blockchain)
: BlockchainCommand(blockchain)
{}

void CreateTransactionCommand::Execute(int socketId, const char * cmd)
{
    time_t dataTime;
    std::vector<std::string> args = StringHelper::splitBySpace(cmd);

    blockchain->addBlock(TransactionData(stod(args[3]), args[1], args[2], time(&dataTime)));
}