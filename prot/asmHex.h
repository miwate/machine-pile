#ifndef ASMHEX_H
    #define ASMHEX_H

    /* Fichier d'en-tête */
    /* Assembleur vers Hexadécimal */

    #include <stdio.h>
    #include <string.h>

    /* Structures */
    typedef struct instruction {
        char code_num;
        int adr_valeur;
    } Instruction;

    typedef struct etiquette {
        char nom_etiq[32];
        int ligne;
    } Etiquette;


    /* Variables externes */
    extern Etiquette etiq_list[512];
    extern int nombre_etiq;

    /* Prototypes de fonctions */
    int get_ligne(const char* _nom_etiq);
    void ajout_etiq_list(const char* _nom_etiq, const int _adr);
    Instruction asm_vers_hex(const char* _instr_assem, const int _valeur);


#endif
