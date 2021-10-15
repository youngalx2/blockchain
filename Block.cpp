#include <stdio.h>
#include <string>

#include "headers/Block.h"
#include "headers/TransactionData.h"

Block::Block(int index, TransactionData data, size_t previousHash)
{
    this->index = index;
    this->data = data;
    this->previousHash = previousHash;
    blockHash = generateHash();
}

int Block::getIndex()
{
    return index;
}

size_t Block::generateHash()
{
    std::string toHashS = std::to_string(data.amount) + data.receiverKey + data.senderKey + std::to_string(data.timestamp);

    std::hash<std::string> dataHash;
    std::hash<std::string> prevHash; // re hasehs previous hash

    // combine hashes and get size_t for block hash
    return dataHash(toHashS) ^ (prevHash(std::to_string(previousHash)) << 1);
}

size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == getHash();
}