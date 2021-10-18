#include "include/PeerSender.h"
#include "include/Color.h"
#include "include/Blockchain.h"
#include <errno.h>

PeerSender::PeerSender(std::shared_ptr<Blockchain> blockchain)
{
    this->blockchain = blockchain;
}

void PeerSender::RegisterPeer(std::string hostname, int port){
	this->SenderName=hostname;
	this->SenderPort=port;
}

void PeerSender::FileDownload(){

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		std::cerr<< "ERROR opening socket\n";
	server = gethostbyname(SenderName.c_str());
	if (server == NULL) {
		std::cerr<< "ERROR, no such host\n";
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(SenderPort);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		std::cerr<< "ERROR connecting" << strerror(errno) << "\n";

	std::cout << "The list of files which can be downloaded are:\n";
	char cmd[MAX_COMMAND_LEN];
	strcpy(cmd,"ls"); //listing of server files
	while (strcmp(cmd, "exit")) {
		if (!strcmp(cmd, "ls")) {
			if (send(sockfd, "ls", MAX_COMMAND_LEN, 0) < 0) {
				std::cerr<< "ERROR sending" << strerror(errno) << "\n";;
			};
			GetListOfFiles(&receive, sockfd);
			std::cout<< receive <<"\n";
			free(receive);
		} else {
			std::cout <<"File Request to download is " << cmd  <<std::endl;
			if (send(sockfd, cmd, MAX_COMMAND_LEN, 0) < 0) {
				std::cerr << "getfile:send_request: Sending Error\n";
			}
			ReceiveAndDownload(sockfd);
		}
		std::cout << "Type the 'filename' to download or 'exit' to discontinue " << std::endl;
		GetPrompt(cmd);
	}
	if (send(sockfd, "disconnect", MAX_PACKET_CHUNK_LEN, 0) < 0) {
		std::cerr <<"Error send while exiting\n";
	}

	close(sockfd);
}

void PeerSender::GetPrompt(char *cmd) {
	printf("%s> %s", KGRN, RESET);
	scanf("%[^\n]", cmd);
	getchar();
	return;
}

void PeerSender::GetListOfFiles(char **buff, int socket_id) {
	char small_buff[MAX_BUFFER_LEN];
	memset(small_buff, 0, sizeof(small_buff));
	recv(socket_id, small_buff, MAX_PACKET_CHUNK_LEN, 0);
	int to_receive = atoi(small_buff);
	int R, received = 0;
	*buff = (char*) malloc(sizeof(char) * (to_receive + 100));
	memset(small_buff, 0, sizeof(small_buff));
	**buff = '\0';

	while (received < to_receive) {
		R = recv(socket_id, small_buff, MAX_PACKET_CHUNK_LEN, 0);
		if (R < 0) {
			printf("ERROR: Received Failed\n");
		}
		strncat(*buff, small_buff, strlen(small_buff) - 1);
		memset(small_buff, 0, sizeof(small_buff));
		received += R;
	}
	return;
}

void PeerSender::ReceiveAndDownload(int SOCKET) {
	char buffer[MAX_BUFFER_LEN + 4];
	char file_name[MAX_BUFFER_LEN];
	int file_data_len;

	memset(buffer, 0, sizeof(buffer));
	memset(file_name, 0, sizeof(file_name));

	/* Get File name + len, under 256 characters */
	if (recv(SOCKET, buffer, MAX_PACKET_CHUNK_LEN, 0) < 0) {
		std::cerr<<"ERROR: Reading file name\n";
		return;
	}
	printf("1: %s\n",buffer);
	char *end_pointer;
	char* ch = strtok_r(buffer, "|", &end_pointer);
	strncpy(file_name, ch, strlen(ch));
	strcat(file_name, "\0");
	ch = strtok_r(NULL, " ,", &end_pointer);
	file_data_len = atoi(ch);
	printf("%sFileName: %s%s\n", KRED, RESET, file_name);
	printf("%sFilesize: %s%d bytes\n", KRED, RESET, file_data_len);

	/* Create File */
    printf("Creating File: %s \n", file_name);
	FILE *fp = fopen(file_name, "wb+");
	if (fp == NULL) {
		printf("File open error");
		return;
	}

	printf("%s-----------------------------------------------------%s\n", KYEL,
			RESET);
	int data_received = 0;
	char dd[10];
	int received = 0;
	while (received < file_data_len) {
		int R = recv(SOCKET, buffer, MAX_PACKET_CHUNK_LEN, 0);
		if (R < 0) {
			std::cerr<< "Error: While receiving\n";
		}
        printf("Buffer: %s \n", buffer);
		if (!fputs(buffer, fp)) {
			std::cerr<< "ERROR: While saving to file\n";
		};
		data_received += R;
		memset(buffer, 0, sizeof(buffer));
		received += R;
        printf("Getting Bytes: %d \n", received);
        printf("Getting Bytes: %d \n", data_received);
	}
	if (received >= file_data_len) {
		printf("%sFile Length:%s%d nbytes %s%s%s\n", KRED, RESET, received, KGRN, TICK,
				RESET);
	} else {
		printf("%sCONCERN:%s File Length not matching%s\n", KRED, KYEL, RESET);
	}

	fclose(fp);
}