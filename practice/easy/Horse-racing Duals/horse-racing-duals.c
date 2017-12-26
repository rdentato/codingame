#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
 
#define _dbg_msg(...)
#define _dbg_do(x)

#ifndef NDEBUG
#define dbg_msg(...) fprintf(stderr,__VA_ARGS__)
#define dbg_do(x) x  
#else
#define dbg_msg(...)  
#define dbg_do(x)
#endif

int icmp(void *a, void *b)
{
    return(*((uint32_t *)a) - *((uint32_t *)b));
}

int main()
{
    uint32_t *values;
    int min;
    int N;
    scanf("%d", &N);
    
    // Get the N values
    values = malloc(N*sizeof(uint32_t));
    assert(values);
    for (int i = 0; i < N; i++) {
        scanf("%d", values+i);
    }

    _dbg_do({
      for (int i = 0; i < N; i++) {
          dbg_msg("val[%d] = %d\n", i, values[i]);
      }
    })
    
    // Sort the array
    qsort(values, N, sizeof(uint32_t), icmp);
    
    _dbg_do({
      for (int i = 0; i < N; i++) {
          dbg_msg("val[%d] = %d\n", i, values[i]);
      }
    })
    
    min = values[N-1]  + 1; // Surely larger than any difference
    
    // the lowest must be the difference between a number and 
    // its successor.

    for (int i = 0; i < N-1; i++) {
        int d = values[i+1] - values[i];
        _dbg_msg("%d\n",d);
        if (min > d) min = d;
    }
    
    printf("%d\n",min);

    free(values);
    return 0;
}