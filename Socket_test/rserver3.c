#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>
#include<netdb.h>
#include<rdma/rsocket.h>
#include<string.h>
#include<iostream>
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
	ssize_t ret = rsendmsg(skt, &hdr, MSG_NOSIGNAL);
	return ret;
}

ssize_t recvData(int skt, char *data, int len)
{
	struct iovec vec[1];
	struct msghdr hdr = { 0, 0, vec, 1, 0, 0, 0 };
	vec[0].iov_base = data;
	vec[0].iov_len  = len;
	int res = ::rrecvmsg(skt, &hdr, 0);
	return (ssize_t )res;
}


int main(int argc, char** argv)
{ ssize_t sendData(int skt, char *data, int len);
  ssize_t recvData(int skt, char *data, int len);
    int    socket_fd, connect_fd;
    struct sockaddr_in     servaddr;
    char *buf= new char[128*1024*1024];
	int sizeLeft,PackageSize=128*1024*1024;
	int ret ;
    //初始化Socket
    if( (socket_fd = rsocket(AF_INET, SOCK_STREAM, 0)) == -1 ){
    printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    //初始化
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。
    servaddr.sin_port = htons(DEFAULT_PORT);//设置的端口为DEFAULT_PORT

    //将本地地址绑定到所创建的套接字上
    if( rbind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    //开始监听是否有客户端连接
    if( rlisten(socket_fd, 10) == -1){
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    printf("\n======waiting for client's request======\n");
    while(1){
//阻塞直到有客户端连接，不然多浪费CPU资源。
        if( (connect_fd = raccept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
        continue;
    }
//接受客户端传过来的数据
		// receive a package
		sizeLeft=PackageSize;
		while (sizeLeft > 0)
		{
			ret = recvData(connect_fd, (char*)(buf+PackageSize-sizeLeft), sizeLeft) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: recv data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}
    buf[0]='A';
    sizeLeft=8;
		while (sizeLeft > 0)
		{
			//ret = send(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			ret = sendData(connect_fd, (char*)buf, sizeLeft);
			if (ret == -1)
			{
				std::cerr << "ERROR: send data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}
		for(int i=0;i<26;i++)
    printf(" %c",buf[i]);
    printf("\n");
    rclose(connect_fd);
    break;
    }
    delete []buf;
    rclose(socket_fd);
}
