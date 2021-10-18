#ifndef Block_h
#define Block_h

#include <string>

#include "TransactionData.h"

class Block
{
    private:
        int index;
        double nonce;
        std::string blockHash;
        std::string previousHash;
        std::string generateHash();
        void sha256_string(const char* input, char output[65]);

    public:
        Block(int index, TransactionData data, std::string previousHas);

        int getIndex();
        std::string getHash();
        std::string getPreviousHash();
        void mineBlock(int difficulty);

        TransactionData data;

        bool isHashValid();
};

#endif