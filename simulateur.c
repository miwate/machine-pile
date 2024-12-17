#include <stdio.h>
#include <string.h>
#define MEM_MAX 5000

typedef struct instruction {
    char code_num;
    int adr_valeur;
} Instruction;

typedef struct etiquette {
    char nom_etiq[32];
    int adr;
} Etiquette;

Etiquette etiq_list[512];
int nombre_etiq = 0;

int get_adr_from_etiq(const char *etiquette){
    for (int i=0; i<nombre_etiq; i++){
        if (strcmp(etiq_list[i].nom_etiq, etiquette) == 0) {
            return etiq_list[i].adr;
        }
    }
    return -1;
}

void add_etiq(const char *etiquette, int adr){
    strcpy(etiq_list[nombre_etiq].nom_etiq, etiquette);
    etiq_list[nombre_etiq].adr = adr;
    nombre_etiq++;
}

void simulateur(const char *input){
    FILE *hexa = fopen(input, "r");
    if (hexa == NULL){
        printf("Erreur - Fichier non trouvé : %s.\n", input);
        return;
    }
}

Instruction assembleur(const char instr_assem[], const int valeur){
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
        
        char ligne[127];
        char erreur = 0;
        int num_ligne = 0;

        // Boucle pour étiquettes et traduction (pour éviter de faire 2 boucles)
        while (fgets(ligne, sizeof(ligne), input)){
            num_ligne++;
            
            // Etiquettes
            if (strchr(ligne, ':')){
                char etiquette[32];
                if (sscanf(ligne, "%31s[^:]", etiquette) == 1){
                    add_etiq(etiquette, num_ligne);
                }
                continue;
            }
        
            char instr_assem[32];
            int valeur = 0;

            // Traduction -> assembleur
            if (sscanf(ligne, "%31s %d", instr_assem, &valeur) >= 1){
                Instruction instruct = assembleur(instr_assem, valeur);

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
            remove("hexa.txt");
            return 1;
        }

        simulateur("hexa.txt");

    }

    return 0;
}
