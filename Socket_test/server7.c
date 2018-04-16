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

int main(int argc, char** argv)
{
    int    socket_fd, connect_fd;
    struct sockaddr_in     servaddr;
    unsigned char *buf= new unsigned char[128*1024*1024];
	unsigned int sizeLeft,PackageSize=1024*1024;
	unsigned int ret,n=1;
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
    printf("\n======waiting for client's request======\n");
    //����ֱ���пͻ������ӣ���Ȼ���˷�CPU��Դ��
    if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
    }
    while(1){
//���ܿͻ��˴�����������
		// receive a package
		PackageSize=1024*1024*n;
		sizeLeft=PackageSize;
		while (sizeLeft > 0)
		{
			ret = recv(connect_fd, (char*)(buf+PackageSize-sizeLeft), sizeLeft,0) ;
			if (ret == -1)
			{
				std::cerr << "ERROR: recv data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}
    buf[1]=buf[0];
    buf[2]=n;
    sizeLeft=8;
		while (sizeLeft > 0)
		{
			//ret = send(skt, (void*)(buf+config.curPackageSize-sizeLeft), sizeLeft, 0) ;
			ret = send(connect_fd, (char*)buf, sizeLeft,0);
			if (ret == -1)
			{
				std::cerr << "ERROR: send data error. " << std::endl ;
				exit (1) ;
			}
			sizeLeft -= ret ;
		}
    for(int i=0;i<3;i++)
         printf(" %d",buf[i]);
    for(int i=3;i<26;i++)
         printf(" %c",buf[i]);
         printf("\n");
    if(n>=128)
    break;
    n=n*2;
    }
    delete []buf;
    close(connect_fd);
    close(socket_fd);
}
