#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <regex.h>
#include <thread>
#include <iostream>
#include "Blockchain.h"

class PeerReceiver
{
private:
	std::string ReceiverName ="";
	int ReceiverPort=0, sockfd=0, newsockfd=0, portno=0;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[256]={0};
	std::shared_ptr<Blockchain> blockchain;
	void FileReaderAndReceiver(const char* file_name, int socket_id);
	int GetFilesize(FILE*);
	void listfiles(int);
	void listCommand(char[]);


public:
	PeerReceiver(std::string receiverName, int receiverPort, std::shared_ptr<Blockchain> blockchain);
	void StartReceiver();
};