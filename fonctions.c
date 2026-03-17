#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programme.h"
#include "interface.h"

Arc* creerArc(int dest, int distance, int etat, int capacite) {
    Arc* arc = (Arc*)malloc(sizeof(Arc));
    arc->dest = dest;
    arc->distance = distance;
    arc->etat = etat;
    arc->capacite = capacite;
    arc->suivant = NULL;
    return arc;
}

void ajouterArc(Graphe* g, int src, int dest, int distance, int etat, int capacite) {
    Arc* arc = creerArc(dest, distance, etat, capacite);
    arc->suivant = g->sommets[src].arcs;
    g->sommets[src].arcs = arc;
}

void initialiserGraphe(Graphe* g, int ordre) {
    g->ordre = ordre;
    for (int i = 0; i < ordre; i++) {
        g->sommets[i].id = i;
        g->sommets[i].arcs = NULL;
        sprintf(g->sommets[i].nom, "Sommet_%d", i);
        g->sommets[i].type = 0;
        g->sommets[i].urgence = 0;
    }
}

void afficherRoutes(Graphe* g) {
    for (int i = 0; i < g->ordre; i++) {
        Arc* arc = g->sommets[i].arcs;
        while (arc) {
            printf("%s -> %s | Distance: %d | État: %d | Capacité: %d\n",
                   g->sommets[i].nom,
                   g->sommets[arc->dest].nom,
                   arc->distance,
                   arc->etat,
                   arc->capacite);
            arc = arc->suivant;
        }
    }
}

void afficher_Accessibles(Graphe* g, int debut) {
    int visites[MAX] = {0};
    dfsAccessibles(g, debut, visites);
    printf("Sommets accessibles depuis %s :\n", g->sommets[debut].nom);
    for (int i = 0; i < g->ordre; i++) {
        if (visites[i]) printf("%s\n", g->sommets[i].nom);
    }
}

void afficher_Inaccessibles(Graphe* g, int debut) {
    int visites[MAX] = {0};
    dfsAccessibles(g, debut, visites);
    printf("Sommets INaccessibles depuis %s :\n", g->sommets[debut].nom);
    for (int i = 0; i < g->ordre; i++) {
        if (!visites[i]) printf("%s\n", g->sommets[i].nom);
    }
}


