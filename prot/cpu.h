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

/* -- Protoytpes de fonctions -- */

/* Met le contenu du haut de la pile à l’adresse x et décrémente SP*/
void pop(Processeur *cpu, int x);

/* Met le contenu du haut de la pile -1 à l’adresse n, où n est la valeur du sommet de la pile décrémente SP de deux*/
void ipop(Processeur *cpu);

/* empile le contenu de l’adresse x (et donc incrémente ensuite SP); */
void push(Processeur *cpu, int x);

/* empile la valeur i (et donc incrémente ensuite SP); */
void pushi(Processeur *cpu, int i);

/* additionne adr au registre PC (adr peut être négatif); */
void jmp(Processeur *cpu, int adr);

/* dépile un élément. Si celui-ci n’est pas nul, additionne adr au registre PC */
void jnz(Processeur *cpu, int adr);

// empile le contenu de l’adresse n, où n est la valeur du sommet de la pile ;
void jpush(Processeur *cpu);

void ret(Processeur *cpu);

void read(Processeur *cpu, int x);

void write(Processeur *cpu, int x);

void randx(Processeur *cpu, int x);

void dup(Processeur *cpu);

void halt(void);

void op(Processeur *cpu, int i);


void executerHexa(Processeur *cpu, int valeur, int instruction);


void lireExec(const char *nomFichier, Processeur *cpu);


#endif