#include <vector>
#include "domain/Peer.h"
#include "Blockchain.h"

class BlockchainNetwork
{
public:
    BlockchainNetwork(std::string hostname, int port, std::shared_ptr<Blockchain> blockchain);
    ~BlockchainNetwork();
    std::vector<Peer> getPeers();
    std::string getHostName();
    int getPort();
    void startNetwork();

private:
    Peer me;
    std::vector<std::thread> threads;
    std::vector<Peer> peers;
    std::shared_ptr<Blockchain> blockchain;
    static void StartThePeerSender(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain);
    static void StartThePeerReceiver(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain);
};