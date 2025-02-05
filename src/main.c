#include "../prot/asmHex.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Erreur - Aucun argument spécifié. Arrêt du programme.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++){
        FILE *input = fopen(argv[i], "r");
        if (input == NULL){
            printf("Erreur - Fichier non trouvé : %s.\n", argv[i]);
            return 1;
        }

        FILE *output = fopen("hexa.txt", "w");
        if (output == NULL){
            printf("Erreur - Écriture impossible : hexa.txt.\n");
            fclose(input);
            return 1;
        }

        
        char erreur = 0;


        

        /* On convertit en code machine */
        while (fgets(ligne, sizeof(ligne), input)){
            num_ligne++;

            char instr_assem[32], etiquette[32], etiquette2[32];
            int valeur = 0;

            /* Cas : instruction valeur */
            if (sscanf(ligne, "%31s %d", instr_assem, &valeur) == 2){
                Instruction instruct = asm_vers_hex(instr_assem, valeur);
                if (instruct.code_num == -1){
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
            }

            /* Cas : étiquette instruction valeur */
            else if (sscanf(ligne, "%31[^:]: %31s %d", etiquette, instr_assem, &valeur) == 3){
                Instruction instruct = asm_vers_hex(instr_assem, valeur);
                if (instruct.code_num == -1){
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
            }

            /* Cas : étiquette instruction */
            else if (sscanf(ligne, "%31[^:]: %31s", etiquette, instr_assem) == 2){
                Instruction instruct = asm_vers_hex(instr_assem, 0);
                if (instruct.code_num == -1){
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
            }

            /* Cas : étiquette instruction étiquette */
            else if (sscanf(ligne, "%31[^:]: %31s %31s", etiquette, instr_assem, etiquette2) == 3){
                valeur = get_ligne(etiquette2) - num_ligne - 1;
                Instruction instruct = asm_vers_hex(instr_assem, valeur);
                if (instruct.code_num == -1){
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
            } 

            /* Cas : instruction étiquette */
            else if (sscanf(ligne, "%31s %31s", instr_assem, etiquette2) == 2){
                valeur = get_ligne(etiquette2) - num_ligne - 1;
                Instruction instruct = asm_vers_hex(instr_assem, valeur);
                if (instruct.code_num == -1){
                    printf("Erreur - Instruction invalide : %s (ligne %d).\n", instr_assem, num_ligne);
                    erreur = 1;
                    break;
                }
                fprintf(output, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
            }
        }

        fclose(input);
        fclose(output);

        if (erreur){
            remove("hexa.txt");
            printf("Arrêt.\n");
            return 1;
        }

        /* Fait la passe au simulateur */
        simulateur("hexa.txt");
    }

    return 0;
}
