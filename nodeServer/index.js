const express = require('express')
const blockchainRouter = express.Router()
const awesomeCoinRouter = express.Router()
const app = express()
const port = process.env.PORT || 3000
const bodyParser = require('body-parser')

const jsonParser = bodyParser.json({type: '*/json'})
app.use(jsonParser)

const blockchainController = require('./controllers/blockchainController')
const awesomeCoinController = require('./controllers/awesomeCoinController')

const asyncMiddleware = fn => (req, res, next) => {
    Promise.resolve(fn(req, res, next))
        .catch(next)
}

blockchainRouter.get('/mineblock', blockchainController.mineBlock.bind(blockchainController))
blockchainRouter.get('/chain', blockchainController.getChain.bind(blockchainController))
blockchainRouter.get('/ischainvalid', blockchainController.isChainValid).bind(blockchainController)

awesomeCoinRouter.get('/mineblock', awesomeCoinController.mineBlock.bind(awesomeCoinController))
awesomeCoinRouter.get('/chain', awesomeCoinController.getChain.bind(awesomeCoinController))
awesomeCoinRouter.get('/ischainvalid', awesomeCoinController.isChainValid.bind(awesomeCoinController))
awesomeCoinRouter.get('/replacechain', asyncMiddleware(awesomeCoinController.replaceChain.bind(awesomeCoinController)))
awesomeCoinRouter.get('/nodes', awesomeCoinController.getNodes.bind(awesomeCoinController))
awesomeCoinRouter.post('/addtransaction', awesomeCoinController.addTransaction.bind(awesomeCoinController))
awesomeCoinRouter.post('/connectnodes', awesomeCoinController.connectNodes.bind(awesomeCoinController))

app.use('/blockchain', blockchainRouter)
app.use('/awesomecoin', awesomeCoinRouter)

app.listen(port, () => {
    console.log(`Server running on port ${port}`)
})