#include <stdio.h>
#include <string.h>

typedef struct instruction {
    char code_num;
    int adr_valeur;
} Instruction;

Instruction assembleur(const char instr_assem[], const int valeur) {
    Instruction instr_machine = {-1, valeur};

    if (strcmp(instr_assem, "pop") == 0) {
        instr_machine.code_num = 0;
    }
    else if (strcmp(instr_assem, "ipop") == 0) {
        instr_machine.code_num = 1;
    }
    else if (strcmp(instr_assem, "push") == 0) {
        instr_machine.code_num = 2;
    }
    else if (strcmp(instr_assem, "ipush") == 0) {
        instr_machine.code_num = 3;
    }
    else if (strcmp(instr_assem, "push#") == 0) {
        instr_machine.code_num = 4;
    }
    else if (strcmp(instr_assem, "jmp") == 0) {
        instr_machine.code_num = 5;
    }
    else if (strcmp(instr_assem, "jnz") == 0) {
        instr_machine.code_num = 6;
    }
    else if (strcmp(instr_assem, "call") == 0) {
        instr_machine.code_num = 7;
    }
    else if (strcmp(instr_assem, "ret") == 0) {
        instr_machine.code_num = 8;
    }
    else if (strcmp(instr_assem, "read") == 0) {
        instr_machine.code_num = 9;
    }
    else if (strcmp(instr_assem, "write") == 0) {
        instr_machine.code_num = 10;
    }
    else if (strcmp(instr_assem, "op") == 0) {
        instr_machine.code_num = 11;
    }
    else if (strcmp(instr_assem, "rnd") == 0) {
        instr_machine.code_num = 12;
    }
    else if (strcmp(instr_assem, "dup") == 0) {
        instr_machine.code_num = 13;
    }
    else if (strcmp(instr_assem, "halt") == 0) {
        instr_machine.code_num = 99;
    }

    return instr_machine;
}


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Erreur - Aucun argument spécifié. Arrêt du programme.\n");
        return 1;
    }

    for(int i=1; i<argc; i++){
        FILE *input = fopen(argv[i], "r");
        if (input == NULL){
            printf("Erreur - Fichier non trouvé : %s.\n", argv[i]);
            fclose(input);
            return 1;
        }

        FILE *output = fopen("hexa.txt", "w");
        if (output == NULL){
            printf("Erreur - Écriture impossible : %s.\n");
            fclose(output);
            return 1;
        }
        
        int valeur;
        int num_ligne = 0;
        char erreur = 0;
        char instr_assem[10];

        
    
        // conversion en assembleur
        while (fscanf(input, "%s %d", instr_assem, &valeur) == 2) {
            num_ligne++;

            Instruction instruct = assembleur(instr_assem, valeur);

            // erreur instruction
            if (instruct.code_num == -1) {
                printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                erreur = 1;
                break;
            }
            fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur);
        }

        fclose(input);
        fclose(output);

        if (erreur) {
            // supression du fichier
            remove("hexa.txt");
            return 1;
        }

        simulateur("hexa.txt");

    }

    return 0;
}