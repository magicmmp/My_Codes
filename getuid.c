#include<unistd.h>
#include<stdio.h>
#include<sys/resource.h>

int main()
{
    uid_t uid=getuid();
    uid_t euid=geteuid();
    struct rlimit m;
    getrlimit(RLIMIT_FSIZE,&m);
    printf("file size limit: rlim_cur=%d bytes,rlim_max=%d bytes.\n",m.rlim_cur,m.rlim_max);
    printf("user id=%d, effective userid=%d\n",uid,euid);
    return 0;
}

