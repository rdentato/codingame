#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _dbg_msg(...)
#define _dbg_do(x)

#ifndef NDEBUG
#define dbg_msg(...) fprintf(stderr,__VA_ARGS__)
#define dbg_do(x) x  
#else
#define dbg_msg(...)  
#define dbg_do(x)
#endif

char line1[12048];
char line2[12048];

char *nextnum(char *s)
{
  while (*s && !isblank(*s)) s++; // skip current number
  while (*s &&  isblank(*s)) s++; // skip separator
  return s;
}

void describe(char *line, char *description)
{
   char *l_ptr = line;
   char *d_ptr = description;
   char c = '\0';
   int num = 0;
   int cnt = 0;
   int ret = 0;
   int prv = -1;
   dbg_msg("%s\n",line);
   
   while (*l_ptr) {
     num = atoi(l_ptr);
     if (num == prv) {
         cnt++;
     } else {
         if (cnt > 0) {
             _dbg_msg("[%d] (%d) #%d\n",num,prv,cnt);
             int l;
             if (d_ptr > description) {*d_ptr++= ' ';}
             l = sprintf(d_ptr,"%d %d",cnt,prv);
             d_ptr += l;
             _dbg_msg("{%s}\n",description);
         }
         cnt = 1;
         prv = num;
     }
     l_ptr = nextnum(l_ptr);
   }
   if (cnt > 0) {
     if (d_ptr > description) {*d_ptr++= ' ';}
     sprintf(d_ptr,"%d %d",cnt,num);
   }
}
 
int main()
{
    int R;
    scanf("%d", &R);
    int L;
    scanf("%d", &L);

    char *l1 = line1;
    char *l2 = line2;
    char *lt;
    
    sprintf(l1,"%d",R);
    while (--L) {
        _dbg_msg("%2d: ",L);
        describe(l1,l2);
        lt = l1; l1 = l2; l2 = lt; // swap
    }

    printf("%s\n",l1);

    return 0;
}