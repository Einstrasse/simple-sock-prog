#include "headerFiles.h"

int main(int argc, char* argv[])
{
	int s;
	int n;
	char* servName;
	int servPort;
	char* string;
	int len;
	char buffer[256+1];
	char* ptr = buffer;
	struct sockaddr_in servAddr;
	if (argc != 3)
	{
		printf("Error: three arguments are needed!");
		exit(1);
	}

	servName = argv[1];
	servPort = atoi(argv[2]);
	string = argv[3];

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, servName, &servAddr.sin_addr);
	serverAddr.sin_port = htons(servPort);

	if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error: socket creation failed!");
		exit(1);
	}

	if (connect(sd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
	{
		perror("Error: connection failed!");
		exit(1);
	}
	send(s, string, strlen(string), 0);
	while((n = recv(s, ptr, maxLen, 0)) > 0)
	{
		ptr += n;
		maxLen -= n;
		len += n;
	}

	buffer[len] = '\0';
	printf("Echoed string received:");
	fputs(buffer, stdout);
	close(s);
	exit(0);
}