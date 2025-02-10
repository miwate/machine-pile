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


/* Initialise le cpu en mettant tout à 0 */
void initCpu(Processeur *cpu);

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

// retour de procédure. On dépile PC.
void ret(Processeur *cpu);

//demande à l’utilisateur de rentrer une valeur qui sera mise dans la variable à l’adresse x.
void read(Processeur *cpu, int x);

//affiche à l’écran le contenu de la variable d’adresse x.
void write(Processeur *cpu, int x);

//met au sommet de la pile un nombre aléatoire entre 0 et X-1
void randx(Processeur *cpu, int x);

// duplique le sommet de la pile
void dup(Processeur *cpu);

// arrête la simulation ; fin du programme
void halt(void);

//tests airthmétiques
void op(Processeur *cpu, int i);

//éxécute hexa.txt
void executerHexa(Processeur *cpu, int valeur, int instruction);

// lire hexa.txt
void lireExec(const char *nomFichier, Processeur *cpu);


#endif