#include "headerFiles.h"

int main(void)
{
	int s;
	int len;
	char buffer[256];
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	int cIntAddrLen;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SERVER_PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error: socket failed!");
		exit(1);
	}

	if ( (bind(s, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) )
	{
		perror("Error: bind failed!");
		exit(1);
	}
	for(;;)
	{
		len = recvfrom(s, buffer, sizeof(buffer), 0,
		 (struct sockaddr*)&cIntAddr, &cIntAddrLen);

		sendto(s, buffer, len, 0, (struct sockaddr*)&cIntAddr, sizeof(cIntAddr));
	}
}