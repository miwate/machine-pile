/*
C'est un fichier main.
Il effectue ce qu'on attend d'un fichier main.
*/

#include "../prot/asmHex.h"
#include "../prot/cpu.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "[Main] Erreur : aucun argument spécifié.\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {

        /* Assembleur --> Hex */
        AsmHex assembleur;
        initAsmHex(&assembleur);

        trouve_etiquettes(&assembleur, argv[i]);
        asmVersHex(&assembleur, argv[i]);
        free_asm(&assembleur);

        printf("[Main] Traduction terminée %s.\n", argv[i]);

        /* Hex --> CPU */
        Processeur cpu;
        initCpu(&cpu);

        lireExec("hexa.txt", &cpu);
    }

    return 0;
}
