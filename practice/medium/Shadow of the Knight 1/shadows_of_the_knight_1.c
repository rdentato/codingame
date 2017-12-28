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

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    scanf("%d%d", &W, &H);
    int N; // maximum number of turns before game over.
    scanf("%d", &N);
    int X0;
    int Y0;
    scanf("%d%d", &X0, &Y0);
    int MIN_X, MIN_Y;
    int MAX_X, MAX_Y;
    // game loop
    MIN_X = W;
    MIN_Y = H;
    MAX_X = 0;
    MAX_Y = 0;
    while (1) {
        char bombDir[4]; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        scanf("%s", bombDir);
        dbg_msg("DIR: %s\n",bombDir);
        char *c;
        c = bombDir;
        dbg_msg("(%d %d) ->",X0,Y0);
        switch(*c) {
            case 'U' : if (Y0 < MIN_Y) {MIN_Y = Y0-1; dbg_msg(" {minY:%d} ",MIN_Y); }
                       Y0 = (MAX_Y+(Y0-1)) / 2;
                       c++; break;
            case 'D' : if (Y0 > MAX_Y) {MAX_Y = Y0+1; dbg_msg(" {maxY:%d} ",MAX_Y); }
                       Y0 = (MIN_Y+(Y0+1)) / 2;
                       c++; break;
        }

        switch(*c) {
            case 'L' : if (X0 < MIN_X) {MIN_X = X0-1; dbg_msg(" {minX:%d} ",MIN_X); }
                       X0 = (MAX_X+(X0-1)) / 2;
                       break;
            case 'R' : if (X0 > MAX_X) {MAX_X = X0+1; dbg_msg(" {maxX:%d} ",MIN_X); }
                       X0 = (MIN_X+(X0+1)) / 2;
                       break;
        }
        dbg_msg("(%d %d)  MIN: (%d,%d)\n",X0,Y0,MIN_X,MIN_Y);
        
        if (X0 >= W) X0=W-1;
        if (Y0 >= H) Y0=H-1;

        printf("%d %d\n",X0, Y0);
    }

    return 0;
}