void dfsGroupe(Graphe* g, int u, int visites[]) {
    visites[u] = 1;
    printf("%s ", g->sommets[u].nom);
    Arc* arc = g->sommets[u].arcs;
    while (arc) {
        if (arc->etat != 0 && !visites[arc->dest]) {
            dfsGroupe(g, arc->dest, visites);
        }
        arc = arc->suivant;
    }
}
void cheminLePlusCourt(Graphe* g, int debut, int fin) {
    int distance[MAX], precedent[MAX], visite[MAX] = {0};

    for (int i = 0; i < g->ordre; i++) {
        distance[i] = INFINI;
        precedent[i] = -1;
    }
    distance[debut] = 0;

    for (int i = 0; i < g->ordre; i++) {
        int minDist = INFINI, u = -1;
        for (int j = 0; j < g->ordre; j++) {
            if (!visite[j] && distance[j] < minDist) {
                minDist = distance[j];
                u = j;
            }
        }

        if (u == -1) break;
        visite[u] = 1;

        Arc* arc = g->sommets[u].arcs;
        while (arc) {
            if (arc->etat != 0 && distance[arc->dest] > distance[u] + arc->distance) {
                distance[arc->dest] = distance[u] + arc->distance;
                precedent[arc->dest] = u;
            }
            arc = arc->suivant;
        }
    }

    if (distance[fin] == INFINI) {
        printf("\nAucun chemin disponible entre %s et %s.\n",
               g->sommets[debut].nom, g->sommets[fin].nom);
        return;
    }

    // Construction du chemin
    int chemin[MAX], k = 0;
    for (int v = fin; v != -1; v = precedent[v]) {
        chemin[k++] = v;
    }

    // Affichage du chemin dans l'ordre correct
    printf("\nChemin le plus court entre %s et %s (distance %d km):\n", 
           g->sommets[debut].nom, g->sommets[fin].nom, distance[fin]);
    for (int i = k - 1; i >= 0; i--) {
        printf("%s", g->sommets[chemin[i]].nom);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

void RoutesASecuriser(Graphe* g) {
    printf("\n--- Routes à sécuriser ---\n");
    for (int i = 0; i < g->ordre; i++) {
        Arc* arc = g->sommets[i].arcs;
        while (arc) {
            if (arc->etat == 1) { // seulement les routes endommagées
                printf("%s -> %s | Distance: %d | Capacité: %d\n",
                       g->sommets[i].nom,
                       g->sommets[arc->dest].nom,
                       arc->distance,
                       arc->capacite);
            }
            arc = arc->suivant;
        }
    }
}

void acheminement(Graphe* g, int debut, int capaciteVehicule) {
    printf("\n--- Acheminement de secours depuis %s ---\n", g->sommets[debut].nom);
    for (int i = 0; i < g->ordre; i++) {
        if (i == debut) continue;
        Arc* arc = g->sommets[debut].arcs;
        while (arc) {
            if (arc->dest == i && arc->etat != 0) {
                int maxVehicules = arc->capacite / capaciteVehicule;
                int temps = arc->distance / 10; // hypothèse : 10 km/h en zone sinistrée
                printf("Vers %s : %d véhicules (urgence: %d), temps estimé: %d h\n",
                       g->sommets[i].nom,
                       maxVehicules,
                       g->sommets[i].urgence,
                       temps);
            }
            arc = arc->suivant;
        }
    }
}
void dfsAccessibles(Graphe* g, int u, int visites[]) {
    visites[u] = 1;
    Arc* arc = g->sommets[u].arcs;
    while (arc) {
        if (arc->etat != 0 && !visites[arc->dest]) {
            dfsAccessibles(g, arc->dest, visites);
        }
        arc = arc->suivant;
    }
}

void menu(Graphe* g) {
    int choix, debut, capaciteVehicule;
    do {
        printf("\nMenu Principal:\n");
        printf("1. Afficher toutes les routes\n");
        printf("2. Afficher chemins accessibles depuis un sommet\n");
        printf("3. Afficher sommets inaccessibles depuis un sommet\n");
        printf("4. Afficher les routes à sécuriser\n");
        printf("5. Acheminement véhicules de secours\n");
        printf("0. Quitter et montre le graphe\n");
        printf("Choix: ");
        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Erreur de saisie.\n");
            return;
        }

        switch (choix) {
            case 1:
                //afficherRoutes(g);
                afficherInterfaceTerminal(g);
                break;
            case 2:
                printf("ID du sommet de départ: ");
                if (scanf("%d", &debut) != 1) {
                    fprintf(stderr, "Erreur de saisie.\n");
                    return;
                }
                afficher_Accessibles(g, debut);
                break;
            case 3: {
                int fin;
                printf("ID du sommet de départ: ");
                if (scanf("%d", &debut) != 1) {
                    fprintf(stderr, "Erreur de saisie.\n");
                    return;
                }
                printf("ID du sommet d'arrivée: ");
                if (scanf("%d", &fin) != 1) {
                    fprintf(stderr, "Erreur de saisie.\n");
                    return;
                }
                cheminLePlusCourt(g, debut, fin);
                break;
            }
            case 4:
                RoutesASecuriser(g);
                break;
            case 5:
                printf("ID du sommet de départ: ");
                if (scanf("%d", &debut) != 1) {
                    fprintf(stderr, "Erreur de saisie.\n");
                    return;
                }
                printf("Capacité d’un véhicule de secours: ");
                if (scanf("%d", &capaciteVehicule) != 1) {
                    fprintf(stderr, "Erreur de saisie.\n");
                    return;
                }
                acheminement(g, debut, capaciteVehicule);
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);
}
 