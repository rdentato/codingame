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


char perm[10]; // even in max for N is 6

char seqs[10][12];
char seq[120];

/*
** Geneate the *next* permutation in lexicographic order. See:
** https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order
*/
int nextperm(int n, char *a)
{
    int k, l;
    char c;
    // Search for largest k such that a[k] < a[k+1]
    k = n-2;
    while (k>=0 && a[k] >= a[k+1]) k--;
    if (k<0) return 0;
    l = n-1;
    while (l>k && a[k] >= a[l]) l--;
    c = a[k]; a[k] = a[l]; a[l] = c;
    
    k++; l = n-1;
    while (k<l) {
        c = a[k] ; a[k] = a[l]; a[l] = c;
        k++; l--;
    }
    
    _dbg_do ({
        for (int i = 0; i < n; i++) {
            dbg_msg("%d ",perm[i]);
        }
        dbg_msg("\n");
    })
    
    return 1;   
}

void merge(char *dst, char *src)
{
    char *dst_ptr;
    char *src_ptr;
    
    dst_ptr = dst;
    src_ptr = src;
    
    while (1) {
        _dbg_msg("[%s][%s]\n",dst_ptr,src_ptr);
        // Search first occurence of first char of src in dst
        while (*dst_ptr && (*dst_ptr != *src_ptr)) dst_ptr++;
        if (*dst_ptr == '\0') {
            while (*src_ptr) *dst_ptr++ = *src_ptr++;
            *dst_ptr = '\0';
            return;
        }
        else { // First char found, check the others
            char *s = src_ptr+1;
            char *d = dst_ptr+1;
        
            while (*s && *d && (*s == *d)) {
                s++; d++;
            }
            if (*s == '\0') return; // src is already in dst
            if (*d == '\0') {
                // Next loop will copy the rest of src and return
                src_ptr = s; dst_ptr = d;
            }
            else  {
                dst_ptr++; // check next position
            }
        }
    }
}

int main()
{
    int N;
    int min;
    int len;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", &seqs[i]);
        _dbg_msg("%d: %s\n",i,seqs[i]);
    }
    
    // First permutation
    for (int i = 0; i < N; i++) perm[i] = i;   
    
    min = 1000;
    do {
        dbg_do({
            for (int i=0; i < N; i++) {
              _dbg_msg("%s ",seqs[perm[i]]);
            }
            dbg_msg("\n");
        })
        seq[0] = '\0';
        for (int i=0; i < N; i++) {
          merge(seq,seqs[perm[i]]);
        }
        len = strlen(seq);
        _dbg_msg("%2d %s\n",len,seq);
        if (len < min) min = len;
        
    } while (nextperm(N,perm));  // next permutation

    printf("%d\n",min);

    return 0;
}