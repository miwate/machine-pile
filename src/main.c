/*
C'est un fichier main.
Il effectue ce qu'on attend d'un fichier main.
*/

#include "../prot/asmHex.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Erreur - Aucun argument spécifié. Arrêt du programme.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {

        /* Assembleur --> Hex */
        AsmHex assembleur;
        initAsmHex(&assembleur);

        trouve_etiquettes(&assembleur, argv[i]);

        asmVersHex(&assembleur, argv[i]);

        free_asm(&assembleur);

        printf("Traduction terminée %s.\n", argv[i]);
        
    }

    return 0;
}
