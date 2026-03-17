#ifndef PROGRAMME_H

#define PROGRAMME_H
#define MAX 100
#define INFINI 1000000000

typedef struct Arc {
    int dest;
    int distance;
    int etat;
    int capacite;
    struct Arc* suivant;
} Arc;

typedef struct Sommet {
    int id;
    char nom[50];
    int type;
    Arc* arcs;
    int urgence;
} Sommet;

typedef struct Graphe {
    int ordre;
    Sommet sommets[MAX];
} Graphe;

Arc* creerArc(int dest, int distance, int etat, int capacite);
void ajouterArc(Graphe* g, int src, int dest, int distance, int etat, int capacite);
void initialiserGraphe(Graphe* g, int ordre);
void afficherRoutes(Graphe* g);
void afficherAccessibles(Graphe* g, int debut);
void afficherInaccessibles(Graphe* g, int debut);
void groupesAccessibles(Graphe* g);
void mission5_acheminement(Graphe* g, int debut, int capaciteVehicule);
void menu(Graphe* g);
void afficherInterface(Graphe* g);
void dfsAccessibles(Graphe* g, int u, int visites[]);

#endif
