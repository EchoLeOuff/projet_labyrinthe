#include <stdlib.h>
#include "labyrinthe.h"

// Fonction utilitaire pour libérer la mémoire en cas d'erreur
void liberer_chemin(Noeud** chemin) {
    if (chemin) free(chemin);
}

// Fonction récursive pour DFS (définie à l'extérieur de resoudre_dfs)
static int dfs(Noeud* courant, int* visite, Noeud** chemin, int* chemin_idx, const GrapheLabyrinthe* graphe) {
    visite[courant->id] = 1;
    chemin[(*chemin_idx)++] = courant;

    if (courant == graphe->sortie) return 1; // Chemin trouvé

    for (int i = 0; i < courant->nb_voisins; i++) {
        Noeud* voisin = courant->voisins[i];
        if (!visite[voisin->id]) {
            if (dfs(voisin, visite, chemin, chemin_idx, graphe)) return 1; // Chemin trouvé via ce voisin
        }
    }

    (*chemin_idx)--; // Backtrack
    return 0; // Pas de chemin via ce nœud
}

Noeud** resoudre_dfs(const GrapheLabyrinthe* graphe) {
    // Allouer un tableau pour marquer les nœuds visités
    int* visite = calloc(graphe->taille, sizeof(int));
    if (!visite) return NULL;

    // Allouer un tableau pour le chemin (taille maximale = nombre de nœuds + 1 pour NULL)
    Noeud** chemin = malloc((graphe->taille + 1) * sizeof(Noeud*));
    if (!chemin) {
        free(visite);
        return NULL;
    }
    int chemin_idx = 0;

    // Lancer DFS depuis l'entrée
    if (!dfs(graphe->entree, visite, chemin, &chemin_idx, graphe)) {
        free(visite);
        liberer_chemin(chemin);
        return NULL; // Aucun chemin trouvé
    }

    // Terminer le chemin avec NULL
    chemin[chemin_idx] = NULL;
    free(visite);
    return chemin;
}

Noeud** resoudre_bfs(const GrapheLabyrinthe* graphe) {
    // Allouer un tableau pour marquer les nœuds visités
    int* visite = calloc(graphe->taille, sizeof(int));
    if (!visite) return NULL;

    // Allouer une file pour BFS
    Noeud** queue = malloc(graphe->taille * sizeof(Noeud*));
    if (!queue) {
        free(visite);
        return NULL;
    }
    int debut = 0, fin = 0;

    // Allouer un tableau pour les précédents
    Noeud** precedent = calloc(graphe->taille, sizeof(Noeud*));
    if (!precedent) {
        free(visite);
        free(queue);
        return NULL;
    }

    // Initialiser BFS
    queue[fin++] = graphe->entree;
    visite[graphe->entree->id] = 1;

    // Exécuter BFS
    while (debut < fin) {
        Noeud* courant = queue[debut++];
        if (courant == graphe->sortie) break;

        for (int i = 0; i < courant->nb_voisins; i++) {
            Noeud* voisin = courant->voisins[i];
            if (!visite[voisin->id]) {
                visite[voisin->id] = 1;
                queue[fin++] = voisin;
                precedent[voisin->id] = courant;
            }
        }
    }

    // Vérifier si la sortie a été atteinte
    if (!visite[graphe->sortie->id]) {
        free(visite);
        free(queue);
        free(precedent);
        return NULL;
    }

    // Compter la longueur du chemin
    int chemin_len = 0;
    Noeud* courant = graphe->sortie;
    while (courant) {
        chemin_len++;
        courant = precedent[courant->id];
    }

    // Allouer le chemin
    Noeud** chemin = malloc((chemin_len + 1) * sizeof(Noeud*));
    if (!chemin) {
        free(visite);
        free(queue);
        free(precedent);
        return NULL;
    }

    // Reconstruire le chemin
    courant = graphe->sortie;
    for (int i = chemin_len - 1; i >= 0; i--) {
        chemin[i] = courant;
        courant = precedent[courant->id];
    }
    chemin[chemin_len] = NULL;

    // Libérer la mémoire
    free(visite);
    free(queue);
    free(precedent);
    return chemin;
}