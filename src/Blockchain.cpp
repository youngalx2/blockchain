#include <stdio.h>
#include <ctime>
#include <string>
#include "../include/StringHelper.h"
#include "../include/Block.h"
#include "../include/Blockchain.h"

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
    return isChainValid(chain);
}

bool Blockchain::isChainValid(std::vector<Block> blocks)
{
    std::vector<Block>::iterator it;

    for(it = blocks.begin(); it != blocks.end(); ++it)
    {
        Block currentBlock = *it;
        if(!currentBlock.isHashValid())
        {
            return false;
        }

        if(it != blocks.begin())
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

bool Blockchain::replaceChain(std::vector<Block> chain)
{
    if(isChainValid(chain) && chain.size() > this->chain.size())
    {
        this->chain = chain;
        return true;
    }

    return false;
}

std::string Blockchain::serialize()
{
    std::string serializedChain = "";
    for (auto &block : chain)
    {
        serializedChain += block.serialize();
        serializedChain += "\n";
    }

    return serializedChain;
}

std::vector<Block> Blockchain::deserialize(std::string serialized)
{
    std::vector<std::string> blocks = StringHelper::split(serialized, "\n");
    std::vector<Block> deserializedChain;

    for (auto &block : blocks)
    {
        deserializedChain.push_back(Block::deserialize(block));
    }

    return deserializedChain;
}
