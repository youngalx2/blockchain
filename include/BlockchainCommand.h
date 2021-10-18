#include "Blockchain.h"
#include "domain/Peer.h"

class BlockchainCommand
{
public:
    BlockchainCommand(std::shared_ptr<Blockchain> blockchain);
    virtual ~BlockchainCommand();

    virtual void Execute(Peer peer) const = 0;
};
