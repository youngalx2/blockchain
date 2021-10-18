#include <stdio.h>
#include <ctime>
#include <string>

#include "include/Block.h"
#include "include/Blockchain.h"

#include <vector>

Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    difficulty = 4;
    chain.push_back(genesis);
}

std::vector<Block> Blockchain::getChain()
{
    return chain;
}

Block Blockchain::createGenesisBlock()
{
    std::time_t current;

    TransactionData data(0, "Genesis", "Genesis", time(&current));

    Block genesis(0, data, "0");
    return genesis;
}

Block* Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData data)
{
    int index = (int)chain.size();
    std::string previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : "0";
    Block newBlock(index, data, previousHash);
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it;

    for(it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if(!currentBlock.isHashValid())
        {
            return false;
        }

        if(it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if(currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }

    return true;
}

void Blockchain::printChain()
{
    std::vector<Block>::iterator it;
    for(it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        printf("\n\nBlock ===============================");
        printf("\nIndex: %d", currentBlock.getIndex());
        printf("\nAmount: %f", currentBlock.data.amount);
        printf("\nSenderKey: %s", currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s", currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %ld", currentBlock.data.timestamp);
        printf("\nHash: %s", currentBlock.getHash().c_str());
        printf("\nPrevious Hash: %s", currentBlock.getPreviousHash().c_str());
        printf("\nIs block valid?: %d", currentBlock.isHashValid());
    }
}

void Blockchain::replaceChain(Blockchain blockchian)
{}
