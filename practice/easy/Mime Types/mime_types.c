#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

#define _dbg(...)
#define _dbg_do(x)

#ifndef NDEBUG
#define dbg(...) fprintf(stderr,__VA_ARGS__)
#define dbg_do(x) x  
#else
#define dbg(...)  
#define dbg_do(x)
#endif

char **mimetypes;
char *mimebuffer;

int N; // Number of elements which make up the association table.
int Q; // Number Q of file names to be analyzed.

int scmp(char **a, char **b)
{
  _dbg("%s == %s\n",*a,*b);
  return strcmp(*a,*b);
}

char *getext(char *fname)
{
  static char ext[40];
  char *t;
  int i = 0;
  t = strrchr(fname,'.');
  if (t) {
   while (*++t && !isspace(*t)) ext[i++] = toupper(*t);
  }
  ext[i] = '\0';
  _dbg("ext: %s\n",ext);
  return ext;
}
 
 
void loadmap(void)
{
    char *buf;
    buf = mimebuffer;
    int c;
    int i=0;
    mimetypes[0] = buf;
    while (1) {
        c = fgetc(stdin);
        if (c == EOF ||  c == '\0') break;
        _dbg("%c-%d\n",c,c);
        if (c == '\n') {
            if (buf > mimebuffer) {
              *buf++ = '\0';
              if (i == N-1) break;
              mimetypes[++i] = buf;
            }
        }
        else if (c == ' ' || c == '\t') {
            if (buf > mimebuffer && buf[-1] != '\0' ) {
                *buf++ = '\0';
            }
        }
        else *buf++ = c;
    }
    *buf= '\0';
}   


int main()
{
    char *type;
    char **t;
    char *ext;
    
    scanf("%d", &N);
    scanf("%d", &Q);
    _dbg("N: %d Q: %d\n",N,Q);
    
    mimetypes = malloc(N * sizeof(char *));
    assert(mimetypes != NULL);
    mimebuffer = malloc(N * 100); // More than enough for 10 char for an extension and max 50 char for mime type
    assert(mimebuffer != NULL);
    _dbg("ALLOC OK\n");
    // Load the associaton table
    loadmap();
    
    // Move to uppercase (for case insesitive comparison)
    for (int i=0; i<N; i++) {
        char *buf;
        buf = mimetypes[i];
        while (*buf)  {*buf = toupper(*buf); buf++;}
        _dbg("%d: %s - %s\n",i, mimetypes[i],buf+1);
    }
    
    qsort(mimetypes, N, sizeof(char *),scmp);
    
    _dbg_do({
      char *buf;
      for (int i=0; i<N; i++) {
          buf = mimetypes[i];
          while (*buf) buf++;
          dbg("%d: %s - %s\n",i, mimetypes[i],buf+1);
      }
    })
    
    for (int i = 0; i < Q; i++) {
        char FNAME[501]; // One file name per line.
        fgets(FNAME, 501, stdin); // One file name per line.
        dbg("fname: %s",FNAME);
        ext = getext(FNAME);
        t = bsearch(&ext,mimetypes,N,sizeof(char *),scmp);
        if (t) {
            type = *t;
            while (*type) type++;
            type++;
        }
        else type = "UNKNOWN";
        
        _dbg("TYPE: %s\n",type);
        printf("%s\n",type);
        
    }

    // Write an action using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");


    // For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.

    return 0;
}