#include <stdio.h>
#include <string>
#include <openssl/sha.h>
#include "Block.h"
#include "TransactionData.h"

using namespace std;

Block::Block(int index, TransactionData data, string previousHash)
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

string Block::generateHash()
{
    std::string toHashS = std::to_string(index) + previousHash + std::to_string(data.amount) + data.receiverKey + data.senderKey + std::to_string(data.timestamp) + std::to_string(nonce);
    char result[65];
    sha256_string(toHashS.c_str(), result);
    return std::string(result);
}

string Block::getHash()
{
    return blockHash;
}

string Block::getPreviousHash()
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
    string prefix = "";
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