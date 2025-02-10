/*
Cette partie du code gère la partie traduction du code assembleur vers du code hexadécimal.
D'où son nom explicite, asmHex
*/

#include "../prot/asmHex.h"

/* Initialisation */
void initAsmHex(AsmHex *assembleur)
{
    assembleur->etiquettes = NULL;
    return;
}

/* Donne la ligne d'une étiquette */
int getLigne(AsmHex *assembleur, const char *_nomEtiquette)
{
    /* Parcourir les étiquettes */
    Etiquette *etiq = assembleur->etiquettes;
    char trouve = 'n';

    while (etiq != NULL && trouve == 'n')
    {
        if (strcmp(etiq->nom_etiq, _nomEtiquette) == 0)
        {
            //printf("[Assembleur] Étiquette [%s] ligne %d.\n", _nomEtiquette, etiq->ligne);
            return etiq->ligne;
        }

        etiq = etiq->next;
    }

    if (trouve == 'n')
    {
        fprintf(stderr,"[Assembleur] Étiquette %s introuvable.\n", _nomEtiquette);
        exit(2);
    }

    return 0;
}

/* Convertir une instruction assembleur vers instruction machine */
InstructionHex asm_vers_hex(const char *_instr_assem, int _valeur)
{
    InstructionHex instr_machine = {-1, _valeur};

    if (_valeur < -32768 || _valeur > 32767)
    {
        fprintf(stderr, "[Assembleur] Warning : perte de précision %d -> %d \n", _valeur, _valeur & 0xFFFF);
        _valeur &= 0xFFFF;
    }

    if (strcmp(_instr_assem, "pop") == 0)
    {
        instr_machine.code_num = 0;
    }
    else if (strcmp(_instr_assem, "ipop") == 0)
    {
        instr_machine.code_num = 1;
    }
    else if (strcmp(_instr_assem, "push") == 0)
    {
        instr_machine.code_num = 2;
    }
    else if (strcmp(_instr_assem, "ipush") == 0)
    {
        instr_machine.code_num = 3;
    }
    else if (strcmp(_instr_assem, "push#") == 0)
    {
        instr_machine.code_num = 4;
    }
    else if (strcmp(_instr_assem, "jmp") == 0)
    {
        instr_machine.code_num = 5;
    }
    else if (strcmp(_instr_assem, "jnz") == 0)
    {
        instr_machine.code_num = 6;
    }
    else if (strcmp(_instr_assem, "call") == 0)
    {
        instr_machine.code_num = 7;
    }
    else if (strcmp(_instr_assem, "ret") == 0)
    {
        instr_machine.code_num = 8;
    }
    else if (strcmp(_instr_assem, "read") == 0)
    {
        instr_machine.code_num = 9;
    }
    else if (strcmp(_instr_assem, "write") == 0)
    {
        instr_machine.code_num = 10;
    }
    else if (strcmp(_instr_assem, "op") == 0)
    {
        instr_machine.code_num = 11;
    }
    else if (strcmp(_instr_assem, "rnd") == 0)
    {
        instr_machine.code_num = 12;
    }
    else if (strcmp(_instr_assem, "dup") == 0)
    {
        instr_machine.code_num = 13;
    }
    else if (strcmp(_instr_assem, "halt") == 0)
    {
        instr_machine.code_num = 99;
    }

    return instr_machine;
}

/* Supprime les espaces et tabulations d'une chaîne de caractères */
void tondre_chaine(char *chaine)
{
    int i = 0, j = 0;

    /* On passe la tondeuse */
    while (chaine[i])
    {
        if (chaine[i] != ' ' && chaine[i] != '\t')
        {
            chaine[j] = chaine[i];
            j++;
        }
        i++;
    }
    chaine[j] = '\0';
}

/* Supprime les espaces et tabulations d'une étiquette mais garde la ligne intacte */
void tondre_etiq_ligne(char *ligne)
{
    int i = 0, j = 0;
    char deux_points = 'n';

    /* On vérifie si la ligne contient ':' */
    while (ligne[i])
    {
        if (ligne[i] == ':')
        {
            deux_points = 'o';
            break;
        }
        i++;
    }

    /* Pas de ':' ne rien faire */
    if (deux_points == 'n')
        return;

    /* On passe la tondeuse sur l'étiquette (avant ':') */
    i = 0;
    while (ligne[i] && ligne[i] != ':')
    {
        if (ligne[i] != ' ' && ligne[i] != '\t')
        {
            ligne[j++] = ligne[i];
        }
        i++;
    }

    /* Le reste */
    while (ligne[i])
    {
        ligne[j++] = ligne[i++];
    }

    ligne[j] = '\0';
}

/* Si la ligne est vide, renvoie 1, sinon 0 */
int ligne_est_vide(char *ligne)
{
    while (*ligne)                      // donc si la ligne est completement vide jsute \0 alors on return direct
    {
        if (*ligne != '\n' && *ligne != ' ' && *ligne != '\t')
            return 0;
        ligne++;
    }
    return 1;
}

