#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef ASMHEX_H
    #define ASMHEX_H

    /* Fichier d'en-tête */
    /* Assembleur vers Hexadécimal */

    /* -- Structures -- */
    typedef struct instructionHex {
        char code_num;
        int adr_valeur;
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

    /* Trouve les étiquettes, ou plutôt cherche les étiquettes */
    void trouve_etiquettes(AsmHex* assembleur, const char* _fichier);

    /* Retrouver la ligne d'une étiquette */
    int getLigne(AsmHex* assembleur, Etiquette* etiquette);
    
    /* */
    InstructionHex asmVersHex(const char* _instr_assem, const int _valeur);


#endif
