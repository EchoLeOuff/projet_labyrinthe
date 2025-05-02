#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "labyrinthe.h"

// Affiche le labyrinthe avec entrée (E) et sortie (S)
void afficher_labyrinthe(const Labyrinthe* lab);

// Affiche un chemin sous forme de coordonnées
void afficher_chemin(Noeud** chemin, const char* methode);

#endif