#include "include/BlockchainNetwork.h"
#include "include/PeerReceiver.h"
#include "include/PeerSender.h"

BlockchainNetwork::BlockchainNetwork(std::string hostname, int port, std::shared_ptr<Blockchain> blockchain)
    : me(hostname, port)
{
    this->blockchain = std::move(blockchain);
    // adding some test peers
    for (int i = 5000; i < 5; i++)
    {
        if(i != port)
        {
            peers.push_back(Peer("localhost", i));
        }
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

void BlockchainNetwork::startNetwork(std::string mode)
{
    if (mode == "Receiver")
    {
        std::thread PeerReceiver(StartThePeerReceiver, getHostName(), getPort(), blockchain);
        PeerReceiver.join();
    } 
    else if (mode == "Sender")
    {
        std::thread StartTheSender(StartThePeerSender, getHostName(), getPort(), blockchain);
        StartTheSender.join();
    }
    else
    {
        throw std::invalid_argument("Invalid mode");
    }

}

void BlockchainNetwork::StartThePeerReceiver(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain)
{
	std::unique_ptr<PeerReceiver> rec(new PeerReceiver(hostName, port, blockchain));
	rec->StartReceiver();
}

void BlockchainNetwork::StartThePeerSender(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain)
{
	sleep(1);
	std::unique_ptr<PeerSender> send(new PeerSender(blockchain));
	send->RegisterPeer(hostName, port);
	send->FileDownload();
}