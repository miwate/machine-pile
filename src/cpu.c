#include <../prot/cpu.h>


/* Met le contenu du haut de la pile à l’adresse x et décrémente SP*/
void pop(Processeur *cpu, int x)
{
    cpu->SP--;
    cpu->memoire[x] = cpu->memoire[cpu->SP];
}

/* Met le contenu du haut de la pile -1 à l’adresse n, où n est la valeur du sommet de la pile décrémente SP de deux*/
void ipop(Processeur *cpu)
{
    cpu->SP -= 2;
    int n = cpu->memoire[cpu->SP];
    cpu->memoire[n] = cpu->memoire[cpu->SP - 1];
}

/* empile le contenu de l’adresse x (et donc incrémente ensuite SP) */
void push(Processeur *cpu, int x)
{
    cpu->memoire[cpu->SP] = cpu->memoire[x];
    cpu->SP++;
}

/* empile la valeur i (et donc incrémente ensuite SP) */
void ipush(Processeur *cpu, int i)
{
    cpu->memoire[cpu->SP] = i;
    cpu->SP++;
}

/* additionne adr au registre PC (adr peut être négatif) */
void jmp(Processeur *cpu, int adr)
{
    cpu->PC += adr;
}

/* dépile un élément. Si celui-ci n’est pas nul, additionne adr au registre PC */
void jnz(Processeur *cpu, int adr)
{
    cpu->SP--;
    if (cpu->memoire[cpu->SP] != 0)
    {
        cpu->PC += adr;
    }
}