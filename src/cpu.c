#include <../prot/cpu.h>


/* Met le contenu du haut de la pile à l’adresse x et décrémente SP*/
void pop(Processeur *cpu, int x)
{   if (cpu->SP==0){
        fprintf(stderr,"Erreur, la pile est vide, impossible de depiler.\n");
        exit(1);
    }
    cpu->SP--;
    cpu->memoire[x] = cpu->memoire[cpu->SP];
}

/* Met le contenu du haut de la pile -1 à l’adresse n, où n est la valeur du sommet de la pile décrémente SP de deux*/
void ipop(Processeur *cpu)
{   if (cpu->SP==0){
        fprintf(stderr,"Erreur, la pile est vide, impossible de depiler.\n");
        exit(1);
    }
    cpu->SP -= 2;
    int n = cpu->memoire[cpu->SP];
    cpu->memoire[n] = cpu->memoire[cpu->SP - 1];
}

/* empile le contenu de l’adresse x (et donc incrémente ensuite SP) */
void push(Processeur *cpu, int x)
{   if (cpu->SP>=5000){
        fprintf(stderr,"Erreur, la pile est pleine, impossible d'empiler.\n");
        exit(1);
    }
    cpu->memoire[cpu->SP] = cpu->memoire[x];
    cpu->SP++;
}
//empile le contenu de l’adresse n, où n est la valeur du sommet de la pile ;
void jpush(Processeur *cpu){
    if (cpu->SP>=5000){
        fprintf(stderr,"Erreur, la pile est pleine, impossible d'empiler.\n");
        exit(1);
    }
    int x;
	x=cpu->memoire[cpu->SP-1];
	cpu->memoire[cpu->SP-1]=x;  

}

/* empile la valeur i (et donc incrémente ensuite SP) */
void pushi(Processeur *cpu, int i)
{   if (cpu->SP>=5000){
        fprintf(stderr,"Erreur, la pile est pleine, impossible d'empiler.\n");
        exit(1);
    }
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
{   if (cpu->SP==0){
        fprintf(stderr,"Erreur, la pile est vide, impossible de depiler.\n");
        exit(1);
    }
    cpu->SP--;
    if (cpu->memoire[cpu->SP] != 0)
    {
        cpu->PC += adr;
    }
}

void ret(Processeur *cpu){
    if (cpu->SP==0){
        fprintf(stderr,"Erreur, la pile est vide, impossible de depiler.\n");
        exit(1);
    }
	cpu->SP--;
	cpu->PC=cpu->memoire[cpu->SP]; 
	

}

void read(Processeur *cpu,int x){
    if (x< 0 || x >5000){
        fprintf(stderr,"Erreur, l'adresse indique ne rentre pas dans la zone memoire de la pile\n");
        exit(1);
    }
    printf("Entrez une valeur pour l'adresse %d : ",x);
    scanf("%d",&(cpu->memoire[x]));

}