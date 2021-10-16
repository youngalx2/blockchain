const crypto = require('crypto')

class Block {
    constructor(index, timestamp, proof, previousHash) {
        this.index = index;
        this.timestamp = timestamp;
        this.proof = proof;
        this.previousHash = previousHash;
        this.hash = this.generateHash()
    }

    generateHash() {
        return crypto.createHash('sha256').update(this.index + this.timestamp + this.proof + this.previousHash).digest('hex')
    }

    isHashValid() {
        return this.hash === this.generateHash()
    }
}

module.exports = Block