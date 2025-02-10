# 🔨 Compilation

En cas de nécessité (normalement non).

Nous compilons à l’aide d’un Makefile.

Pour une compilation propre :

```bash
make re
```

# 👟 Éxécution d’un programme

Le programme assembleur à éxécuter doit être dans un format lisible par un éditeur de texte.

Pour lancer le programme contenu dans `foo.txt` :

```bash
./simulateur foo.txt
```

# 🧩 Syntaxe du langage assembleur

## Sensibilité à la casse

L’assembleur différencie les majuscules et les minuscules (`etiquette` ≠ `Etiquette`).

🤖 La mémoire de la machine à pile est constitué de 5000 cases d’entiers allant de -32 768 à 32 767, ainsi tout valeur en dehors de cet intervalle sera tronquer, toute tentative d’accès à une casse mémoire en dehors de [0;4999] et toute division par zéro provoquera une erreur.

## Indentation

Il est possible d’indenter autant que possible, y compris entre les étiquettes, instructions et variables (du moment que la ligne contient moins de 126 caractères).

 `ici     :         read    1000`     équivaut à `ici: read 1000`.

Il n’est cependant pas possible de tout coller.

⚠️`push#` ≠ `push #` 

 Il faut également au minimum 1 espace entre l’instructions et la valeur au risque d’une erreur 💢

## Lignes

Une seule instruction par ligne sera lue par l’assembleur. Les sauts de lignes n’ont aucune incidence sur l’exécution.

⚠️Les étiquettes doivent être suivies d’un “:” puis d’une instruction. Si vous souhaitez ajouter une étiquette mais qu’il n’y a pas “:” alors cela provoquera une erreur car l’étiquette sera interprété comme une instructions n’appartenant pas à notre machine à pile.

# 👷‍♂️ Déboggage

Chaque partie de l’éxécution nécessitant un affichage sera affiché dans le terminal entouré de `[ ]` comme aide de déboggage.

Sorties possibles à la suite d’une exécution :

```bash
[Assembleur] Warning : perte de précision 66536 -> 1000 
[Main] Traduction terminée sujetBizarre.txt.
[CPU] Entrez une valeur pour l'adresse 1000 : 5
[CPU] Valeur de la variable à l'adresse 1000 : -5
[CPU] Fin de l'exectution du programme
```

```bash
[Assembleur] Warning : perte de précision 66536 -> 1000 
[Assembleur] Erreur : Étiquette etiquette_non_déclarée non déclarée.
```

# ✅ Exemples de codes

## Étiquettes

❌ Exemple de code incorrect : 

```bash
boucle_externe:
	push# 0
	read 10
```

✅ Exemple de code correct :

```bash
boucle_externe: push# 0
read 10
```

## Indentation

✅ Exemple de code correct :

```bash
        ici     : read 66536
    
    push    1000
    push#                     0

    
    op 0
     jnz    fin
     push 1000

    op 15                        
    pop           1000

    write 1000

    jmp     ici

                    fin                 :    halt

            
```
---


# Petit Tuto Git

Pour nous, les étudiants.

## Mettre à jour son projet local
   ```git pull origin main```

## Envoyer ses modifications

1. **Vérifier l'état du dépôt**
   ```git status```

2. **Ajouter tous les fichiers modifiés**
   ```git add .```

3. **Encore vérifier l'état du dépôt**
   ```git status```

4. **Valider les changements avec un message**
   ```git commit -a -m "Message détaillé"```

5. **Encore encore vérifier l'état du dépôt**
   ```git status```

6. **Envoyer les modifications vers le dépôt distant**
   ```git push```

