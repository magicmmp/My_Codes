#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h>   
int port=8888;  
int main(int argc, char** argv) {  

    int socket_descriptor;
    char buf[20];
	char recvbuff[128];  
	sprintf(buf,"Hello,I am a client.");
    struct sockaddr_in address;
    bzero(&address,sizeof(address));  
    address.sin_family=AF_INET;
	printf("please input a server IP:\n");  
	char ipbuff[24];
	gets(ipbuff);
    address.sin_addr.s_addr=inet_addr(ipbuff);
    address.sin_port=htons(port);  
    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
    sendto(socket_descriptor,buf,sizeof(buf),0,(struct sockaddr *)&address,sizeof(address));
	int recvlen;
	recvlen=recvfrom(socket_descriptor, recvbuff, sizeof(recvbuff), 0, NULL, NULL);
      
    printf("recv %d bytes from echo server : %s\n",recvlen,recvbuff); 
    close(socket_descriptor);  
    printf("exit.\n");  
    exit(0);  
    return ;  
}  

