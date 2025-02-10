#include "../prot/cpu.h"

/* Initialise le cpu en mettant tout à 0 */
void initCpu(Processeur *cpu)
{
    cpu->SP = 0;
    cpu->PC = 0;
    for (int i = 0; i < 5000; i++)
    {
        cpu->memoire[i] = 0;
    }
}

int tronquer(int valeur)
{
    short resultat = (short)(valeur % 65536); /*(%)on prend les 16bits de poids faible car de -32768 - 32767 il y a 65536 valeurs, on met short pour le bit de signe attention il faut (short)*/
    printf("[CPU] Warning : Perte de précision, valeur tronquée à %d\n", resultat);
    return resultat;
}

/* Met le contenu du haut de la pile à l’adresse x et décrémente SP*/
void pop(Processeur *cpu, int x)
{
    if (cpu->SP == 0)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est vide, impossible de depiler.\n");
        exit(1);
    }
    cpu->SP--;
    cpu->memoire[x] = cpu->memoire[cpu->SP];
}

/* Met le contenu du haut de la pile -1 à l’adresse n, où n est la valeur du sommet de la pile décrémente SP de deux*/
void ipop(Processeur *cpu)
{
    if (cpu->SP < 2)
    {
        fprintf(stderr, "[CPU] Erreur, pas assez d'element sur al pile.\n");
        exit(1);
    }
    int valeur = cpu->memoire[cpu->SP - 1];
    int adresse = cpu->memoire[cpu->SP - 2];
    cpu->memoire[adresse] = valeur;
    cpu->SP -= 2;
}

/* empile le contenu de l’adresse x (et donc incrémente ensuite SP) */
void push(Processeur *cpu, int x)
{
    if (cpu->SP >= 5000)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est pleine, impossible d'empiler.\n");
        exit(1);
    }
    cpu->memoire[cpu->SP] = cpu->memoire[x];
    cpu->SP++;
}
// empile le contenu de l’adresse n, où n est la valeur du sommet de la pile ;
void jpush(Processeur *cpu)
{
    if (cpu->SP == 0)
    {
        fprintf(stderr, "[CPU] Erreur, pile vide, impossible d'ipush.\n");
        exit(1);
    }
    int adresse = cpu->memoire[cpu->SP - 1];
    if (adresse < 0 || adresse >= 5000)
    {
        fprintf(stderr, "[CPU] Erreur, tentative de lecture hors mémoire avec ipush.\n");
        exit(1);
    }
    cpu->memoire[cpu->SP - 1] = cpu->memoire[adresse];
}

/* empile la valeur i (et donc incrémente ensuite SP) */
void pushi(Processeur *cpu, int i)
{
    if (cpu->SP >= 5000)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est pleine, impossible d'empiler.\n");
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
{
    if (cpu->SP == 0)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est vide, impossible de depiler.\n");
        exit(1);
    }
    cpu->SP--;
    if (cpu->memoire[cpu->SP] != 0)
    {
        cpu->PC += adr;
    }
}

void call(Processeur *cpu, int adr)
{
    if (cpu->SP >= 5000)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est pleine, impossible d'empiler PC.\n");
        exit(1);
    }
    cpu->memoire[cpu->SP] = cpu->PC;
    cpu->PC = cpu->PC + adr;
}

void ret(Processeur *cpu)
{
    if (cpu->SP == 0)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est vide, impossible de depiler.\n");
        exit(1);
    }
    cpu->SP--;
    cpu->PC = cpu->memoire[cpu->SP];
}

void read(Processeur *cpu, int x)
{
    if (x < 0 || x >= 5000)
    {
        fprintf(stderr, "[CPU] Erreur, l'adresse indique ne rentre pas dans la zone memoire de la pile\n");
        exit(1);
    }
    printf("[CPU] Entrez une valeur pour l'adresse %d : ", x);
    int y;
    scanf("%d", &y);
    if (y < -32768 || y > 32767)
    { /*on verifie si ça sort des limites des 2bits*/
        cpu->memoire[x] = tronquer(y);
    }
    else
    {
        cpu->memoire[x] = y;
    }
}

