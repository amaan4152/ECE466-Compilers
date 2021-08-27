#ifndef __EXTDEF_H
#define __EXTDEF_H
#define BUFSIZE 4096
/*
    C = CHAR, S = SIGNED, I = INT, U = UNSIGNED
    L = LONG, D = DOUBLE, F = FLOAT, V = VOID
    0 => not marked with any signedness
*/
enum TYPE {C = 1, S, U, SHRT, I, UL, LL, ULL, L, D, LD, F, V, CMPLX, BOOL}; 
#endif 