class Transaction {
    constructor(sender, receiver, amount) {
        if(!sender || !receiver || !amount) {
            throw new Error("Invalid transaction");
        }
        
        this.sender = sender;
        this.receiver = receiver;
        this.amount = amount;
    }
}

module.exports = Transaction