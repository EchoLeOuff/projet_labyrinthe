#include <stdlib.h>
#include "labyrinthe.h"

int labyrinthe_vers_graphe(const Labyrinthe* lab, GrapheLabyrinthe* graphe) {
    // Étape 1 : Compter les nœuds (cellules avec ' ')
    int nb_noeuds = 0;
    for (int i = 0; i < lab->lignes; i++) {
        for (int j = 0; j < lab->colonnes; j++) {
            if (lab->grille[i][j] == ' ') nb_noeuds++;
        }
    }

    // Allouer le tableau de nœuds
    graphe->noeuds = malloc(nb_noeuds * sizeof(Noeud*));
    if (!graphe->noeuds) return -1;
    graphe->taille = nb_noeuds;

    // Créer les nœuds
    int id = 0;
    for (int i = 0; i < lab->lignes; i++) {
        for (int j = 0; j < lab->colonnes; j++) {
            if (lab->grille[i][j] == ' ') {
                Noeud* noeud = malloc(sizeof(Noeud));
                if (!noeud) {
                    for (int k = 0; k < id; k++) free(graphe->noeuds[k]);
                    free(graphe->noeuds);
                    return -1;
                }
                noeud->id = id;
                noeud->x = i;
                noeud->y = j;
                noeud->voisins = NULL;
                noeud->nb_voisins = 0;
                noeud->distance = -1;
                noeud->precedent = NULL;
                graphe->noeuds[id] = noeud;
                id++;
            }
        }
    }

    // Étape 2 : Créer les arêtes
    for (int i = 0; i < graphe->taille; i++) {
        Noeud* noeud = graphe->noeuds[i];
        int x = noeud->x, y = noeud->y;
        int voisins_potentiels[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Haut, bas, gauche, droite
        noeud->nb_voisins = 0;

        // Compter les voisins valides
        for (int k = 0; k < 4; k++) {
            int nx = x + voisins_potentiels[k][0];
            int ny = y + voisins_potentiels[k][1];
            if (nx >= 0 && nx < lab->lignes && ny >= 0 && ny < lab->colonnes && lab->grille[nx][ny] == ' ') {
                noeud->nb_voisins++;
            }
        }

        // Allouer la liste des voisins
        noeud->voisins = malloc(noeud->nb_voisins * sizeof(Noeud*));
        if (!noeud->voisins) {
            for (int k = 0; k < graphe->taille; k++) {
                free(graphe->noeuds[k]->voisins);
                free(graphe->noeuds[k]);
            }
            free(graphe->noeuds);
            return -1;
        }
        int voisin_idx = 0;

        // Ajouter les voisins
        for (int k = 0; k < 4; k++) {
            int nx = x + voisins_potentiels[k][0];
            int ny = y + voisins_potentiels[k][1];
            if (nx >= 0 && nx < lab->lignes && ny >= 0 && ny < lab->colonnes && lab->grille[nx][ny] == ' ') {
                for (int m = 0; m < graphe->taille; m++) {
                    if (graphe->noeuds[m]->x == nx && graphe->noeuds[m]->y == ny) {
                        noeud->voisins[voisin_idx++] = graphe->noeuds[m];
                        break;
                    }
                }
            }
        }
    }

    // Étape 3 : Définir entrée et sortie
    graphe->entree = NULL;
    graphe->sortie = NULL;
    for (int i = 0; i < graphe->taille; i++) {
        if (graphe->noeuds[i]->x == lab->entree_x && graphe->noeuds[i]->y == lab->entree_y) {
            graphe->entree = graphe->noeuds[i];
        }
        if (graphe->noeuds[i]->x == lab->sortie_x && graphe->noeuds[i]->y == lab->sortie_y) {
            graphe->sortie = graphe->noeuds[i];
        }
    }

    if (!graphe->entree || !graphe->sortie) {
        for (int i = 0; i < graphe->taille; i++) {
            free(graphe->noeuds[i]->voisins);
            free(graphe->noeuds[i]);
        }
        free(graphe->noeuds);
        return -1;
    }

    return 0;
}