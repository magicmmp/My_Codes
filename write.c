#include <stdio.h>
 
int main()
{
   FILE *fp = NULL;
 
   fp = fopen("test.txt", "w+");
   fprintf(fp, "1This is testing for fprintf...\n");
   fputs("2This is testing for fputs...\n", fp);
   fclose(fp);
}
