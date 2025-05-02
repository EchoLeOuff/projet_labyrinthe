#ifndef LABYRINTHE_H
#define LABYRINTHE_H
#define MAX_TAILLE 100

typedef struct {
    int lignes;
    int colonnes;
    char grille[MAX_TAILLE][MAX_TAILLE]; // '#' = mur, ' ' = chemin
    int entree_x, entree_y; // Position d'entrée
    int sortie_x, sortie_y; // Position de sortie
} Labyrinthe;

typedef struct Noeud {
    int id; // Identifiant unique
    int x, y; // Position dans le labyrinthe
    struct Noeud** voisins; // Liste des voisins
    int nb_voisins; // Nombre de voisins
    int distance; // Pour les algorithmes
    struct Noeud* precedent; // Pour le chemin
} Noeud;

typedef struct {
    Noeud** noeuds; // Tableau de pointeurs
    int taille; // Nombre de noeuds
    Noeud* entree; // Noeud d'entrée
    Noeud* sortie; // Noeud de sortie
} GrapheLabyrinthe;

// Prototypes des fonctions
void generer_labyrinthe(Labyrinthe* lab);
int labyrinthe_vers_graphe(const Labyrinthe* lab, GrapheLabyrinthe* graphe);
Noeud** resoudre_dfs(const GrapheLabyrinthe* graphe);
Noeud** resoudre_bfs(const GrapheLabyrinthe* graphe);

#endif