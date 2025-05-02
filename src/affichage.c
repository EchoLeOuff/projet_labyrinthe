    #include <stdio.h>
    #include "affichage.h"

    void afficher_labyrinthe(const Labyrinthe* lab) {
        for (int i = 0; i < lab->lignes; i++) {
            for (int j = 0; j < lab->colonnes; j++) {
                if (i == lab->entree_x && j == lab->entree_y) {
                    printf("E");
                } else if (i == lab->sortie_x && j == lab->sortie_y) {
                    printf("S");
                } else {
                    printf("%c", lab->grille[i][j]);
                }
            }
            printf("\n");
        }
    }

    void afficher_chemin(Noeud** chemin, const char* methode) {
        printf("%s chemin : ", methode);
        if (!chemin) {
            printf("Aucun chemin trouvé\n");
            return;
        }
        for (int i = 0; chemin[i] != NULL; i++) {
            printf("(%d,%d) ", chemin[i]->x, chemin[i]->y);
        }
        printf("\n");
    }