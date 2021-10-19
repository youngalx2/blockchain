#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "include/commands/ListFilesCommand.h"

ListFilesCommand::ListFilesCommand()
    :Command()
{
}

void ListFilesCommand::Execute(int socketId, const char * cmd)
{
    char buff[MAX_BUFFER_LEN];
	memset(buff, 0, sizeof(buff));
	
	ListCommand(buff);

	// Send length of data
	char snum[200];
	memset(snum, 0, sizeof(snum));
	int size=strlen(buff);
	sprintf(snum, "%d", size);
	send(socketId, snum, MAX_PACKET_CHUNK_LEN, 0);

	// Send all data
	int S,sent=0;
	while(sent < size) {
		S = send(socketId, buff + sent, MAX_PACKET_CHUNK_LEN, 0);
		if(S < 0) {
			std::cerr << "listfiles sending error \n";
		}
		sent += S;
	};
}

void ListFilesCommand::ListCommand(char bufferResult[]) {
	int pipefd[2];
	pipe(pipefd);
	char buffer[MAX_BUFFER_LEN];
	memset(buffer, 0, sizeof(buffer));
	int pid=fork();
	if(pid==0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		dup2(pipefd[1], 2);
		close(pipefd[1]);

        // casted to remove warning
        char folder[sizeof(SERVER_SHARED_DIR)];
        strcpy(folder, SERVER_SHARED_DIR);
		char *args[] = { (char *)"ls", (char *)"-a1", folder, NULL };
		execvp(args[0], &args[0]);
		exit(EXIT_SUCCESS);
	}
	else {
		// parent
		close(pipefd[1]);  // close the write end of the pipe in the parent
		while (read(pipefd[0], buffer, sizeof(buffer)) != 0)
		{
		}
	}
	strcpy(bufferResult, buffer);	// Copy into the given buffer
	return;
}
