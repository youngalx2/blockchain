#include <iostream>
#include <ctime>
#include <vector>
#include <thread>
#include <unistd.h>
#include <memory>
#include <exception>

#include "include/TransactionData.h"
#include "include/Blockchain.h"
#include "include/Block.h"
#include "include/PeerReceiver.h"
#include "include/PeerSender.h"
#include "include/BlockchainNetwork.h"



int main(int argc, char **argv)
{
     if(argc < 4)
     {
          std::cout << "Invalid amount of arguments";
          return 1;
     }

     std::string PeerReceiverName = argv[1];
     int PeerReceiverPort = atoi(argv[2]);
     std::string Mode = argv[3];
     
     auto tinchocoin = std::shared_ptr<Blockchain>();
     BlockchainNetwork network(PeerReceiverName, PeerReceiverPort, tinchocoin);

     network.startNetwork(Mode);

     std::cout << "Mining block 1" << std::endl;
     time_t dataTime;
     TransactionData data(1.5, "Pepe", "Botella", time(&dataTime));
     tinchocoin->addBlock(data);

     std::cout << "Mining block 2" << std::endl;
     time_t dataTime2;
     TransactionData data2(0.00013322, "Alberto", "Bolaños", time(&dataTime2));
     tinchocoin->addBlock(data2);

     tinchocoin->printChain();

     std::cout << "\nIs Chain valid?" << std::endl
          << tinchocoin->isChainValid() << std::endl;

     Block* hackBlock = tinchocoin->getLatestBlock();
     hackBlock->data.amount = 10000;
     hackBlock->data.receiverKey = "Tony Stark";

     tinchocoin->printChain();

     std::cout << "\nNow Is Chain valid??????" << std::endl
          << tinchocoin->isChainValid() << std::endl;

    return 0;
}