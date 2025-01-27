#ifndef DEMINEUR_H
#define DEMINEUR_H

#include <stdbool.h>

typedef struct {
    bool bombe;
    bool decouverte;
    bool drapeau;
    int bombesVoisines;
} Case;

typedef struct {
    int largeur;
    int hauteur;
    int nombreBombes;
    Case **cases;
} Plateau;

Case *NouvelleCase();
void Initialiser(int largeur, int hauteur, int nombreBombes, Plateau* plateau);
void PlacerBombes(Plateau* plateau);
void UpdateNombresBombes(Plateau* plateau);
void PlacerDrapeau(Plateau* plateau, int x, int y);
void RevelerCase(Plateau* plateau, int x, int y);
void CaseAdjacente(Plateau* plateau, int x, int y);

#endif /* DEMINEUR_H */
