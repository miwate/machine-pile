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

## Indentation

Il est possible d’intender autant que possible, y compris entre les étiquettes, instructions et variables (du momen la ligne contient moins de 126 caractères).

 `ici     :         read    1000`     équivaut à `ici: read 1000`.

Il n’est cependant pas possible de tout coller.

⚠️`push#` ≠ `push #` 

## Lignes

Une seule instruction par ligne sera lue par l’assembleur. Les sauts de lignes n’ont aucune incidence sur l’exécution.


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

