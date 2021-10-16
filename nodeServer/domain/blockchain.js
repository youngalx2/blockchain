const crypto = require('crypto');
const Block = require("./block");

class Blockchain {
    constructor() {
        this.chain = [];
        this.createGenesisBlock()
    }

    reset(chain) {
        this.chain = chain
        return this
    }

    createBlock(proof, previousHash) {
        const block = this.generateBlockFrom(proof, previousHash)
        this.chain.push(block)
        return block
    }

    createGenesisBlock() {
        const block = new Block(1, new Date().getTime(), 1, '0')
        this.chain.push(block)
        return block
    }

    generateBlockFrom(proof, previousHash) {
        return new Block(this.getNextBlockIndex(),
            new Date().getTime(),
            proof,
            previousHash)
    }

    getLatestBlock() {
        return this.chain[this.chain.length - 1];
    }

    getNextBlockIndex() {
        return this.getLatestBlock().index + 1
    }

    proofOfWork(previousProof) {
        let proof = 1;
        let checkProof = false;
        while (!checkProof) {
            const hash = this.calculateProofHash(proof, previousProof)

            if(this.isHashValidProof(hash)) {
                checkProof = true
            } else {
                proof += 1;
            }
        }
        return proof;
    }

    isChainValid() {
        for (let i = 1; i < this.chain.length; i++) {
            const currentBlock = this.chain[i];

            if(!currentBlock.isHashValid())
                return false;

            const previousBlock = this.chain[i - 1];
            if (currentBlock.previousHash != previousBlock.hash)
                return false;
            
            if(!this.isHashValidProof(this.calculateProofHash(currentBlock.proof, previousBlock.proof)))
                return false;
        }

        return true;
    }

    calculateProofHash(proof, previousProof) {
        return crypto.createHash("sha256")
                .update((proof**2 - previousProof**2).toString())
                .digest("hex")
    }

    isHashValidProof(hash) {
        return hash.startsWith("0000");
    }

}

module.exports = Blockchain;