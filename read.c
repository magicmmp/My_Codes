#include <stdio.h>
 
int main()
{
   FILE *fp = NULL;
   unsigned char buff[1025],buff2[1025],s[97];
   int i,j=0;
   fp = fopen("FEB0_bin.dat", "rb");
   fb2 = fopen("data.txt", "wb" );
   fread(buff,sizeof(unsigned char),1024,fp);
for(i=0;i<1016;i=i+8)
for(j=0;j<8;j++)
{buff2[i+j]=buff[i+7-j];  }
for(i=0;i<1024;i++)
{
   printf("%02X ",buff2[i]);
    if((i+1)%8==0)
      printf("\n");}
   fclose(fp);
 
}

