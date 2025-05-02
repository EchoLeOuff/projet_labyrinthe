#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"
#include "affichage.h"

// Fonction pour libérer le graphe
void liberer_graphe(GrapheLabyrinthe* graphe) {
    for (int i = 0; i < graphe->taille; i++) {
        free(graphe->noeuds[i]->voisins);
        free(graphe->noeuds[i]);
    }
    free(graphe->noeuds);
}

int main() {
    // Initialiser un labyrinthe
    Labyrinthe lab = {15, 15, {{0}}, 0, 0, 0, 0};
    printf("Génération du labyrinthe...\n");
    generer_labyrinthe(&lab);
    printf("Labyrinthe généré :\n");
    afficher_labyrinthe(&lab);

    // Convertir en graphe
    GrapheLabyrinthe graphe = {NULL, 0, NULL, NULL};
    printf("\nConversion en graphe...\n");
    if (labyrinthe_vers_graphe(&lab, &graphe) != 0) {
        printf("Erreur lors de la conversion en graphe\n");
        return 1;
    }
    printf("Graphe créé avec %d nœuds\n", graphe.taille);
    printf("Entrée : (%d,%d), Sortie : (%d,%d)\n", 
           graphe.entree->x, graphe.entree->y, 
           graphe.sortie->x, graphe.sortie->y);

    // Résoudre avec DFS
    printf("\nRésolution avec DFS...\n");
    Noeud** chemin_dfs = resoudre_dfs(&graphe);
    afficher_chemin(chemin_dfs, "DFS");

    // Résoudre avec BFS
    printf("\nRésolution avec BFS...\n");
    Noeud** chemin_bfs = resoudre_bfs(&graphe);
    afficher_chemin(chemin_bfs, "BFS");

    // Libérer la mémoire
    free(chemin_dfs);
    free(chemin_bfs);
    liberer_graphe(&graphe);

    // Ajouter une pause pour voir la sortie
    printf("\nAppuyez sur Entrée pour quitter...\n");
    getchar();

    return 0;
}