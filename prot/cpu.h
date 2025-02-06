#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Code Hex vers machine */
#ifndef CPU_H
#define CPU_H

/* -- Structures -- */
typedef struct processeur
{
    int PC;
    int SP;
    int memoire[5000];
    
} Processeur;

#endif