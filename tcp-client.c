#include "headerFiles.h"

int main(int argc, char* argv[])
{
	int s;
	int n;
	char* servName;
	int servPort;
	char* string;
	int len;
	int maxLen = 256;
	char buffer[256+1];
	char send_buf[256];
	char* ptr = buffer;
	struct sockaddr_in servAddr;
	if (argc != 4)
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
	servAddr.sin_port = htons(servPort);

	if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error: socket creation failed!");
		exit(1);
	}
	printf("create socket\n");

	if (connect(s, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
	{
		perror("Error: connection failed!");
		exit(1);
	}
	printf("create connection\n");

	strcpy(send_buf, string);
	send_buf[strlen(string)] = 0x0a;
	send_buf[strlen(string)+1] = '\0';
	int send_len = send(s, send_buf, strlen(send_buf), 0);
	if (send_len == -1) {
		perror("Error: send failed!");
		exit(1);
	}

	printf("sending message '%s', len=%d\n", string, send_len);
	while( (n = recv(s, ptr, maxLen, 0)) > 0)
	{
		printf("receiving reply %d bytes..\n", n);
		write(1, ptr, n);
		ptr += n;
		maxLen -= n;
		len += n;
	}

	// buffer[len] = '\0';
	// printf("Echoed string received:");
	// fputs(buffer, stdout);
	close(s);
	exit(0);
}