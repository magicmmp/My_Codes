#include <stdio.h>
#include <string.h>
int main()
{
   unsigned char buff[40];
   unsigned int cmd[5]={0x5656512E,343,221,66,533};
   int i;
for(i=0;i<5;i++)
printf("%08X\n",cmd[i]);
memcpy(buff,&cmd,sizeof(cmd)); 
for(i=0;i<20;i++)
printf("%02X",buff[i]);

sprintf(buff,"%X",cmd);
for(i=0;i<40;i++)
printf("%s",buff);

}
