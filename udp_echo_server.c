#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char** argv) 
{
	int sockfd;
	int recv_len,addr_len;
	char buff[256];
	int  bufflen=256;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //#define INADDR_ANY   ((unsigned long int) 0x00000000)
	servaddr.sin_port = htons(8888);
	addr_len=sizeof(servaddr);
	/* bind address and port to socket */
	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind error");
		exit(1);
	}
	
	char add_buff[32];
	sprintf(add_buff,"Oh,I am a server of BaiduYun.");
	while(1)
	{
		recv_len = recvfrom(sockfd, buff, bufflen, 0, (struct sockaddr *)&cliaddr, &addr_len);
		int i;
		for(i=0;i<sizeof(add_buff);i++)
			buff[recv_len+i]=add_buff[i];
		if( recv_len > 0 )
			sendto(sockfd, buff, recv_len+32, 0, (struct sockaddr *)&cliaddr, addr_len);		 	

	}
	return 0;
}
