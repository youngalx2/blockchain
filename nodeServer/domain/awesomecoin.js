const AwesomeBlock = require('./awesomeBlock')
const Blockchain = require('./blockchain')
const url = require('url')
const http = require('http')

class AwesomeCoin extends Blockchain
{
    constructor() {
        super()
        this.transactions = []
        this.nodes = new Set()
    }

    reset(chain) {
        super.reset(chain)
        this.transactions = []
        this.nodes = new Set()
        return this
    }

    generateBlockFrom(proof, previousHash) {
        return new AwesomeBlock(this.chain.length + 1,
            new Date().getTime(),
            proof,
            previousHash,
            this.transactions)
    }

    createBlock(proof, previousHash) {
        const block = super.createBlock(proof, previousHash)
        this.transactions = []
        return block
    }

    createGenesisBlock() {
        const block = new AwesomeBlock(1, new Date().getTime(), 1, '0', [])
        this.chain.push(block)
        return block
    }

    addTransaction(transaction) {
        this.transactions.push(transaction)
        return this.getNextBlockIndex()
    }

    addNode(node) {
        const parserdUrl = url.parse(node, false)
        this.nodes.add(parserdUrl.host)
    }

    async replaceChain() {
        let maxLength = this.chain.length
        let longestChain
        const arrNodes = Array.from(this.nodes)

        for (let i = 0; i < arrNodes.length; i++) {
            const host = arrNodes[i]
            try {
                const nodeChain = await this.getNodeChain(host)
                if (nodeChain.chain.length > maxLength && nodeChain.isChainValid()) {
                    maxLength = nodeChain.chain.length
                    longestChain = nodeChain.chain
                }
            } catch (e) {
                console.log(e)
                continue
            }
        }

        if(longestChain) {
            this.chain = longestChain
            return true
        }
        return false
    }

    async getNodeChain(nodeUrl) {
        const hostname = nodeUrl.split(':')[0]
        const port = nodeUrl.split(':')[1]
        const options = {
            hostname: hostname,
            port: port,
            path: '/awesomecoin/chain',
            method: 'GET'
        }
        
        return new Promise((resolve, reject) => {
            http.request(options, res => {  
                let data = ''
                res.on('data', chunk => {
                    data += chunk
                })

                res.on('end', () => {
                    const chain = new AwesomeCoin()
                        .reset(JSON.parse(data).chain.map(block => Object.setPrototypeOf(block, AwesomeBlock.prototype)))
                    resolve(chain)
                });
            }).on('error', error => {
                reject(error)
            }).end()
        })
    }
}

module.exports = AwesomeCoin