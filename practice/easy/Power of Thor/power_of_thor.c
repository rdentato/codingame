#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int sign(int x) {  return x?1-2*(x<0):0; }

char *move_str[] = {"NE", "N", "NW", "W", "X", "E", "SW", "S", "SE"};
#define move(dx,dy) move_str[(dy+1)*3+(dx+1)]
int main()
{
    int LX; // the X position of the light of power
    int LY; // the Y position of the light of power
    int TX; // Thor's starting X position
    int TY; // Thor's starting Y position
    int DX;
    int DY;
    
    scanf("%d%d%d%d", &LX, &LY, &TX, &TY); fgetc(stdin);
    fprintf(stderr," %d %d  %d %d\n",TX,TY,LX,LY);

    /*
         (TX - LX)
          0  1  2
         -1  0  1   
       0 NW  N  NE
       1  W  X  E
       2 SW  S  SE
    */

    // game loop
    while (1) {
        int E; // The level of Thor's remaining energy, representing the number of moves he can still make.
        scanf("%d", &E); fgetc(stdin);

        DX = sign(LX-TX);
        DY = sign(LY-TY);
        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");
        
        fprintf(stderr,"DX: %d DY: %d -> %s\n",DX,DY,move(DX,DY));
        TX += DX;
        TY += DY;
        fprintf(stderr,"(%d,%d)",TX,TY);
        
        printf("%s\n",move(DX,DY)); // A single line providing the move to be made: N NE E SE S SW W or NW
    }
}
