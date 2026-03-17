#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "programme.h"

#define RAYON_SOMMET 14
#define SCALE 1.8
#define FONT_SIZE_INFO 18
#define FONT_SIZE_LABEL 16
#define FONT_SIZE_LEGEND 18
#define FONT_SIZE_TOOLTIP 16

typedef struct {
    int x, y;
} Position;

Position positions[MAX] = {
    {70, 20}, {180, 20}, {290, 20}, {400, 20}, {510, 20}, {620, 20}, {730, 20}, {840, 20}, {950, 20}, {1060, 20},
    {125, 260}, {235, 260}, {345, 260}, {455, 260}, {565, 260}, {675, 260}, {785, 260}, {895, 260}, {1005, 260}, {1115, 260},
    {70, 500}, {180, 500}, {290, 500}, {400, 500}, {510, 500}, {620, 500}, {730, 500}, {840, 500}, {950, 500}, {1060, 500},
    {125, 740}, {235, 740}, {345, 740}, {455, 740}, {565, 740}, {675, 740}, {785, 740}, {895, 740}, {1005, 740}, {1115, 740},
    {70, 980}, {180, 980}, {290, 980}, {400, 980}, {510, 980}, {620, 980}, {730, 980}, {840, 980}, {950, 980}, {1060, 980}
};







Color getCouleurEtat(int etat) {
    switch (etat) {
        case 2: return GREEN;
        case 1: return ORANGE;
        case 0: return RED;
        default: return GRAY;
    }
}

void afficherInterface(Graphe* g) {
    InitWindow(1200, 1000, "Réseau Routier - Interface Raylib");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mouse = GetMousePosition();
        Arc* arcSurvole = NULL;
        int sommetSrcSurvole = -1;

        // Dessin des arcs
        for (int i = 0; i < g->ordre; i++) {
            Arc* arc = g->sommets[i].arcs;
            while (arc) {
                int j = arc->dest;
                Vector2 posA = {positions[i].x, positions[i].y};
                Vector2 posB = {positions[j].x, positions[j].y};
                Vector2 milieu = {(posA.x + posB.x) / 2, (posA.y + posB.y) / 2};

                DrawLineEx(posA, posB, 3, getCouleurEtat(arc->etat));

                char info[64];
                sprintf(info, "%dkm | cap:%d", arc->distance, arc->capacite);
                int textWidth = MeasureText(info, FONT_SIZE_INFO);
                int verticalOffset = (i % 2 == 0) ? -25 : -10;
                DrawText(info, milieu.x - textWidth / 2, milieu.y + verticalOffset, FONT_SIZE_INFO, DARKGRAY);

                float dist = sqrtf((mouse.x - milieu.x)*(mouse.x - milieu.x) + (mouse.y - milieu.y)*(mouse.y - milieu.y));
                if (dist < 12) {
                    arcSurvole = arc;
                    sommetSrcSurvole = i;
                }
                arc = arc->suivant;
            }
        }

        // Légende
        DrawRectangle(900, 50, 250, 150, LIGHTGRAY);
        DrawText("Légende routes :", 920, 60, FONT_SIZE_LEGEND, DARKGRAY);
        DrawLineEx((Vector2){920, 95}, (Vector2){960, 95}, 3, GREEN);
        DrawText("OK", 970, 88, FONT_SIZE_LEGEND, DARKGRAY);
        DrawLineEx((Vector2){920, 120}, (Vector2){960, 120}, 3, ORANGE);
        DrawText("Endommagée", 970, 113, FONT_SIZE_LEGEND, DARKGRAY);
        DrawLineEx((Vector2){920, 145}, (Vector2){960, 145}, 3, RED);
        DrawText("Détruite", 970, 138, FONT_SIZE_LEGEND, DARKGRAY);

        // Sommets
        for (int i = 0; i < g->ordre; i++) {
            DrawCircle(positions[i].x, positions[i].y, RAYON_SOMMET, SKYBLUE);
            int textWidth = MeasureText(g->sommets[i].nom, FONT_SIZE_LABEL);
            DrawText(g->sommets[i].nom, positions[i].x - textWidth / 2, positions[i].y - RAYON_SOMMET - 30, FONT_SIZE_LABEL, DARKBLUE);
        }

        // Info bulle si survol
        if (arcSurvole != NULL) {
            int dest = arcSurvole->dest;
            char details[128];
            sprintf(details, "De %s à %s\nDistance: %d km\nCapacité: %d\nÉtat: %s",
                    g->sommets[sommetSrcSurvole].nom,
                    g->sommets[dest].nom,
                    arcSurvole->distance,
                    arcSurvole->capacite,
                    arcSurvole->etat == 2 ? "OK" :
                    arcSurvole->etat == 1 ? "Endommagée" : "Détruite");

            DrawRectangle(mouse.x + 10, mouse.y, 200, 75, Fade(LIGHTGRAY, 0.95f));
            DrawText(details, mouse.x + 15, mouse.y + 8, FONT_SIZE_TOOLTIP, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
}

void afficherInterfaceTerminal(Graphe* g) {
    printf("\n===== Sommets =====\n");
    for (int i = 0; i < g->ordre; i++)
        printf("- %s (urgence : %d)\n", g->sommets[i].nom, g->sommets[i].urgence);

    printf("\n===== Arcs =====\n");
    for (int i = 0; i < g->ordre; i++) {
        Arc* arc = g->sommets[i].arcs;
        while (arc) {
            printf("%s -> %s | %dkm | cap:%d | état: %s\n",
                   g->sommets[i].nom,
                   g->sommets[arc->dest].nom,
                   arc->distance,
                   arc->capacite,
                   arc->etat == 2 ? "OK" :
                   arc->etat == 1 ? "Endommagée" : "Détruite");
            arc = arc->suivant;
        }
    }
}
