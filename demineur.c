#include "demineur.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

Case* NouvelleCase(){
    Case* MaCase = (Case*)malloc(sizeof(Case));
    if (MaCase != NULL) {
        MaCase->bombesVoisines = 0;
        MaCase->bombe = false;
        MaCase->decouverte = false;
        MaCase->drapeau = false;
    }
    return MaCase;
}

void Initialiser(int largeur, int hauteur, int nombreBombes, Plateau* plateau){
    plateau->hauteur = hauteur;
    plateau->largeur = largeur;
    plateau->nombreBombes = nombreBombes;

    plateau->cases = (Case**)malloc(sizeof(Case*) * hauteur);
    for (int i = 0; i < hauteur; ++i) {
        plateau->cases[i] = (Case*)malloc(sizeof(Case) * largeur);
        for (int j = 0; j < largeur; ++j) {
            plateau->cases[i][j] = *NouvelleCase();
        }
    }
    PlacerBombes(plateau);
    UpdateNombresBombes(plateau);
}

void PlacerBombes(Plateau* plateau) {
    srand(time(NULL));
    int bombesPlacees = 0;
    while (bombesPlacees < plateau->nombreBombes) {
        int x = rand() % plateau->hauteur;
        int y = rand() % plateau->largeur;
        if (!(plateau->cases[x][y].bombe)) {
            plateau->cases[x][y].bombe = true;
            printf("Bombe Placee en : %d,%d\n", x, y);
            bombesPlacees++;
        }
    }
}

void UpdateNombresBombes(Plateau* plateau){
    for(int i=0; i<plateau->hauteur;i++){
        for(int j=0; j<plateau->largeur;j++){
            int nombreBombes = 0;
            for(int x=-1; x<=1; x++){
                for(int y=-1; y<=1; y++){
                    if((x != 0 || y != 0) &&
                       (i+x >= 0 && i+x < plateau->hauteur) &&
                       (j+y >= 0 && j+y < plateau->largeur)) {
                        if(plateau->cases[i+x][j+y].bombe) {
                            nombreBombes++;
                        }
                    }
                }
            }
            plateau->cases[i][j].bombesVoisines = nombreBombes;
            printf("Cette case a %d bombes voisines\n", nombreBombes);
        }
    }
}

void PlacerDrapeau(Plateau* plateau,int x,int y){
    plateau->cases[x][y].drapeau=true;
}

void RevelerCase(Plateau * plateau,int x, int y){
    if(plateau->cases[x][y].bombe){
        printf("Vous avez Perdu\n");
    }
    else{
        printf("Cette case a %d bombes voisines\n", plateau->cases[x][y].bombesVoisines);
        plateau->cases[x][y].decouverte = true;
        if(plateau->cases[x][y].bombesVoisines==0) {
            CaseAdjacente(plateau, x, y);
        }
    }
}

void CaseAdjacente(Plateau *plateau, int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i >= 0 && x + i < plateau->hauteur &&
                y + j >= 0 && y + j < plateau->largeur) {
                if (!plateau->cases[x + i][y + j].decouverte &&
                    !plateau->cases[x + i][y + j].bombe) {
                    plateau->cases[x + i][y + j].decouverte = true;
                    if (plateau->cases[x + i][y + j].bombesVoisines == 0) {
                        CaseAdjacente(plateau, x + i, y + j);
                    }
                }
            }
        }
    }
}



