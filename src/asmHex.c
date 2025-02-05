#include "../prot/asmHex.h"

/* Définition des variables globales */
Etiquette etiq_list[512];
int nombre_etiq = 0;

/* Récupérer la ligne d'une étiquette */
int get_ligne(const char* _nom_etiq){
    for (int i=0; i<nombre_etiq; i++){
        if (strcmp(etiq_list[i].nom_etiq, _nom_etiq) == 0) return etiq_list[i].ligne;
    }
    return -1;
}

/* Fonction pour garder étiquette en mémoire */
void ajout_etiq_list(const char* _nom_etiq, const int _adr) {
    strcpy(etiq_list[nombre_etiq].nom_etiq, _nom_etiq);
    etiq_list[nombre_etiq].ligne = _adr;
    nombre_etiq++;
}

/* Convertir une instruction assembleur vers instruction machine */
Instruction asm_vers_hex(const char* _instr_assem, const int _valeur) {
    Instruction instr_machine = {-1, _valeur};

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
