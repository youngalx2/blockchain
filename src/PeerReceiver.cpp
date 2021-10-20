#include "../include/PeerReceiver.h"
#include "../include/commands/GetBlockchainCommand.h"

PeerReceiver::PeerReceiver(std::string receiverName, int receiverPort, std::shared_ptr<Blockchain> blockchain){
	this->ReceiverName = receiverName;
	this->ReceiverPort = receiverPort;
    this->blockchain = blockchain;
	this->commands.emplace("ls", []() -> std::unique_ptr<Command> { return std::make_unique<ListFilesCommand>(); });
	this->commands.emplace("get", []() -> std::unique_ptr<Command> { return std::make_unique<ReadFileCommand>(); });
	this->commands.emplace("bc-get-chain", [&]() -> std::unique_ptr<Command> { return std::make_unique<GetBlockchainCommand>(blockchain); });
}

PeerReceiver::~PeerReceiver()
{
	int errorCode;
	socklen_t errorCodeSize = sizeof(errorCode);
	if(getsockopt(newsockfd, SOL_SOCKET, SO_ERROR, &errorCode, &errorCodeSize) == 0)
		close(newsockfd);
	if(getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &errorCode, &errorCodeSize) == 0)
		close(sockfd);
}

void PeerReceiver::StartReceiver(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		std::cerr << "ERROR opening socket" << strerror(errno)<<"\n";
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(ReceiverPort);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		std::cerr << "ERROR on binding" << std::endl;
	listen(sockfd, 10);
	clilen = sizeof(cli_addr);

	while(true) {
		std::cout << "---- PEER Receiver started at Port ---- " << ReceiverPort << std::endl;
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
			std::cerr << "ERROR on accept" << strerror(errno)<<"\n";;

		char cmd[MAX_COMMAND_LEN];
		recv(newsockfd, cmd, MAX_COMMAND_LEN, 0);
		while (strcmp(cmd, "disconnect")) {
			if(commands.count(Command::ExtractCommand(cmd)) > 0) {
				commands[Command::ExtractCommand(cmd)]()->Execute(newsockfd, cmd);
			}

			memset(cmd, 0, sizeof(cmd));
			recv(newsockfd, cmd, MAX_COMMAND_LEN, 0);
		}
		close(newsockfd);
	}
	close(sockfd);
}
