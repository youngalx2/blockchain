const Blockchain = require('../domain/blockchain')
const blockchain = new Blockchain()


class BlockchainController {
    mineBlock(req, res) {
        const previousBlock = blockchain.getLatestBlock()
        const proof = blockchain.proofOfWork(previousBlock.proof)
        const block = blockchain.createBlock(proof, previousBlock.hash)
    
        res.send({
            message: 'New Block Forged',
            ...block
        })
    }

    getChain(req, res) {
        res.send({
            length: blockchain.chain.length,
            chain: blockchain.chain
        })
    }

    isChainValid(req, res) {
        res.send({
            message: blockchain.isChainValid() ? 'Chain is healthy' : 'Chain broken'
        })
    }
}

const blockchainController = new BlockchainController()
module.exports = blockchainController
