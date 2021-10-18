#include <vector>
#include "domain/Peer.h"
#include "Blockchain.h"

class BlockchainNetwork
{
public:
    BlockchainNetwork(std::string hostname, int port, std::shared_ptr<Blockchain> blockchain);
    std::vector<Peer> getPeers();
    std::string getHostName();
    int getPort();
    void startNetwork(std::string mode);

private:
    Peer me;
    std::vector<Peer> peers;
    std::shared_ptr<Blockchain> blockchain;
    static void StartThePeerSender(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain);
    static void StartThePeerReceiver(std::string hostName, int port, std::shared_ptr<Blockchain> blockchain);
};