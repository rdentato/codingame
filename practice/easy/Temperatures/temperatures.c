#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
    int temp = 9999;
    int n; // the number of temperatures to analyse
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int t; // a temperature expressed as an integer ranging from -273 to 5526
        scanf("%d", &t);
        int d = abs(t) - abs(temp);
        if (d < 0 || (d == 0 && t > temp)) {
            temp = t;
        }
    }

    if (temp == 9999) temp = 0;
    printf("%d\n",temp);

    return 0;
}