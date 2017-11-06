#include "headerFiles.h"

#define SERV_PORT 1234

int main(void)
{
	int ls;
	int s;
	char buffer[256];
	char* ptr = buffer;
	int len = 0;
	int maxLen = sizeof(buffer);
	int n = 0;
	int waitSize = 16;
	struct sockaddr_in servAddr;
	struct sockaddr_in clientAddr;
	int clientAddrLen;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_PORT);

	if ( (ls = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error: Listen socket failed!");
		exit(1);
	}

	if ( (bind (ls, &servAddr, sizeof(servAddr))) < 0)
	{
		perror("Error: binding failed!");
		exit(1);
	}

	if (listen(ls, waitSize) < 0)
	{
		perror("Error: listrening failed!");
		exit(1);
	}

	for(;;)
	{
		if (s = accept(ls, &clientAddr, &clientAddrLen) < 0)
		{
			perror("Error: accepting failed!");
			exit(1);
		}

		while( (n = recv(s, ptr, maxLen, 0) > 0) )
		{
			ptr += n;
			maxLen -= n;
			len += n;
		}

		send(s, buffer, len, 0);
		close(s);
	}
}