void write(Processeur *cpu, int x)
{
    printf("[CPU] Valeur de la variable à l'adresse %d : %d\n", x, cpu->memoire[x]);
}

void randx(Processeur *cpu, int x)
{
    if (cpu->SP >= 5000)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est pleine, impossible d'empiler.\n");
        exit(1);
    }
    if (x <= 0)
    {
        fprintf(stderr, "[CPU] Limite invalide x doit être strictement superieur à 1.\n"); // on ne peut pas prendre en nombre aléatoire entre 0 et négatif
        exit(1);
    }
    int valAlea = rand() % x;
    cpu->memoire[cpu->SP] = valAlea;
    cpu->SP++;
}

void dup(Processeur *cpu)
{
    if (cpu->SP >= 5000)
    {
        fprintf(stderr, "[CPU] Erreur, la pile est pleine, impossible de dupliquer et d'empiler.\n");
        exit(1);
    }
    if (cpu->SP == 0)
    {
        fprintf(stderr, "[CPU] La pile est vide on ne duplique rien.\n");
        exit(1);
    }
    cpu->memoire[cpu->SP] = cpu->memoire[cpu->SP - 1];
    cpu->SP++;
}

void halt(void)
{
    fprintf(stderr, "[CPU] Fin de l'exectution du programme\n");
    exit(1);
}

void op(Processeur *cpu, int i)
{
    switch (i)
    {
    case 0:
    { /*je met des {} apres chaque case pour que x soit local à chaque case sinon erreur*/
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        if (cpu->memoire[x] == cpu->memoire[cpu->SP])
        {
            cpu->memoire[x] = 1;
        }
        else
        {
            cpu->memoire[x] = 0;
        }
        break;
    }

    case 1:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        if (cpu->memoire[x] != cpu->memoire[cpu->SP])
        {
            cpu->memoire[x] = 1;
        }
        else
        {
            cpu->memoire[x] = 0;
        }
        break;
    }

    case 2:
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        if (cpu->memoire[x] >= cpu->memoire[cpu->SP])
        {
            cpu->memoire[x] = 1;
        }
        else
        {
            cpu->memoire[x] = 0;
        }
        break;
    case 3:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        if (cpu->memoire[x] <= cpu->memoire[cpu->SP])
        {
            cpu->memoire[x] = 1;
        }
        else
        {
            cpu->memoire[x] = 0;
        }
        break;
    }
    case 4:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        if (cpu->memoire[x] > cpu->memoire[cpu->SP])
        {
            cpu->memoire[x] = 1;
        }
        else
        {
            cpu->memoire[x] = 0;
        }
        break;
    }

    case 5:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        if (cpu->memoire[x] < cpu->memoire[cpu->SP])
        {
            cpu->memoire[x] = 1;
        }
        else
        {
            cpu->memoire[x] = 0;
        }
        break;
    }
    case 6:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        cpu->memoire[x] = cpu->memoire[x] | cpu->memoire[cpu->SP];
        break;
    }
    case 7:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        cpu->memoire[x] = cpu->memoire[x] ^ cpu->memoire[cpu->SP];
        break;
    }
    case 8:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        cpu->memoire[x] = cpu->memoire[x] & cpu->memoire[cpu->SP];
        break;
    }

    case 9:
    {
        if (cpu->SP < 1)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        int x = cpu->SP - 1;
        cpu->memoire[x] = ~cpu->memoire[x];
        break;
    }
    case 10:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        int a = cpu->memoire[x];
        int b = cpu->memoire[cpu->SP];
        int val = a + b;
        if (val < -32768 || val > 32767)
        { /*on verifie si ça sort des limites des 2bits*/
            cpu->memoire[x] = tronquer(val);
        }
        else
        {
            cpu->memoire[x] = val;
        }
        break;
    }
    case 11:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        int a = cpu->memoire[x];
        int b = cpu->memoire[cpu->SP];
        int val = a - b;
        if (val < -32768 || val > 32767)
        { /*on verifie si ça sort des limites des 2bits*/
            cpu->memoire[x] = tronquer(val);
        }
        else
        {
            cpu->memoire[x] = val;
        }
        break;
    }
    case 12:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        int a = cpu->memoire[x];
        int b = cpu->memoire[cpu->SP];
        int val = a * b;
        if (val < -32768 || val > 32767)
        { /*on verifie si ça sort des limites des 2bits*/
            cpu->memoire[x] = tronquer(val);
        }
        else
        {
            cpu->memoire[x] = val;
        }
        break;
    }
    case 13:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        int a = cpu->memoire[x];
        int b = cpu->memoire[cpu->SP];
        if (b == 0)
        {
            fprintf(stderr, "[CPU] Erreur, division par zero \n");
            exit(1);
        }
        int val = a / b;
        if (val < -32768 || val > 32767)
        { /*on verifie si ça sort des limites des 2bits*/
            cpu->memoire[x] = tronquer(val);
        }
        else
        {
            cpu->memoire[x] = val;
            break;
        }
    }
    case 14:
    {
        if (cpu->SP < 2)
        {
            fprintf(stderr, "[CPU] Erreur, pas assez de valeurs sur la pile .\n");
            exit(1);
        }
        cpu->SP--;
        int x = cpu->SP - 1;
        int a = cpu->memoire[x];
        int b = cpu->memoire[cpu->SP];
        int val = a % b;
        if (val < -32768 || val > 32767)
        { /*on verifie si ça sort des limites des 2bits*/
            cpu->memoire[x] = tronquer(val);
        }
        else
        {
            cpu->memoire[x] = val;
        }
        break;
    }
    case 15:
    {
        if (cpu->SP == 0)
        {
            fprintf(stderr, "[CPU] Erreur, pile vide pas possible d'inverser la valeur du sommet .\n");
            exit(1);
        }
        int x = cpu->SP - 1;
        cpu->memoire[x] = -cpu->memoire[x];
        break;
    }
    default:
        fprintf(stderr, "[CPU] code operation <0 ou >15 .\n");
        exit(1);
    }
}

