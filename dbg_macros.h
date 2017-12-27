/*
**  (CC0) Licenced as Public Domain by Remo Dentato
**                                     rdentato@gmail.com
**                                     https://github.com/rdentato)
** 
** Macros to help debugging.
** Just Copy/Paste the following lines in your code.
**
**    dbg(...)     Works a printf on stderr
**    dbg_do({ })  Performs the code inside { }
**
**    Prefix with _ to disable the instruction
*
*/

#define _dbg_msg(...)
#define _dbg_do(x)

#ifndef NDEBUG
#define dbg_msg(...) fprintf(stderr,__VA_ARGS__)
#define dbg_do(x) x  
#else
#define dbg_msg(...)  
#define dbg_do(x)
#endif


