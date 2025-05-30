#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm-generic/socket.h>
#include <asm-generic/types.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT	9000

int main()
{
	struct sockaddr_in sad,cad;
	memset(&sad, 0, sizeof(sad));
	memset(&cad, 0, sizeof(cad));
	
	sad.sin_family = AF_INET;
	sad.sin_port = htons(PORT);	
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	//printf("LE: %d    BE: %d\r\n",PORT, sad.sin_port);  
	unsigned int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	printf("socket open result : %d....\r\n", fd);
	
	//int optvalue = 1;
	//setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));
	
	int addrLen = sizeof(sad);
	int ret = connect(fd, (struct sockaddr*)(&sad), addrLen);
	printf("client connect result : %d....\r\n", ret);

	char buf[100],b[50];
	int r;
	while(1)
	{
		printf("Message> "); scanf("%s",buf);
		send(fd,buf,strlen(buf),0);
		if(strncmp(buf, "exit", 4) == 0) break;
		r = recv(fd,b,50,0);
		if(r > 0)
		{
			b[r] = 0; printf("\r\n%s\r\n",b);
		}

	}
	close(fd);
}
