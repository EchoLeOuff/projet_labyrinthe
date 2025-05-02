#include <stdlib.h>
#include <time.h>
#include "labyrinthe.h"

// Initialise la grille avec des murs
void initialiser_labyrinthe(Labyrinthe* lab) {
    for (int i = 0; i < lab->lignes; i++) {
        for (int j = 0; j < lab->colonnes; j++) {
            lab->grille[i][j] = '#';
        }
    }
}

// Fonction récursive pour le Backtracking
void backtrack(Labyrinthe* lab, int x, int y) {
    lab->grille[x][y] = ' '; // Marquer comme chemin

    // Directions : haut, droite, bas, gauche
    int directions[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};
    // Mélanger les directions pour un résultat aléatoire
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp_x = directions[i][0], temp_y = directions[i][1];
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = temp_x;
        directions[j][1] = temp_y;
    }

    // Explorer chaque direction
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        // Vérifier si le voisin est valide
        if (nx >= 0 && nx < lab->lignes && ny >= 0 && ny < lab->colonnes && lab->grille[nx][ny] == '#') {
            // Casser le mur entre la cellule actuelle et le voisin
            lab->grille[x + directions[i][0]/2][y + directions[i][1]/2] = ' ';
            backtrack(lab, nx, ny);
        }
    }
}

void generer_labyrinthe(Labyrinthe* lab) {
    srand(time(NULL)); // Initialiser le générateur aléatoire

    if (lab->lignes % 2 == 0) lab->lignes--;
    if (lab->colonnes % 2 == 0) lab->colonnes--;
    if (lab->lignes < 3) lab->lignes = 3;
    if (lab->colonnes < 3) lab->colonnes = 3;
    if (lab->lignes > MAX_TAILLE) lab->lignes = MAX_TAILLE - 1;
    if (lab->colonnes > MAX_TAILLE) lab->colonnes = MAX_TAILLE - 1;

    // Étape 1 : Créer le labyrinthe
    initialiser_labyrinthe(lab);

    // Définir l'entrée et la sortie
    lab->entree_x = 1;
    lab->entree_y = 0;
    lab->sortie_x = lab->lignes - 2;
    lab->sortie_y = lab->colonnes - 1;
    lab->grille[lab->entree_x][lab->entree_y] = ' ';
    lab->grille[lab->sortie_x][lab->sortie_y] = ' ';

    // Générer le labyrinthe avec Backtracking
    backtrack(lab, 1, 1);

    // Étape 2 : Convertir en graphe
    GrapheLabyrinthe graphe = {NULL, 0, NULL, NULL};
    if (labyrinthe_vers_graphe(lab, &graphe) != 0) {
        // Gestion d'erreur si la conversion échoue
        return;
    }

    // Libérer la mémoire du graphe (car generer_labyrinthe ne retourne pas le graphe)
    for (int i = 0; i < graphe.taille; i++) {
        free(graphe.noeuds[i]->voisins);
        free(graphe.noeuds[i]);
    }
    free(graphe.noeuds);
}