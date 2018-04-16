#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<iostream>
#include <unistd.h>
#include <sys/time.h>
#include <netinet/tcp.h>
#include <errno.h>
#define DEFAULT_PORT 8000
using namespace std;

int main(int argc, char** argv)
{
   unsigned char *buf= new unsigned char[128*1024*1024];
    for(int i=0;i<1024;i++)
        buf[i]='a'+i%26;
	unsigned int sizeLeft,sizeSent,PackageSize,n=1;
	unsigned int ret ;
    int    sockfd;
    struct sockaddr_in    servaddr;
    timeval t1, t2 ;


    if( argc != 2){
    printf("usage: ./client <ipaddress>\n");
    exit(1);
    }


    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(1);
    }


    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
    printf("inet_pton error for %s\n",argv[1]);
    exit(1);
    }


    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    exit(1);
    }

    printf("Before Send: \n");
    for(int i=0;i<26;i++)
         printf(" %c",buf[i]);
         printf("\n");
    printf("\nsend msg to server: \n");
for (PackageSize=1024*1024; PackageSize<=128*1024*1024; PackageSize=1024*1024*n)
	{
    sizeLeft=PackageSize;
    sizeSent=0 ;
    buf[0]=n;
    gettimeofday(&t1,NULL) ;
		while (sizeLeft > 0)
		{
			//ret = send(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			ret = send(sockfd, (char*)(buf+PackageSize-sizeLeft), sizeLeft,0);
			if (ret == -1)
			{
				std::cerr << "ERROR: send data error. " << std::endl ;
				exit (1) ;
			}
			sizeSent += ret ;
			sizeLeft -= ret ;
		}
        sizeLeft=8;
		while (sizeLeft > 0)
		{
			ret = recv(sockfd, (char*)buf, sizeLeft,0) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: recv data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}
    gettimeofday(&t2,NULL) ;
    printf("Received :");
    for(int i=0;i<3;i++)
         printf(" %d",buf[i]);
    for(int i=3;i<26;i++)
         printf(" %c",buf[i]);
         printf("\n");
    if(buf[0]==buf[2])
{ 	double timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
    printf ("Send --> Package:%d Time:%.6fS Speed:%.2fMB/s\n", sizeSent,timeSpan, (sizeSent/timeSpan)/(1024*1024)) ;
       }
       n=n*2; }
    delete []buf;
    close(sockfd);
    exit(0);
}
