#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "programme.h"
#include "interface.h"

int main() {
    Graphe g;
    initialiserGraphe(&g, 50); // Graphe avec 50 sommets

    // Attribution des noms explicites à chaque sommet
    for (int i = 0; i < 30; i++) {
        sprintf(g.sommets[i].nom, "Ville_%d", i);
    }
    for (int i = 30; i < 40; i++) {
        sprintf(g.sommets[i].nom, "Hopital_%d", i);
    }
    for (int i = 40; i < 50; i++) {
        sprintf(g.sommets[i].nom, "Entrepot_%d", i);
    }

    // Exemple d’urgences
    g.sommets[31].urgence = 2;
    g.sommets[33].urgence = 1;
    g.sommets[42].urgence = 3;

    // Arcs manuels (liens représentatifs)
    ajouterArc(&g, 0, 31, 10, 2, 6);   // Ville_0 → Hopital_31
    ajouterArc(&g, 1, 41, 12, 2, 8);   // Ville_1 → Entrepot_41
    ajouterArc(&g, 2, 35, 20, 1, 4);   // Ville_2 → Hopital_35
    ajouterArc(&g, 3, 44, 25, 0, 3);   // Ville_3 → Entrepot_44
    ajouterArc(&g, 4, 5, 15, 2, 7);
    ajouterArc(&g, 6, 7, 18, 1, 5);
    ajouterArc(&g, 8, 45, 22, 2, 8);
    ajouterArc(&g, 9, 39, 25, 1, 4);
    ajouterArc(&g, 10, 49, 30, 2, 9);

    // Ajout d’arcs automatiques aléatoires
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        int nbArcs = 2 + rand() % 3; // 2 à 4 arcs par sommet
        for (int j = 0; j < nbArcs; j++) {
            int dest = rand() % 50;
            if (dest != i) {
                int distance = 10 + rand() % 40;
                int etat = rand() % 3;        // 0: détruite, 1: endommagée, 2: OK
                int capacite = 1 + rand() % 9;
                ajouterArc(&g, i, dest, distance, etat, capacite);
            }
        }
    }

    // Menu et interface graphique
    menu(&g);
    afficherInterface(&g);
    return 0;
}
