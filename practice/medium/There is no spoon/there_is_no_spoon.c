#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define _dbg(...)
#define _dbg_do(x)

#ifndef NDEBUG
#define dbg(...) fprintf(stderr,__VA_ARGS__)
#define dbg_do(x) x  
#else
#define dbg(...)  
#define dbg_do(x)
#endif

uint32_t grid[32];
int width; // the number of cells on the X axis
int height; // the number of cells on the Y axis
    

int isnode(int x, int y)
{
    _dbg("x: %d y: %d\n",x,y);
    return (( y<height) && (x<width) && (grid[y] & (1 << x)));
}

void  printnode(int x, int y) 
{
    if (!isnode(x,y)) { x = y = -1; }
    printf("%d %d",x,y);
}

int findright(int x, int y)
{
   while (x++ < width)
     if (isnode(x,y)) return x;
   return -1;
}

int finddown(int x, int y)
{
   while (y++ < height)
     if (isnode(x,y)) return y;
   return -1;
}

int main()
{
    char line[32]; // width characters, each either 0 or .
    scanf("%d", &width);
    scanf("%d", &height); fgetc(stdin);
    
    for (int y = 0; y < height; y++) {
        fgets(line, 32, stdin); // width characters, each either 0 or .
        dbg("%s",line);
        grid[y] = 0;
        for (int x = 0; x < width; x++) {
            if (line[x] == '0')  grid[y] |= (1<<x);
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (isnode(x,y)) {
                printnode(x,y);
                fputc(' ',stdout);
                printnode(findright(x,y),y);
                fputc(' ',stdout);
                printnode(x,finddown(x,y));
                fputc('\n',stdout);
            }
        }
    }
    return 0;
}