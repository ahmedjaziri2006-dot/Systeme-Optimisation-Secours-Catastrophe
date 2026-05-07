# Système de Gestion de Catastrophe Naturelle

Application développée en C qui simule la gestion d'une catastrophe naturelle en s'appuyant sur la théorie des graphes pour optimiser l'acheminement des secours et l'utilisation du réseau routier. Une interface graphique interactive avec Raylib permet de visualiser le réseau et l'état des routes en temps réel.

## Contexte

Projet académique réalisé à l'ESIEA (janvier – juin 2025) dans le cadre du module **INF2032 – Graphes et Applications**. Travail d'équipe (3 personnes).

## Modèle simulé

Le réseau modélisé comprend 50 sommets répartis en trois catégories :
- **30 villes** (Ville_0 à Ville_29)
- **10 hôpitaux** (Hopital_30 à Hopital_39)
- **10 entrepôts** (Entrepot_40 à Entrepot_49)

Chaque arête (route) porte trois attributs :
- **Distance** en kilomètres
- **État** : OK (2), endommagée (1), ou détruite (0)
- **Capacité** maximale en véhicules

Certains sommets possèdent un niveau d'urgence permettant de prioriser l'intervention des secours.

## Fonctionnalités

### Analyse du réseau
- Affichage de toutes les routes avec leur état, distance et capacité
- Identification des sommets accessibles depuis un point de départ (parcours DFS)
- Identification des sommets inaccessibles
- Mise en évidence des routes endommagées à sécuriser

### Optimisation des trajets
- Calcul du plus court chemin entre deux sommets (algorithme de Dijkstra)
- Prise en compte de l'état des routes : les routes détruites sont automatiquement exclues du calcul

### Gestion des secours
- Calcul du nombre de véhicules de secours pouvant emprunter une route donnée à partir de sa capacité
- Estimation du temps de transport en fonction de la distance

### Interface utilisateur
- Menu interactif en terminal pour piloter les fonctionnalités
- Visualisation graphique du réseau routier via Raylib :
  - Affichage des 50 sommets répartis sur une grille
  - Code couleur des arêtes selon l'état (vert : OK, orange : endommagée, rouge : détruite)
  - Info-bulle au survol d'une route (distance, capacité, état)
  - Légende intégrée

## Algorithmes et concepts

- Graphes orientés pondérés
- Représentation par listes d'adjacence (listes chaînées)
- Parcours en profondeur (DFS) récursif pour l'analyse de connectivité
- Algorithme de Dijkstra pour les plus courts chemins (implémentation array-based, complexité O(V²))

## Structures de données

```c
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
```

## Stack technique

- **Langage :** C (C99)
- **Visualisation :** Raylib
- **Build :** Makefile (gcc)

## Structure du projet

```
main.c         - point d'entrée et initialisation du graphe
fonctions.c    - logique du graphe et algorithmes (DFS, Dijkstra, secours)
interface.c    - couche de visualisation Raylib + affichage terminal
programme.h    - types et déclarations partagés (Graphe, Arc, Sommet)
interface.h    - interface publique de la couche de visualisation
Makefile       - configuration de build
```

## Installation

### Prérequis
- gcc
- make
- raylib

### Installation de Raylib

**Linux (Ubuntu / Debian) :**
```bash
sudo apt install libraylib-dev
```

**macOS :**
```bash
brew install raylib
```

## Compilation et exécution

```bash
git clone https://github.com/ahmedjaziri2006-dot/Systeme-Optimisation-Secours-Catastrophe
cd Systeme-Optimisation-Secours-Catastrophe
make
./projet
```

Pour nettoyer les fichiers compilés :
```bash
make clean
```

## Compétences mises en œuvre

- Théorie des graphes appliquée à un problème de routage et d'allocation de ressources
- Implémentation d'algorithmes classiques (DFS, Dijkstra) en C from scratch
- Architecture modulaire séparant la logique algorithmique de la couche de visualisation
- Manipulation de structures de données chaînées (listes d'adjacence dynamiques)
- Intégration d'une bibliothèque graphique (Raylib) avec un cœur algorithmique en C
- Conception d'une interface graphique interactive avec gestion d'événements (survol, info-bulles)

## Auteurs

Projet réalisé en équipe à l'ESIEA par Ahmed Jaziri et coéquipiers.

## Licence

Projet académique à but pédagogique.
