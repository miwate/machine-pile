#include <../prot/cpu.h>

int tronquer(int valeur){
    short resultat= (short)(valeur % 65536);  /*(%)on prend les 16bits de poids faible car de -32768 - 32767 il y a 65536 valeurs, on met short pour le bit de signe attention il faut (short)*/ 
    printf("warning : Perte de précision, valeur tronquée à %d\n", resultat);
    return resultat;
}

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
    if (x< 0 || x >=5000){
        fprintf(stderr,"Erreur, l'adresse indique ne rentre pas dans la zone memoire de la pile\n");
        exit(1);
    }
    printf("Entrez une valeur pour l'adresse %d : ",x);
    scanf("%d",&(cpu->memoire[x]));

}

void write(Processeur *cpu,int x){
	printf("valeur de la variable à l'adresse%d : %d ", x,cpu->memoire[x]);
	
}

void randx(Processeur *cpu,int x){
    if (cpu->SP>=5000){
        fprintf(stderr,"Erreur, la pile est pleine, impossible d'empiler.\n");
        exit(1);
    }
	 if (x <= 0) {
        fprintf(stderr,"limite invalide x doit etre strictement superieur a 1.\n"); //on ne peut pas prendre en nombre aléatoire entre 0 et négatif
        exit(1);
    }
	int valalea = rand()% x;
	cpu->memoire[cpu->SP] = valalea;
    cpu->SP++;

}

void dup(Processeur *cpu){
    if (cpu->SP>=5000){
        fprintf(stderr,"Erreur, la pile est pleine, impossible de dupliquer et d'empiler.\n");
        exit(1);
    }
    if (cpu->SP==0){
        fprintf(stderr," la pile est vide on ne duplique rien.\n");
        exit(1);
    }
	cpu->memoire[cpu->SP] = cpu->memoire[cpu->SP - 1]; 
    cpu->SP++; 

}

void op(Processeur *cpu,int i){
    switch(i){
        case 0 :{  /*je met des {} apres chaque case pour que x soit local à chaque case sinon erreur*/
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            } 
            cpu->SP--;
            int x=cpu->SP-1;
            if (cpu->memoire[x]==cpu->memoire[cpu->SP]){
                cpu->memoire[x]=1;
            }else{
                cpu->memoire[x]=0;
            }
            break;
        }

        case 1 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }  
            cpu->SP--;
            int x=cpu->SP-1;
            if (cpu->memoire[x]!=cpu->memoire[cpu->SP]){
                cpu->memoire[x]=1;
            }else{
                cpu->memoire[x]=0;
            }
            break;
        }

        case 2 :
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            } 
            cpu->SP--;
            int x=cpu->SP-1;
            if (cpu->memoire[x]>=cpu->memoire[cpu->SP]){
                cpu->memoire[x]=1;
            }else{
                cpu->memoire[x]=0;
            }
            break;
        case 3 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            } 
            cpu->SP--;
            int x=cpu->SP-1;
            if (cpu->memoire[x]<=cpu->memoire[cpu->SP]){
                cpu->memoire[x]=1;
            }else{
                cpu->memoire[x]=0;
            }
            break;
        }
        case 4 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            if (cpu->memoire[x]>cpu->memoire[cpu->SP]){
                cpu->memoire[x]=1;
            }else{
                cpu->memoire[x]=0;
            }
            break;
        }

        case 5 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            if (cpu->memoire[x]<cpu->memoire[cpu->SP]){
                cpu->memoire[x]=1;
            }else{
                cpu->memoire[x]=0;
            }
            break;
        }
        case 6 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            cpu->memoire[x]=cpu->memoire[x]|cpu->memoire[cpu->SP];
            break;
        }
        case 7 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            cpu->memoire[x]=cpu->memoire[x]^cpu->memoire[cpu->SP];
            break;
        }
        case 8 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            cpu->memoire[x]=cpu->memoire[x]&cpu->memoire[cpu->SP];
            break;
        }

        case 9 :{
            if (cpu->SP<1){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            int x=cpu->SP-1;
            cpu->memoire[x]= ~cpu->memoire[x];
            break;
        }
        case 10 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            int a = cpu->memoire[x];
            int b = cpu->memoire[cpu->SP];
            int val=a+b;
            if (val< -32768 || val> 32767){ /*on verifie si ça sort des limites des 2bits*/
                cpu->memoire[x]= tronquer(val);
            }else{
               cpu->memoire[x]=val;
            }  
            break;
        }
        case 11 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            int a = cpu->memoire[x];
            int b = cpu->memoire[cpu->SP];
            int val=a-b;
            if (val< -32768 || val> 32767){ /*on verifie si ça sort des limites des 2bits*/
                cpu->memoire[x]= tronquer(val);
            }else{
               cpu->memoire[x]=val;
            }
            break;
        }
        case 12 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            int a = cpu->memoire[x];
            int b = cpu->memoire[cpu->SP];
            int val=a*b;
            if (val< -32768 || val> 32767){ /*on verifie si ça sort des limites des 2bits*/
                cpu->memoire[x]= tronquer(val);
            }else{
               cpu->memoire[x]=val;
            }  
            break;
        }
        case 13 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            int a = cpu->memoire[x];
            int b = cpu->memoire[cpu->SP];
            if (b==0){
                fprintf(stderr,"Erreur, division par zero \n");
                exit(1);
            }
            int val=a/b;
            if (val< -32768 || val> 32767){ /*on verifie si ça sort des limites des 2bits*/
                cpu->memoire[x]= tronquer(val);
            }else{
               cpu->memoire[x]=val;  
            break;
        }
        case 14 :{
            if (cpu->SP<2){
                fprintf(stderr,"Erreur, pas assez de valeurs sur la pile .\n");
                exit(1);
            }
            cpu->SP--;
            int x=cpu->SP-1;
            int a = cpu->memoire[x];
            int b = cpu->memoire[cpu->SP];
            int val=a%b;
            if (val< -32768 || val> 32767){ /*on verifie si ça sort des limites des 2bits*/
                cpu->memoire[x]= tronquer(val);
            }else{
               cpu->memoire[x]=val;
            }
            break;
        }
    }
}
}
