#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define _dbg(...)
#define _dbg_do(x)

#ifndef NDEBUG
#define dbg(...) fprintf(stderr,__VA_ARGS__)
#define dbg_do(x) x  
#else
#define dbg(...)  
#define dbg_do(x)
#endif

#define outc(c) fputc(c,stdout)

/* returns the next bit (0 or 1) or -1 on EOF */

int getbit()
{
  static int c=0;
  static int n=0;
  int b;
  
  if (c == -1) return -1;
  
  if (n == 0)  {
      c = fgetc(stdin);
      _dbg("c: %d\n",c);
      n = 64;
  }
  
  if (c == EOF || c == '\n') {
      c = -1;
      return -1;
  }
  b = (c & n)?1:0;
  n >>= 1;
  return b;
}


int main()
{
    int  b; // 0 or 1
    int cur_b = -1;
    while (1) {
      b = getbit();
      _dbg("b: %d\n",b);
      if (b == -1) break;
      if (b != cur_b) {
          if (cur_b >= 0) outc(' '); // not the first character
          cur_b = b;
          outc('0');
          if (b == 0) outc('0');
          outc(' ');
      }
      outc('0');
    }

    return 0;
}