#include<stdio.h>
#define SIZE 1024
#define BUFSIZE = 4096
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
{  char HB[71]="210000005B7C0000 TIGER 1: HB: Framecount: 0000B6F8 SEUcount: 00000000\n";
   char CW[71]="01B79E7F200FC3F0 TIGER 0: CW: ChID: 00  CounterWord: 0000000000000000\n";
   char EW[98]="01B79E7F200FC3F0 TIGER 0: EW: ChID: 00 tacID: 0 Tcoarse: 0000 Ecoarse: 000 Tfine: 000 Efine: 000\n";
   char* str;
   FILE *fp = NULL;
   FILE *fw = NULL;
   unsigned char buff[1025],buff2[1025];
   int i,j=0;
//   int Total_Data=0;
   fp = fopen("FEB0_bin.dat", "rb");
   fw = fopen("data.txt","w+");
   fread(buff,sizeof(unsigned char),1024,fp);
for(i=0;i<1016;i=i+8)
for(j=0;j<8;j++)
{buff2[i+j]=buff[i+7-j];  }
for(i=0;i<1024;i++)
{
   printf("%02X ",buff2[i]);
    if((i+1)%8==0)
      printf("\n");}
for(i=0;i<SIZE-8;i=i+8)
{str=buff2+i;
if((str[0]>>3)==0x04)
{
int_to_hex(str,0,64,HB,0,15);
int_to_hex(str,5,3,HB,23,23);//tiger
int_to_hex(str,33,16,HB,42,49);//framecount
int_to_hex(str,49,15,HB,61,68);//seucount
fwrite(HB,sizeof(unsigned char),70,fw); }
if((str[0]>>3)==0x08)
{
int_to_hex(str,0,64,CW,0,15);
int_to_hex(str,5,3,CW,23,23);//tiger
int_to_hex(str,10,6,CW,36,37);//chid
int_to_hex(str,40,24,CW,53,68);//counterword
fwrite(CW,sizeof(unsigned char),70,fw); }
if((str[0]>>3)==0)
{
int_to_hex(str,0,64,EW,0,15);
int_to_hex(str,5,3,EW,23,23);//tiger
int_to_hex(str,10,6,EW,36,37);//chid
int_to_hex(str,16,2,EW,46,46);//tacid
int_to_hex(str,18,16,EW,57,60);//tcoase
int_to_hex(str,34,10,EW,71,73);//ecoase
int_to_hex(str,44,10,EW,82,84);//tfine
int_to_hex(str,54,10,EW,93,95);//efine
fwrite(EW,sizeof(unsigned char),sizeof(EW)-1,fw); }  }
   fclose(fp);
   fclose(fw);
}
