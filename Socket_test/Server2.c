#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>
#include<netdb.h>
#include<string.h>
#include<iostream>
#include <sys/time.h>
#include <netinet/tcp.h>
#include <errno.h>
#define DEFAULT_PORT 8000
using namespace std;


ssize_t sendData(int skt, char *data, int len)
{
	sleep(1) ;
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
    int    socket_fd, connect_fd;
    struct sockaddr_in     servaddr;
    char *buf= new char[128*1024*1024];
	int sizeLeft,PackageSize=128*1024*1024;
	int ret ;
    //��ʼ��Socket
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
    printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    //��ʼ��
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP��ַ���ó�INADDR_ANY,��ϵͳ�Զ���ȡ������IP��ַ��
    servaddr.sin_port = htons(DEFAULT_PORT);//���õĶ˿�ΪDEFAULT_PORT

    //�����ص�ַ�󶨵����������׽�����
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    //��ʼ�����Ƿ��пͻ�������
    if( listen(socket_fd, 10) == -1){
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }

    for(int i=1008;i<1024;i++)
    printf(" %d",buf[i]);
    printf("\n======waiting for client's request======\n");
    while(1){
//����ֱ���пͻ������ӣ���Ȼ���˷�CPU��Դ��
        if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
        continue;
    }
//���ܿͻ��˴�����������
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

		for(int i=1008;i<1024;i++)
    printf(" %c",buf[i]);
    printf("\n");
    close(connect_fd);
    break;
    }
    delete []buf;
    close(socket_fd);
}
