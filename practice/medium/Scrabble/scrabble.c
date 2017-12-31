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

#define MAX_LETTERS 10

typedef struct {
   int32_t pos;
   char sig[8];
   char word[8];
} dct_entry;

typedef struct {
   uint32_t N;
   dct_entry entries[0];
} dct_t;

dct_t *dictionary = NULL;

void sig(char *s, char *w)
{
    char *m;
    char  c;
    
    if (s != w) strcpy(s,w);
    // Selection sort
    for (char *e=s; e[1] != '\0'; e++) {
        m=e;
        for (char *p=e+1; *p != '\0'; p++) {
            if (*p < *m) m = p;
        }
        c = *m; *m = *e; *e = c; 
    }
}

int dct_cmp(void *a, void *b)
{
  int n;
  dct_entry *entry_a = a;
  dct_entry *entry_b = b;
  
  _dbg_msg("cmp: [%s] [%s]\n",entry_a->sig, entry_b->sig);
  n = strcmp(entry_a->sig, entry_b->sig);
  if (n == 0) n = entry_a->pos - entry_b->pos;
  return n;
}
    
int dct_cmpsig(void *a, void *b)
{
  int n;
  dct_entry *entry_a = a;
  dct_entry *entry_b = b;
  
  _dbg_msg("cmp: [%s] [%s]\n",entry_a->sig, entry_b->sig);
  n = strcmp(entry_a->sig, entry_b->sig);
  return n;
}
    
dct_t *dct_load(FILE *f)
{
    char W[32];
    int len;
    dct_t *dct;
    
    int N;
    scanf("%d", &N); fgetc(stdin);
    
    dct = malloc(sizeof(dct_t) + N*sizeof(dct_entry));
    assert(dct);
    
    for (int i = 0; i < N; i++) {
        fgets(W, 31, f);
        len = strlen(W);
        if (W[len-1] == '\n') W[--len] = '\0';
        
        if (0 < len && len <= 7) { // skip empty lines and too long words
            strcpy(dct->entries[dct->N].word, W);
            dct->entries[dct->N].pos = dct->N;
            sig(dct->entries[dct->N].sig,dct->entries[dct->N].word);
            _dbg_msg("%6d %-7s (%s)\n",dct->entries[dct->N].pos,dct->entries[dct->N].sig,dct->entries[dct->N].word);
            dct->N++;
        }
    }
    
    qsort(dct->entries, dct->N, sizeof(dct_entry), dct_cmp);
    
   _dbg_do({
        for (int i=0; i<dct->N; i++)
            dbg_msg("%6d %-7s (%s)\n",dct->entries[i].pos,dct->entries[i].sig,dct->entries[i].word);
    })
    return dct;
}

dct_t *dct_free(dct_t *d)
{
  if (d) free(d);
  return NULL;
}

dct_entry *dct_search(dct_t *d, char *w)
{
    dct_entry entry;
    dct_entry *e;
     
    strcpy(entry.sig,w);
    
    e = bsearch(&entry, d->entries, d->N, sizeof(dct_entry), dct_cmpsig);
    return e;
}

void getsubword(char *word, int n,char *letters)
{
    char *c;
    c = word;
    for (int i = 0; i <= 7; i++)  {
       if (n & (1<<i)) {
           *c++ = letters[i];
           *c   = '\0';
       }
    }
}

            // a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z
char *pts = "\x01\x03\x03\x02\x01\x04\x02\x04\x01\x08\x05\x01\x03\x01\x01\x03\x0A\x01\x01\x01\x01\x04\x04\x08\x04\x0A";

int points(char *w)
{
  int pnt = 0;
  
  while (*w) {
      if ('a' <= *w && *w <= 'z') {
          pnt += pts[*w-'a'];
      }
      w++;
  }
  return pnt;
}

int main()
{
    
    char WORD[MAX_LETTERS];
    char LETTERS[MAX_LETTERS];
    
    int        max_pts = 0;
    dct_entry *max_entry = NULL;
    dct_entry *entry     = NULL;
    
    dictionary=dct_load(stdin);
    fgets(LETTERS, MAX_LETTERS, stdin);
    
    // Remove '\n' (if present) and ensure all chars after first '\0' are '\0' as well.
    for (int i = 0; i<9; i++) {
        if (LETTERS[i] == '\n' || (i>0 && LETTERS[i-1] == '\0'))
            LETTERS[i] = '\0';
    }
    _dbg_msg("letters: %s\n",LETTERS);

    sig(LETTERS,LETTERS);
    _dbg_msg("letters: %s\n",LETTERS);
  
    for (int i=1; i <= 127; i++) {
        int pts;
        getsubword(WORD,i,LETTERS);
        pts = points(WORD);
        entry = dct_search(dictionary, WORD);
        _dbg_msg("%d %s %d %d\n",i,WORD, pts,!!entry);
        if (entry) {
            if (pts > max_pts || (pts == max_pts && entry->pos < max_entry->pos)) {
                max_entry = entry;
                max_pts = pts;
            }
        }
    }
  
    if (max_entry) {
        while (max_entry > dictionary->entries && (strcmp(max_entry[0].sig,max_entry[-1].sig) == 0))
          max_entry--;
        printf("%s\n",max_entry->word);
    }
    else printf("invalid word\n");
      
    dictionary = dct_free(dictionary);
    return 0;
}