void executerHexa(Processeur *cpu, int valeur, int instruction)
{
    switch (instruction)
    {
    case 0x00:
        pop(cpu, valeur);
        break;
    case 0x01:
        ipop(cpu);
        break;
    case 0x02:
        push(cpu, valeur);
        break;
    case 0x03:
        jpush(cpu);
        break;
    case 0x04:
        pushi(cpu, valeur);
        break;
    case 0x05:
        jmp(cpu, valeur);
        break;
    case 0x06:
        jnz(cpu, valeur);
        break;
    case 0x07:
        call(cpu, valeur);
        break;
    case 0x08:
        ret(cpu);
        break;
    case 0x09:
        read(cpu, valeur);
        break;
    case 0x0a:
        write(cpu, valeur);
        break;
    case 0x0b:
        op(cpu, valeur);
        break;
    case 0x0c:
        randx(cpu, valeur);
        break;
    case 0x0d:
        dup(cpu);
        break;
    case 0x63:
        halt();
        break;
    default:
        fprintf(stderr, "[CPU] code operation <0 ou >15 .\n");
        exit(1);
    }
}

void lireExec(const char *nomFichier, Processeur *cpu)
{
    FILE *f = fopen(nomFichier, "r");
    if (!f)
    {
        fprintf(stderr, "[CPU] Erreur d'ouverture du fichier %s\n", nomFichier);
        exit(1);
    }
    int instruction, valeur;
    while (fscanf(f, "%2x %4x", &instruction, &valeur) == 2)
    {
        executerHexa(cpu, valeur, instruction);
        cpu->PC++;
    }

    fclose(f);
}

/*int main(){
    Processeur cpu;
    cpu.SP=0;
    cpu.PC=0;
    lireExec("hexa.txt",&cpu);
}*/