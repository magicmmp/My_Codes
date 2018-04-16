#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SIZE 2048
//#define BUFSIZE = 4096
 
int main()
{  
   unsigned char buff[1024];
   int i,j=0;
   int port=58914;
    int sin_len;
    int socket_descriptor;
    struct sockaddr_in sin,cliaddr;
    bzero(&sin,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=htonl(INADDR_ANY);
    sin.sin_port=htons(port);
    sin_len=sizeof(sin);
    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
    bind(socket_descriptor,(struct sockaddr *)&sin,sizeof(sin));
//   fread(buff,sizeof(unsigned char),1024,fp);
while(1)
{

i=recvfrom(socket_descriptor,buff,1024,0,(struct sockaddr *)&cliaddr,&sin_len);
// printf("receive data from:%s,port:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
// printf("%s\n",buff);
//buff[0]='S';buff[1]='e';buff[2]='r';buff[3]=':';
sendto(socket_descriptor,buff,i,0,(struct sockaddr *)&cliaddr,sin_len);
}

   close(socket_descriptor);
}
