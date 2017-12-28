#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char ch[30][30*30];
int main()
{
    int L;
    int H;
    int N;
    int c;
    char T[256];
    char ROW[1024];
    char *t;
    
    scanf("%d", &L); fgetc(stdin);
    scanf("%d", &H); fgetc(stdin);
    if (L <= 0 || 30 <= L) return 1;
    if (H <= 0 || 30 <= H) return 1;
    
    fgets(T,256,stdin);
    for (int i = 0; i < H; i++) {
        fgets(ROW,1024,stdin);
        strcpy(ch[i],ROW);
        //fprintf(stderr,"%s",ch[i]);
    }
    
    for (int i=0; i< H; i++) {
        for (char *t = T; *t && *t != '\n' ; t++) {
           c = *t;
           //fprintf(stderr,"%d",c);
           c = toupper(c);
           if (c < 'A'  || 'Z' < c) c = 'Z'+1;
           c -= 'A';
           //fprintf(stderr," %d\n",c);
           for (int j=0; j<L; j++) {
               putchar(ch[i][c*L+j]);
           }  
        }
        putchar('\n');
    }
}