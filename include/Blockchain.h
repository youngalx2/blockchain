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
    
    public:
        Blockchain();

        std::vector<Block> getChain();
        Block* getLatestBlock(); // just demo
        bool isChainValid();
        void addBlock(TransactionData data);
        void printChain();
        void replaceChain(Blockchain blockchin);
};

#endif