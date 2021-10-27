#ifndef Blockchain_h
#define Blockchain_h

#include <vector>
#include "Block.h"

class Blockchain
{
    private:
        Block createGenesisBlock();
        std::vector<Block> chain;
        int difficulty;
        bool isChainValid(std::vector<Block> blocks);
    public:
        Blockchain();

        std::vector<Block> getChain();
        Block* getLatestBlock(); // just demo
        bool isChainValid();
        void addBlock(TransactionData data);
        void printChain();
        bool replaceChain(std::vector<Block> chain);
        std::string serialize();
        static std::vector<Block> deserialize(std::string serialized);
};

#endif