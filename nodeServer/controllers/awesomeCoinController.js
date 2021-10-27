const AwesomeCoin = require('../domain/awesomecoin')
const uuid = require('uuid')
const Transaction = require('../domain/transaction')
const awesomeCoin = new AwesomeCoin()


class AwesomeCoinController {
    constructor() {
        this.nodeAddress = uuid.v4().replace('-', '')
    }

    mineBlock(req, res) {
        const previousBlock = awesomeCoin.getLatestBlock()
        const proof = awesomeCoin.proofOfWork(previousBlock.proof)
        awesomeCoin.addTransaction(new Transaction(this.nodeAddress, 'Awesome', 10))
        const block = awesomeCoin.createBlock(proof, previousBlock.hash)
    
        res.send({
            message: 'New Block Forged',
            ...block
        })
    }

    addTransaction(req, res) {
        const nextBlockIndex = awesomeCoin.addTransaction(new Transaction(req.body.from, req.body.to, req.body.amount))
        res.status(201).send({
            message: `This transaction will be added to block ${nextBlockIndex}`
        })
    }

    getChain(req, res) {
        res.send({
            length: awesomeCoin.chain.length,
            chain: awesomeCoin.chain
        })
    }

    isChainValid(req, res) {
        res.send({
            message: awesomeCoin.isChainValid() ? 'Chain is healthy' : 'Chain broken'
        })
    }

    getNodes(req, res) {
        return res.send({
            nodes: Array.from(awesomeCoin.nodes)
        })
    }

    connectNodes(req, res) {
        const {addresses} = req.body
        if(!addresses || addresses.length === 0) {
            res.status(400).send({
                message: 'No address provided'
            })
        }

        addresses.forEach(address => {
            awesomeCoin.addNode(address)
        })
        res.status(201).send({
            message: `Nodes ${Array.from(awesomeCoin.nodes).join(', ')} connected`,
            totalNodes: Array.from(awesomeCoin.nodes).length
        })
    }

    async replaceChain(req, res) {
        const result = await awesomeCoin.replaceChain()
        res.send({
            message: result ? `The nodes had different chain so the chain was replaced by the longest one`: `All good. The chain is the largest one`,
            chain: awesomeCoin.chain
        })
    }
}

const awesomeCoinController = new AwesomeCoinController()
module.exports = awesomeCoinController
