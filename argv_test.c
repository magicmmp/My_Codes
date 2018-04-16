#include<stdio.h>

void size(void* buf)
{
printf("the size of the buf is %d\n",sizeof((int*)buf));

}




void main(int argc,char *argv[])  
{  
unsigned long int gemroc_command_words[12];
int len;
char addr[12];
sprintf(addr, "172.16.8.%d", atoi(argv[1])) ;
printf("IP : %s\n",addr);
printf("len=%d\n",sizeof(gemroc_command_words));
size(gemroc_command_words);
char cfg_filename[31];
sprintf(cfg_filename,"GEMROC_%d_def_cfg_LV_2018.txt",12) ;
printf("cfg_filename=%s\n",cfg_filename);
 printf("arg count=%d\n",argc);
    int i;
    for(i=1;i<argc;i++)  
    {  
        printf("argument %d is: %d \n",i,atoi(argv[i]));  
    }   
   }  

