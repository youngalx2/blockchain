#include <iostream>
#include <sys/socket.h>
#include "include/commands/ReceiveFileCommand.h"

ReceiveFileCommand::ReceiveFileCommand()
    : Command()
{}

void ReceiveFileCommand::Execute(int socketId, const char * cmd)
{
    char buffer[MAX_BUFFER_LEN + 4];
	char file_name[MAX_BUFFER_LEN];
	int file_data_len;

	memset(buffer, 0, sizeof(buffer));
	memset(file_name, 0, sizeof(file_name));

	/* Get File name + len, under 256 characters */
	if (recv(socketId, buffer, MAX_PACKET_CHUNK_LEN, 0) < 0) {
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
		int R = recv(socketId, buffer, MAX_PACKET_CHUNK_LEN, 0);
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