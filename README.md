# 🌍 Système de Gestion de Catastrophe Naturelle

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg">
  <img src="https://img.shields.io/badge/graphics-Raylib-green.svg">
  <img src="https://img.shields.io/badge/status-Academic%20Project-orange.svg">
  <img src="https://img.shields.io/badge/build-Makefile-lightgrey.svg">
</p>

---

## 📌 Description

Ce projet est une application développée en **C** qui simule la gestion d’une catastrophe naturelle en utilisant la **théorie des graphes**.

L’objectif est d’optimiser :

* 🚑 l’acheminement des secours
* 📦 la distribution des ressources
* 🛣️ l’utilisation du réseau routier

Une **interface graphique avec Raylib** permet de visualiser le système en temps réel.

---

## 🚀 Fonctionnalités

### 🔹 Analyse du réseau

* Visualisation des routes et de leurs états
* Identification des zones accessibles / inaccessibles

### 🔹 Connectivité

* Détection des composantes du graphe

### 🔹 Optimisation des trajets

* Calcul des plus courts chemins
* Adaptation dynamique en cas de routes endommagées

### 🔹 Sécurisation

* Identification des routes critiques
* Minimisation du coût du réseau

### 🔹 Gestion des secours

* Optimisation du flux de véhicules
* Gestion des priorités (urgence, type de mission)
* Calcul des délais de transport

### ⭐ Bonus

* Optimisation des ressources (type sac à dos)
* Amélioration du réseau avec un minimum de routes

---

## 🧠 Concepts utilisés

* Graphes orientés pondérés
* BFS / DFS
* Algorithmes de plus court chemin
* Arbre couvrant minimal
* Flot maximal
* Optimisation combinatoire

---

## 🛠️ Technologies

* **Langage :** C
* **Graphique :** Raylib
* **Build :** Makefile

---

## 🎮 Interface graphique (Raylib)

* Visualisation du graphe
* Affichage des villes / hôpitaux / entrepôts
* Simulation des déplacements des secours
* Interface interactive

---

## 📂 Structure du projet

```text
project/
├── main.c
├── graph.c / graph.h
├── algorithms.c / algorithms.h
├── interface.c / interface.h
├── Makefile
└── README.md
```

---

## ⚙️ Installation

### 🔧 Prérequis

* gcc
* make
* raylib

### 📦 Installer Raylib

#### Linux (Ubuntu)

```bash
sudo apt install libraylib-dev
```

#### macOS

```bash
brew install raylib
```

---

## ▶️ Compilation & Exécution

```bash
make
./main
```

---

## 📸 Aperçu (optionnel)

> Ajoutez ici des captures d’écran de votre interface Raylib pour améliorer votre repo

---

## 👥 Auteurs

Projet réalisé dans le cadre du module **INF2032 – Graphes et Applications**

* 👤 Votre Nom
* 👤 Coéquipier 1
* 👤 Coéquipier 2

---

## 📜 Licence

Projet académique à but pédagogique.

---

## ⭐ Remarque

Ce projet met en pratique des concepts avancés d’algorithmique et de modélisation pour résoudre des problèmes réels liés aux catastrophes naturelles.
