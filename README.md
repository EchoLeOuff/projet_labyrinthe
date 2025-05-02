# projet_labyrinthe

Ce projet a pour but de créer un labyrinthe aléatoire à l'aide de l'algorithme de backtracking et de trouver le chemin le plus court à l'aide de 2 algorithmes : la recherche BFS et DFS.

# fonctionnalitées 

- Génération aléatoire de labyrinthe à l'aide de l'algorithme de Backtracking. 
- Transformation de ce labyrinthe en un graphe (grâce à la structure de labyrinthe.h) pour pouvoir utiliser les algorithmes DFS et BFS
- Résolution du plus court chemin par les 2 algorithmes
- affichage du labyrinthe et du plus court chemin en fonction des coordonnées.

# structure : 

- 2 fichiers header : labyrinthe.h et affichage.h qui me permettent de définir des structures de données et de fontions.
- affichage.c : permet l'affichage dans l'invite de commande.
- generation.c : générer le labyrinthe en fonction d'une taille demandée.
- graphe.c : convertit le labyrinthe généré en un graphe.
- resoudre.c : applique les algorithmes BFS et DFS.
- main.c : le fichier qui appelle toutes les fonctions

# Implémentation : 

- generation.c : Les fonctions créés dans ce code on était implémenter en partie par moi et par Grok. Notament pour la fonction de backtracking.
- graphe.c : implémenté par moi-même.
- resoudre.c : les codes des algorithmes BFS et DFS on était récupérer sur internet et adapté à mon projet.
- affichage.c : codé par moi-même
- main.c : Grok
- Compileur : adapté a mon code par Grok car je n'ai aucune connaissance en compilateur.


# Remarques :

Ce projet fut interessant par la structuration choisi. En effet on a jamais utilisé une telle strucutre en C avec des fichiers séparés. Il m'a permit de découvrir la manière de créer des fichiers compilés et d'approfondir mes compétences en c. 
