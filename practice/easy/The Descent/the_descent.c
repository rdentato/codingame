#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
   int k;
   int max;
    // game loop
    while (1) {
        max=-1;
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain.
            scanf("%d", &mountainH);
            if (mountainH > max) { max = mountainH; k = i;}
        }
        // fprintf(stderr,"%d\n",k);

        printf("%d\n",k); // The index of the mountain to fire on.
    }

    return 0;
}