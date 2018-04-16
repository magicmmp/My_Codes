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


ssize_t sendData(int skt, char *data, int len)
{
        struct iovec vec[1];
        vec[0].iov_base = (void *)data;
        vec[0].iov_len  = len;
        struct msghdr hdr = { 0, 0, vec, 1, 0, 0, 0 };
        ssize_t ret = sendmsg(skt, &hdr, MSG_NOSIGNAL);
        return ret;
}

ssize_t recvData(int skt, char *data, int len)
{
        struct iovec vec[1];
        struct msghdr hdr = { 0, 0, vec, 1, 0, 0, 0 };
        vec[0].iov_base = data;
        vec[0].iov_len  = len;
        int res = ::recvmsg(skt, &hdr, 0);
        return (ssize_t )res;
}


int main(int argc, char** argv)
{ ssize_t sendData(int skt, char *data, int len);
  ssize_t recvData(int skt, char *data, int len);
    char *buf= new char[128*1024*1024];
    for(int i=0;i<1024;i++)
        buf[i]='a'+i%26;
	int sizeLeft,sizeSent,PackageSize=128*1024*1024;
	int ret ;
    int    sockfd, n,rec_len;
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
    printf("\nsend msg to server: \n");

	gettimeofday(&t1,NULL) ;
    sizeLeft=PackageSize;
    sizeSent=0 ;
		while (sizeLeft > 0)
		{
			//ret = send(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			ret = sendData(sockfd, (char*)(buf+PackageSize-sizeLeft), sizeLeft);
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
			ret = recvData(sockfd, (char*)buf, sizeLeft) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: recv data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}
    gettimeofday(&t2,NULL) ;

    printf("Received :");
    for(int i=0;i<26;i++)
         printf(" %c",buf[i]);
         printf("\n");
    if(buf[0]=='A')
{ 	double timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
    printf ("Send --> Package:%d Bytes:%ld Speed:%.2fMB/s\n", PackageSize, sizeSent, (sizeSent/timeSpan)/(1024*1024)) ;
    }
    delete []buf;
    close(sockfd);
    exit(0);
}
