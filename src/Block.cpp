#include <stdio.h>
#include <string>
#include <openssl/sha.h>
#include "../include/Block.h"
#include "../include/Color.h"
#include "../include/TransactionData.h"
#include "../include/StringHelper.h"

Block::Block(int index, TransactionData data, std::string previousHash)
{
    this->nonce = 0;
    this->index = index;
    this->data = data;
    this->previousHash = previousHash;
    blockHash = generateHash();
}

int Block::getIndex()
{
    return index;
}

std::string Block::generateHash()
{
    std::string toHashS = std::to_string(index) + previousHash + std::to_string(data.amount) + data.receiverKey + data.senderKey + std::to_string(data.timestamp) + std::to_string(nonce);
    char result[65];
    sha256_string(toHashS.c_str(), result);
    return std::string(result);
}

std::string Block::getHash()
{
    return blockHash;
}

std::string Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == getHash();
}

void Block::sha256_string(const char* input, char output[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = 0;
}

void Block::mineBlock(int difficulty)
{
    std::string prefix = "";
    for(int i = 0; i < difficulty; i++)
    {
        prefix += "0";
    }

    while(blockHash.substr(0, difficulty) != prefix)
    {
        nonce++;
        blockHash = generateHash();
    }

}

std::string Block::serialize()
{
    return std::to_string(index) + SERIALIZATION_DELIMITER + 
        blockHash + SERIALIZATION_DELIMITER + 
        previousHash + SERIALIZATION_DELIMITER +
        std::to_string(data.amount) + SERIALIZATION_DELIMITER +
        data.receiverKey + SERIALIZATION_DELIMITER +
        data.senderKey + SERIALIZATION_DELIMITER +
        std::to_string(data.timestamp) + SERIALIZATION_DELIMITER +
        std::to_string(nonce);
}

Block Block::deserialize(std::string serialized)
{
    std::vector<std::string> parts = StringHelper::split(serialized, SERIALIZATION_DELIMITER);
    Block block(std::stoi(parts[0]), TransactionData(std::stoi(parts[3]), parts[5], parts[4], std::strtoul(parts[6].c_str(), NULL, 0)), parts[2]);

    block.nonce = std::stoi(parts[7]);
    block.blockHash = parts[1];

    return block;
}