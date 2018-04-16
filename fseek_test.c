#include <stdio.h>

int main(){   
    FILE *fp = NULL;
    fp = fopen("test.txt", "r+");  // ȷ±£ test.txt Î¼þÒ´´½¨
    fprintf(fp, "This is testing for fprintf...\n");   
    fseek(fp, 10, SEEK_SET);
    if (fputc(65,fp) == EOF) {
        printf("fputc fail");   
    }   
    fclose(fp);
}
