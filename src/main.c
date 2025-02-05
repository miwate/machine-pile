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
        FILE *input = fopen(argv[i], "r");
        if (input == NULL)
        {
            printf("Erreur - Fichier non trouvé : %s.\n", argv[i]);
            return 1;
        }

        FILE *output = fopen("hexa.txt", "w");
        if (output == NULL)
        {
            printf("Erreur - Écriture impossible : hexa.txt.\n");
            fclose(input);
            return 1;
        }

        AsmHex assembleur;
        initAsmHex(&assembleur);

        trouve_etiquettes(&assembleur, argv[i]);

        asmVersHex(&assembleur, argv[i]);

        printf("Traduction terminée %s.\n", argv[i]);
        
        fclose(input);
        fclose(output);
    }
    
    return 0;
}