/* Lit le fichier et trouve les étiquettes d'un code assembleur et empile dans l'assembleur */
void trouve_etiquettes(AsmHex *assembleur, const char *_fichier)
{
    FILE *fichier = fopen(_fichier, "r");
    if (fichier == NULL)
    {
        fprintf(stderr ,"[Assembleur] Fichier %s introuvable.\n", _fichier);
        exit(2);
        return;
    }

    /* On récupère les étiquettes */
    int num_ligne = 0;
    char ligne[127];

    while (fgets(ligne, sizeof(ligne), fichier))
    {
        /* Passe à la ligne suivant si la ligne est vide */
        if (ligne_est_vide(ligne) == 1)
            continue;

        num_ligne++;

        if (strchr(ligne, ':'))
        {
            char etiquette[32];

            if (sscanf(ligne, "%31[^:]:", etiquette) == 1)
            {

                /* Supprimer les espaces bizarres et tabulations bizarres en cas de sujet bizarre */
                tondre_chaine(etiquette);

                //printf("[Assembleur] Étiquette [%s].\n", etiquette);

                /* On sauvegarde l'étiquette dans l'assembleur */
                Etiquette *etiq = malloc(sizeof(Etiquette));
                if (etiq == NULL)
                {
                    fprintf(stderr, "[Assembleur] Allocation mémoire impossible.\n");
                    fclose(fichier);
                    exit(2);
                    return;
                }

                /* Copie du nom, puis de sa ligne */
                strncpy(etiq->nom_etiq, etiquette, sizeof(etiq->nom_etiq) - 1);
                etiq->nom_etiq[sizeof(etiq->nom_etiq) - 1] = '\0';
                etiq->ligne = num_ligne;

                /* Insertion de l'étiquette dans la file */
                etiq->next = assembleur->etiquettes;
                assembleur->etiquettes = etiq;
            }
            continue;
        }
    }
    fclose(fichier);
}

/* Traduit le code assembleur et crée le fichier hexa.txt */
void asmVersHex(AsmHex *assembleur, const char *_fichierAsm)
{

    FILE *fichier = fopen(_fichierAsm, "r");
    if (fichier == NULL)
    {
        printf("[Assembleur] Fichier %s introuvable.\n", _fichierAsm);
        return;
    }

    FILE *hexaTxt = fopen("hexa.txt", "w");
    if (hexaTxt == NULL)
    {
        printf("[Assembleur] hexa.txt introuvable.\n");
        return;
    }

    /* On convertit en code machine */
    int num_ligne = 0;
    char ligne[127];
    char erreur = 'n';

    while (fgets(ligne, sizeof(ligne), fichier))
    {

        /* Passe à la ligne suivant si la ligne est vide */
        if (ligne_est_vide(ligne) == 1)
            continue;

        /* Supprime les espaces/tabulations d'une étiquette peu importe le nombre */
        tondre_etiq_ligne(ligne);

        num_ligne++;

        char instr_assem[32], etiquette[32], etiquette2[32];
        int valeur = 0;

        /* Cas : instruction valeur */
        if (sscanf(ligne, "%31s %d", instr_assem, &valeur) == 2)
        {
            InstructionHex instruct = asm_vers_hex(instr_assem, valeur);

            if (instruct.code_num == -1)
            {
                erreur = 'o';
                break;
            }
            fprintf(hexaTxt, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
        }

        /* Cas : étiquette instruction valeur */
        else if (sscanf(ligne, "%31[^:]: %31s %d", etiquette, instr_assem, &valeur) == 3)
        {
            InstructionHex instruct = asm_vers_hex(instr_assem, valeur);

            if (instruct.code_num == -1)
            {
                erreur = 'o';
                break;
            }
            fprintf(hexaTxt, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
        }

        /* Cas : étiquette instruction étiquette */
        else if (sscanf(ligne, "%31[^:]: %31s %31s", etiquette, instr_assem, etiquette2) == 3)
        {
            int ligne_etiquette = getLigne(assembleur, etiquette2);
            valeur = ligne_etiquette - num_ligne - 1;

            InstructionHex instruct = asm_vers_hex(instr_assem, valeur);

            if (instruct.code_num == -1)
            {
                erreur = 'o';
                break;
            }
            fprintf(hexaTxt, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
        }

        /* Cas : étiquette instruction */
        else if (sscanf(ligne, "%31[^:]: %31s", etiquette, instr_assem) == 2)
        {
            InstructionHex instruct = asm_vers_hex(instr_assem, 0);

            if (instruct.code_num == -1)
            {
                erreur = 'o';
                break;
            }
            fprintf(hexaTxt, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
        }

        /* Cas : instruction étiquette */
        else if (sscanf(ligne, "%31s %31s", instr_assem, etiquette2) == 2)
        {
            int ligne_etiquette = getLigne(assembleur, etiquette2);
            valeur = ligne_etiquette - num_ligne - 1;

            InstructionHex instruct = asm_vers_hex(instr_assem, valeur);

            if (instruct.code_num == -1)
            {
                erreur = 'o';
                break;
            }
            fprintf(hexaTxt, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
        }

        /* Cas : instruction seulement */
        else if (sscanf(ligne, "%31s", instr_assem) == 1)
        {
            InstructionHex instruct = asm_vers_hex(instr_assem, 0);

            if (instruct.code_num == -1)
            {
                erreur = 'o';
                break;
            }
            fprintf(hexaTxt, "%02x %04x\n", instruct.code_num, instruct.adr_valeur & 0xFFFF);
        }
    }
    

    if (erreur == 'o')
    {
        remove("hexa.txt");
        printf("[Assembleur] Erreur ligne %d: \"%s\".\n", num_ligne, ligne);
    }

    fclose(fichier);
    fclose(hexaTxt);
}

/* Libère la mémoire de l'assembleur */
void free_asm(AsmHex *assembleur)
{
    Etiquette *p = assembleur->etiquettes;
    Etiquette *q;

    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    
    assembleur->etiquettes = NULL;
}