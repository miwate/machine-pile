#include "../prot/asmHex.h"

/* Initialisation */
void initAsmHex(AsmHex* assembleur){
    assembleur->etiquettes = NULL;
    assembleur->instructions = NULL;
    return;
}


/* Convertir une instruction assembleur vers instruction machine */
InstructionHex asm_vers_hex(const char* _instr_assem, const int _valeur) {
    InstructionHex instr_machine = {-1, _valeur};

    if (strcmp(_instr_assem, "pop") == 0) {
        instr_machine.code_num = 0;
    }
    else if (strcmp(_instr_assem, "ipop") == 0) {
        instr_machine.code_num = 1;
    }
    else if (strcmp(_instr_assem, "push") == 0) {
        instr_machine.code_num = 2;
    }
    else if (strcmp(_instr_assem, "ipush") == 0) {
        instr_machine.code_num = 3;
    }
    else if (strcmp(_instr_assem, "push#") == 0) {
        instr_machine.code_num = 4;
    }
    else if (strcmp(_instr_assem, "jmp") == 0) {
        instr_machine.code_num = 5;
    }
    else if (strcmp(_instr_assem, "jnz") == 0) {
        instr_machine.code_num = 6;
    }
    else if (strcmp(_instr_assem, "call") == 0) {
        instr_machine.code_num = 7;
    }
    else if (strcmp(_instr_assem, "ret") == 0) {
        instr_machine.code_num = 8;
    }
    else if (strcmp(_instr_assem, "read") == 0) {
        instr_machine.code_num = 9;
    }
    else if (strcmp(_instr_assem, "write") == 0) {
        instr_machine.code_num = 10;
    }
    else if (strcmp(_instr_assem, "op") == 0) {
        instr_machine.code_num = 11;
    }
    else if (strcmp(_instr_assem, "rnd") == 0) {
        instr_machine.code_num = 12;
    }
    else if (strcmp(_instr_assem, "dup") == 0) {
        instr_machine.code_num = 13;
    }
    else if (strcmp(_instr_assem, "halt") == 0) {
        instr_machine.code_num = 99;
    }

    return instr_machine;
}



/* Trouve les étiquettes d'un code assembleur */
void trouve_etiquettes(AsmHex* assembleur, const char* _fichier){
    FILE* fichier = fopen(_fichier, "r");
    if (fichier == NULL){
        printf("Fichier %s introuvable.\n", _fichier);
        return;
    }
    
    /* On récupère les étiquettes */
    int num_ligne = 0;
    char ligne[127];

    
    while (fgets(ligne, sizeof(ligne), fichier)){
        num_ligne++;

        if (strchr(ligne, ':')){
            char etiquette[32];

            if (sscanf(ligne, "%31[^:]:", etiquette) == 1){
                printf("Étiquette [%s].\n", etiquette);

                /* On sauvegarde l'étiquette dans l'assembleur */
                Etiquette* etiq = malloc(sizeof(Etiquette));
                if (etiq == NULL){
                    printf("Alloc mémoire impossible.\n");
                    fclose(fichier);
                    return;
                }

                /* Copie du nom, puis de sa ligne */
                strncpy(etiq->nom_etiq, etiquette, sizeof(etiq->nom_etiq)-1);
                etiq->nom_etiq[sizeof(etiq->nom_etiq)-1] = '\0';
                etiq->ligne = num_ligne;

                /* Insertion de l'étiquette dans pile */
                etiq->next = assembleur->etiquettes;
                assembleur->etiquettes = etiq;

            }
            continue;
        }
    }
    fclose(fichier);
}
