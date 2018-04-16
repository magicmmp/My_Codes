#include<stdio.h>
void int_to_hex(unsigned char* s,int w,int bits,char* s2,int p2,int p3)
{unsigned long int x;
 int i,j;
 int c1,bit1,c2,bit2;
 unsigned char c;
 c1=w/8;c2=(w+bits-1)/8;
 bit1=w%8;bit2=7-(w+bits-1)%8;x=0;c=0;
c=s[c1]<<bit1;//bit1,bit2 are unused bits.
 if(c1==c2)
{c=c>>(bit1+bit2);x=x+c; }
 else
{
c=c>>bit1;x=x+c;
  if(c1+1<c2)
  for(i=c1+1;i<c2;i++)
   { x=x<<8;x=x+s[i];}
  x=x<<(8-bit2);
  x=x+(s[c2]>>bit2); }
for(i=p3;i>=p2;i--)
{c=x%16;
 if(c>=0&&c<=9)s2[i]=c+'0';
 else s2[i]=c+55;
 x=x>>4;  }
} 
int main()
{
   char s[97]="01B79E7F200FC3F0 TIGER 0: EW: ChID: 00 tacID: 0 Tcoarse: 0000 Ecoarse: 000 Tfine: 000 Efine: 000";
   unsigned char cc[8]={0x01,0xB7,0xFE,0x88,0x22,0x4F,0xC0,0x11};
   FILE *fp = NULL;
   unsigned char buff[1025],buff2[1025];
   int i,j=0;
   fp = fopen("FEB0_bin.dat", "rb");
   fread(buff,sizeof(unsigned char),1024,fp);
for(i=0;i<1016;i=i+8)
for(j=0;j<8;j++)
{buff2[i+j]=buff[i+7-j];  }
for(i=0;i<1024;i++)
{
   printf("%02X ",buff2[i]);
    if((i+1)%8==0)
      printf("\n");}
printf("%s\n",s);
//for(i=0;i<8;i++)
//cc[i]=buff2[i];
for(i=0;i<8;i++)
printf("%02X",cc[i]);
printf("\n");
int_to_hex(cc,5,3,s,23,23);//tiger
int_to_hex(cc,10,6,s,36,37);//chid
int_to_hex(cc,16,2,s,46,46);//tacid
int_to_hex(cc,18,16,s,57,60);//tcoase
int_to_hex(cc,34,10,s,71,73);//ecoase
int_to_hex(cc,44,10,s,82,84);//tfine
int_to_hex(cc,54,10,s,93,95);//efine
printf("%s\n",s);
   fclose(fp);
}
