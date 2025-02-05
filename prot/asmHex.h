#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Code assembleur vers Hexadécimal */
#ifndef ASMHEX_H
    #define ASMHEX_H

    /* -- Structures -- */
    typedef struct instructionHex {
        int code_num;
        int adr_valeur;
        struct instructionHex* next;
    } InstructionHex;

    typedef struct etiquette {
        char nom_etiq[32];
        int ligne;
        struct etiquette* next;
    } Etiquette;

    /* On va l'appeler assembleur ensuite */
    typedef struct asmHex {
        struct etiquette* etiquettes;
        struct instructionHex* instructions;
    } AsmHex ;
    

    /* -- Prototypes de fonctions -- */
    
    /* Initialisation */
    void initAsmHex(AsmHex* assembleur);

    /* Lit le fichier et trouve les étiquettes d'un code assembleur et empile dans l'assembleur */
    void trouve_etiquettes(AsmHex* assembleur, const char* _fichier);

    /* Donne la ligne d'une étiquette */
    int getLigne(AsmHex* assembleur, const char* _nomEtiquette);
    
    /* Lit le fichier et empile les instructions dans l'assembleur */
    void asmVersHex(AsmHex *assembleur, const char *_fichierAsm);

#endif
