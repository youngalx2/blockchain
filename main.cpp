#include <iostream>
#include <ctime>
#include <vector>

#include "TransactionData.h"
#include "Blockchain.h"
#include "Block.h"

using namespace std;

int main()
{
    Blockchain tinchocoin;

     cout << "Mining block 1" << endl;
    time_t dataTime;
    TransactionData data(1.5, "Pepe", "Botella", time(&dataTime));
    tinchocoin.addBlock(data);

     cout << "Mining block 2" << endl;
    time_t dataTime2;
    TransactionData data2(0.00013322, "Alberto", "Bolaños", time(&dataTime2));
    tinchocoin.addBlock(data2);

    tinchocoin.printChain();

    cout << "\nIs Chain valid?" << endl
         << tinchocoin.isChainValid() << endl;

    Block* hackBlock = tinchocoin.getLatestBlock();
    hackBlock->data.amount = 10000;
    hackBlock->data.receiverKey = "Tony Stark";

    tinchocoin.printChain();

    cout << "\nNow Is Chain valid??????" << endl
         << tinchocoin.isChainValid() << endl;

    return 0;
}