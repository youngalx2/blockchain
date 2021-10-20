#include <iostream>
#include <sys/socket.h>
#include "../include/commands/GetBlockchainCommand.h"

GetBlockchainCommand::GetBlockchainCommand(std::shared_ptr<Blockchain> blockchain)
    : BlockchainCommand(blockchain)
{}

void GetBlockchainCommand::Execute(int socketId, const char * cmd)
{
    // char buff[MAX_BUFFER_LEN];
	// memset(buff, 0, sizeof(buff));
    auto chain = blockchain->serialize();
    const char *serializedChain = chain.c_str();
    printf("Sending chain: %s\n", serializedChain);

	// Send length of data
	char snum[200];
	memset(snum, 0, sizeof(snum));
	int size=strlen(serializedChain);
	sprintf(snum, "%d", size);
	send(socketId, snum, MAX_PACKET_CHUNK_LEN, 0);

	// Send all data
	int S,sent=0;
	while(sent < size) {
		S = send(socketId, serializedChain + sent, MAX_PACKET_CHUNK_LEN, 0);
		if(S < 0) {
			std::cerr << "listfiles sending error \n";
		}
		sent += S;
	};
}