const Block = require('./block')
const crypto = require('crypto')

class AwesomeBlock extends Block
{
    constructor(index, timestamp, proof, previousHash, transactions) {
        super(index, timestamp, proof, previousHash)
        this.transactions = transactions
        this.hash = this.generateHash()
    }

    generateHash() {
        return crypto.createHash('sha256').update(this.index + this.timestamp + this.proof + this.previousHash + JSON.stringify(this.transactions))
            .digest('hex')
    }
}

module.exports = AwesomeBlock