# Surréalisme : Comment utiliser le programme
## Préambule

Dans tous les cas, remplacer tous les caractères `ö` (2 occurrences) du dictionnaire non accentué par `o`.
### Sur Windows
Changer le **chemin relatif** du dictionnaire non accentué au main.c:12 (à la ligne 12 de main.c) pour son chemin absolu.

i.e. `char** file = read_file("dictionnaire_non_accentue.txt", &size);` 
peut devenir `char** file = read_file(`**`"c:\\Users\\utilisateur\\Desktop\\Surealisme\\dictionnaire_non_accentue.txt"`**`, &size);`

### Sur MacOS ou Linux
Le programme fonctionnera correctement.

## Utilisation
1. Compiler les fichiers sources. 
2. Exécuter le fichier résultant. 
3. Entrer le chiffre indiqué par le menu pour accéder à sa partie.

Par exemple : 
pour cet affichage-ci
```
0) Leave 
1) Generate a complete sentence 
2) Search with flechi words 
3) Other
```
entrer `1` permettra d'accéder à la 2e partie, soit la génération d'une phrase complète.

4. Pour quitter le programme, entrer `0` dans le menu principal (pour l'action `Leave`).
