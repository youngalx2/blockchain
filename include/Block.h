#ifndef Block_h
#define Block_h

#include <string>

#include "TransactionData.h"
using namespace std;

class Block
{
    private:
        int index;
        double nonce;
        string blockHash;
        string previousHash;
        string generateHash();
        void sha256_string(const char* input, char output[65]);

    public:
        Block(int index, TransactionData data, string previousHas);

        int getIndex();
        string getHash();
        string getPreviousHash();
        void mineBlock(int difficulty);

        TransactionData data;

        bool isHashValid();
};

#endif