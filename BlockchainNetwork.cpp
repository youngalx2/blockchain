#include "include/BlockchainNetwork.h"
#include "include/PeerReceiver.h"
#include "include/PeerSender.h"

BlockchainNetwork::BlockchainNetwork(std::string hostname, int port, std::shared_ptr<Blockchain> blockchain)
    : me(hostname, port)
{
    this->blockchain = blockchain;
    // adding some test peers
    for (int i = 50000; i < 50002; i++)
    {
        if(i != port)
        {
            peers.push_back(Peer("localhost", i));
        }
    }
}

BlockchainNetwork::~BlockchainNetwork()
{
    for (auto &thread : threads)
    {
        thread.~thread();
    }
}

std::vector<Peer> BlockchainNetwork::getPeers()
{
    return this->peers;
}

std::string BlockchainNetwork::getHostName()
{
    return this->me.hostname;
}

int BlockchainNetwork::getPort()
{
    return this->me.port;
}

void BlockchainNetwork::startNetwork()
{
    threads.push_back(std::thread (StartThePeerReceiver, getHostName(), getPort(), blockchain));
    
    for (Peer peer : peers)
    {
        threads.push_back(std::thread (StartThePeerSender, peer.hostname, peer.port, blockchain));
    }
}

void BlockchainNetwork::StartThePeerReceiver(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain)
{
	std::unique_ptr<PeerReceiver> rec(new PeerReceiver(hostName, port, blockchain));
	rec->StartReceiver();
}

void BlockchainNetwork::StartThePeerSender(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain)
{
    try
    {
        sleep(10);
        std::unique_ptr<PeerSender> send(new PeerSender(blockchain));
        send->RegisterPeer(hostName, port);
        send->FileDownload();
    }
    catch(std::exception& e)
    {
        printf("Error reaching peer %s:%i. Error: %s \n", hostName.c_str(), port, e.what());
    }
}