#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define MEM_MAX 5000

typedef struct instruction {
    char code_num;
    int16_t adr_valeur;
} Instruction;

typedef struct etiquette {
    char nom_etiq[32];
    int16_t ligne;
} Etiquette;

Etiquette etiq_list[512];
int nombre_etiq = 0;

int16_t get_ligne_from_etiq(const char *etiquette) {
    for (int i = 0; i < nombre_etiq; i++) {
        if (strcmp(etiq_list[i].nom_etiq, etiquette) == 0) {

            printf("D : %s - %d\n", etiq_list[i].nom_etiq, etiq_list[i].ligne);
            return etiq_list[i].ligne;
        }
    }
    return -1;
}

void add_etiq(const char *etiquette, int adr) {
    strcpy(etiq_list[nombre_etiq].nom_etiq, etiquette);
    etiq_list[nombre_etiq].ligne = adr;
    nombre_etiq++;
}

void simulateur(const char *input) {
    FILE *hexa = fopen(input, "r");
    if (hexa == NULL) {
        printf("Erreur - Fichier non trouvé : %s.\n", input);
        return;
    }
    fclose(hexa);
}

Instruction assembleur(const char instr_assem[], const int16_t valeur) {
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Erreur - Aucun argument spécifié. Arrêt du programme.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *input = fopen(argv[i], "r");
        if (input == NULL) {
            printf("Erreur - Fichier non trouvé : %s.\n", argv[i]);
            fclose(input);
            return 1;
        }

        FILE *output = fopen("hexa.txt", "w");
        if (output == NULL) {
            printf("Erreur - Écriture impossible : %s.\n", argv[i]);
            fclose(output);
            return 1;
        }

        char ligne[127];
        char erreur = 0;
        int16_t num_ligne = 0;

        while (fgets(ligne, sizeof(ligne), input)) {
            num_ligne++;

            // Etiquettes
            if (strchr(ligne, ':')) {
                char etiquette[32];
                if (sscanf(ligne, "%31s[^:]", etiquette) == 1) {

                    //printf("etiquette- %s\n",etiquette);
                    add_etiq(etiquette, num_ligne);

                    //printf("A : %s - %d\n", etiquette, num_ligne);
                }
                continue;
            }
        }

        char instr_assem[32];
        char etiquette[32];
        char etiquette2[32];
        int16_t valeur = 0;

        //LALALA FAUT AJOUTER UN TRUC POUR LES ADRESSES DES ETIQUETTES, faut peut-être faire deux boucles au fina

        rewind(input);
        num_ligne = 0;

        while (fgets(ligne, sizeof(ligne), input)) {
            num_ligne++;

            // F1 Cas instruction valeur
            if (sscanf(ligne, "%31s %" SCNd16, instr_assem, &valeur) == 2) {

                //printf("%s - %d\n",instr_assem, valeur);
                Instruction instruct = assembleur(instr_assem, valeur);

                if (instruct.code_num == -1) {
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }

                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur);
            }

            // F2 Cas étiquette instruction valeur
            else if (sscanf(ligne, "%31[^:]: %31s %" SCNd16, etiquette, instr_assem, &valeur) == 3) {

                //fprintf(output, "B : %s - %d\n", etiquette, valeur);
                Instruction instruct = assembleur(instr_assem, valeur); 
                if (instruct.code_num == -1) {
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur);

            }

            // F3 Cas étiquette instruction (ipop, ipush, dup, halt)
            else if (sscanf(ligne, "%31[^:]: %31s", etiquette, instr_assem) == 2) {

                //fprintf(output, "C : %s - %s\n", etiquette, instr_assem);
                Instruction instruct = assembleur(instr_assem, 0); 

                if (instruct.code_num == -1) {
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur);

            }

            // F4 Cas étiquette instruction étiquette
            else if (sscanf(ligne, "%31[^:]: %31s %31s", etiquette, instr_assem, etiquette2) == 3) {

                valeur = get_ligne_from_etiq(etiquette2);
                valeur = valeur - num_ligne -1;
                Instruction instruct = assembleur(instr_assem, valeur); 

                if (instruct.code_num == -1) {
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur);

                //fprintf(output, "C : %s - %s - %s\n", etiquette, instr_assem, etiquette2);
            }

            // F5 Cas instruction étiquette
            else if (sscanf(ligne, "%31s %31s", instr_assem, etiquette2) == 2) {

// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

                valeur = get_ligne_from_etiq(etiquette2);
                //printf("% " SCNd16 , valeur);
                printf("num_ligne: %d\n" , num_ligne);
                valeur = valeur - num_ligne -1;

                Instruction instruct = assembleur(instr_assem, valeur); 
                
                if (instruct.code_num == -1) {
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur);

                //fprintf(output, "C : %s - %s\n", instr_assem, etiquette2);
            
            }                     
        }

        fclose(input);
        fclose(output);

        if (erreur) {
            //remove("hexa.txt");
            printf("Arrêt.\n");
            return 1;
        }

        simulateur("hexa.txt");
    }

    return 0;
}
