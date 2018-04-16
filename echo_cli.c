#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
//#define SIZE 2048
//#define BUFSIZE = 4096
 
int main()
{  
   unsigned char buff2[1024],buff[1024]="hello,I am client";
   int i,j=0;
   int port=58914;
    int sin_len;
    int socket_descriptor;
    struct sockaddr_in sin;
    bzero(&sin,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=inet_addr("127.0.0.1");
    sin.sin_port=htons(port);
    sin_len=sizeof(sin);
    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
//   fread(buff,sizeof(unsigned char),1024,fp);
sendto(socket_descriptor,buff,18,0,(struct sockaddr *)&sin,sin_len);
i=recvfrom(socket_descriptor,buff2,1024,0,NULL,NULL);
printf("Receive echo:%s\n",buff2);


   close(socket_descriptor);
}
