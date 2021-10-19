#include <iostream>
#include "include/Color.h"
#include <sys/socket.h>
#include "include/commands/ReplaceBlockchainCommand.h"
#include "include/Blockchain.h"

ReplaceBlockchainCommand::ReplaceBlockchainCommand(std::shared_ptr<Blockchain> blockchain)
    : BlockchainCommand(blockchain)
{}

void ReplaceBlockchainCommand::Execute(int socketId, const char * cmd)
{
    int R, received = 0;
    char *receive=NULL;
    char small_buff[MAX_BUFFER_LEN];
	memset(small_buff, 0, sizeof(small_buff));
	R = recv(socketId, small_buff, MAX_PACKET_CHUNK_LEN, 0);
	if (R < 0)
		throw std::runtime_error("Error receving files list");
	
	int to_receive = atoi(small_buff);
	receive = (char*) malloc(sizeof(char) * (to_receive + 100));
	memset(small_buff, 0, sizeof(small_buff));
	*receive = '\0';

	while (received < to_receive) {
		R = recv(socketId, small_buff, MAX_PACKET_CHUNK_LEN, 0);
		if (R < 0) {
			printf("ERROR: Received Failed\n");
		}
		strncat(receive, small_buff, strlen(small_buff) - 1);
		memset(small_buff, 0, sizeof(small_buff));
		received += R;
	}

    printf("Received chain: %s\n", receive);
    auto blocks = Blockchain::deserialize(receive);
    auto chainReplaced = this->blockchain->replaceChain(blocks);
    printf("Chain replaced: %d\n", chainReplaced);
    this->blockchain->printChain();
	free(receive);
	return;
}