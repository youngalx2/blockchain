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
     if(argc < 3)
     {
          std::cout << "Invalid amount of arguments";
          return 1;
     }

     std::string PeerReceiverName = argv[1];
     int PeerReceiverPort = atoi(argv[2]);
     
     auto tinchocoin = std::make_shared<Blockchain>();
     BlockchainNetwork network(PeerReceiverName, PeerReceiverPort, tinchocoin);
     network.startNetwork();

     while(true)
     {}

    return 0;
}