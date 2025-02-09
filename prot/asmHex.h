#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Code assembleur vers Hexadécimal */
#ifndef ASMHEX_H
#define ASMHEX_H

/* -- Structures -- */
typedef struct instructionHex
{
    int code_num;
    int adr_valeur;
} InstructionHex;

typedef struct etiquette
{
    char nom_etiq[32];
    int ligne;
    struct etiquette *next;
} Etiquette;

/* On va l'appeler assembleur ensuite */
typedef struct asmHex
{
    struct etiquette *etiquettes;
} AsmHex;

/* -- Prototypes de fonctions -- */

/* Initialisation */
void initAsmHex(AsmHex *assembleur);

/* Convertir une instruction assembleur vers instruction machine */
InstructionHex asm_vers_hex(const char *_instr_assem, int _valeur);

/* Lit le fichier et trouve les étiquettes d'un code assembleur et empile dans l'assembleur */
void trouve_etiquettes(AsmHex *assembleur, const char *_fichier);

/* Donne la ligne d'une étiquette */
int getLigne(AsmHex *assembleur, const char *_nomEtiquette);

/* Lit le fichier et empile les instructions dans l'assembleur */
void asmVersHex(AsmHex *assembleur, const char *_fichierAsm);

/* Supprime les espaces et tabulations d'une chaîne de caractères */
void tondre_chaine(char *chaine);

/* Supprime les espaces et tabulations d'une étiquette mais garde la ligne intacte */
void tondre_etiq_ligne(char *ligne);

/* Si la ligne est vide, renvoie 1, sinon 0 */
int ligne_est_vide(char *ligne);


/* Libère la mémoire de l'assembleur */
void free_asm(AsmHex *assembleur);

#endif
