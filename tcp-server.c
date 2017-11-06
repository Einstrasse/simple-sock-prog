#include "headerFiles.h"

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
	socklen_t clientAddrLen;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_PORT);

	if ( (ls = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error: Listen socket failed!");
		exit(1);
	}
	printf("Socket created\n");

	if ( (bind (ls, (const struct sockaddr*)&servAddr, sizeof(servAddr)) ) < 0)
	{
		perror("Error: binding failed!");
		exit(1);
	}
	printf("Socket address binded\n");

	if (listen(ls, waitSize) < 0)
	{
		perror("Error: listrening failed!");
		exit(1);
	}
	printf("Socket is listening\n");

	for (;;) 
	{

		if ( (s = accept(ls, (struct sockaddr*)&clientAddr, &clientAddrLen)) < 0)
		{
			perror("Error: accepting failed!");
			exit(1);
		}

		while( (n = read(s, ptr, maxLen)) != 0) {
	           write(s, ptr, n);
	             write(1, ptr, n);
	    }
	    close(s);
	}
	// for(;;)
	// {
		// if ( (s = accept(ls, (struct sockaddr*)&clientAddr, &clientAddrLen)) < 0)
		// {
		// 	perror("Error: accepting failed!");
		// 	exit(1);
		// } else {
		// 	printf("accepting new connection...(client socket = %d)\n", s);
		// }

		// for(;;)
		// {

		// 	while( (n = recv(s, ptr, maxLen, 0) > 0) )
		// 	{
		// 		printf("Receiving messages(len = %d)\n", n);
		// 		ptr += n;
		// 		maxLen -= n;
		// 		len += n;
		// 		printf("Trying to reply..\n");
		// 		int reply_len = send(s, ptr-n, n, 0);
		// 		if (reply_len == -1) 
		// 		{
		// 			perror("Error: reply failed!");
		// 			exit(1);
		// 		} else {
		// 			printf("Reply success. len=%d\n", reply_len);
		// 		}
		// 	}
		// }
	// }
	printf("closing socket\n");
	close(s);
}