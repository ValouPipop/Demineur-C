#include "graphics.h"
#include <stdio.h>

#define TAILLE_CASE 20


void afficherMenuPrincipal(SDL_Renderer *renderer) {
    // Nettoyer le rendu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Charger l'image du menu principal
    SDL_Texture *menuTexture = chargerTexture(renderer, "assets/EcranTitre.bmp");
    if (menuTexture == NULL) {
        printf("Erreur lors du chargement de l'image du menu principal\n");
        return;
    }

    // Obtenir les dimensions de l'image du menu principal
    int menuLargeur, menuHauteur;
    SDL_QueryTexture(menuTexture, NULL, NULL, &menuLargeur, &menuHauteur);

    // Dessiner l'image du menu principal au centre de la fenêtre
    SDL_Rect destRect = {(LARGEUR_FENETRE - menuLargeur) / 2, (HAUTEUR_FENETRE - menuHauteur) / 2, menuLargeur, menuHauteur};
    SDL_RenderCopy(renderer, menuTexture, NULL, &destRect);

    // Réaliser le rendu
    SDL_RenderPresent(renderer);

    // Libérer la texture du menu principal
    SDL_DestroyTexture(menuTexture);
}


SDL_Texture *chiffres[10];
SDL_Texture *caseRevelee;
SDL_Texture *caseNonRevelee;
SDL_Texture *caseDrapeau;
SDL_Texture *ecranMenu;
SDL_Texture *ecranVictoire;
SDL_Texture *ecranDefaite;;

void chargerTextures(SDL_Renderer *renderer) {
    // Chargement des textures à partir des fichiers image
    chiffres[0] = chargerTexture(renderer, "assets/chiffre_0.bmp");
    chiffres[1] = chargerTexture(renderer, "assets/chiffre_1.bmp");
    chiffres[2] = chargerTexture(renderer, "assets/chiffre_2.bmp");
    chiffres[3] = chargerTexture(renderer, "assets/chiffre_3.bmp");
    chiffres[4] = chargerTexture(renderer, "assets/chiffre_4.bmp");
    chiffres[5] = chargerTexture(renderer, "assets/chiffre_5.bmp");
    chiffres[6] = chargerTexture(renderer, "assets/chiffre_6.bmp");
    chiffres[7] = chargerTexture(renderer, "assets/chiffre_7.bmp");
    chiffres[8] = chargerTexture(renderer, "assets/chiffre_8.bmp");

    caseRevelee = chargerTexture(renderer, "images/case.bmp");
    caseNonRevelee = chargerTexture(renderer, "images/case_0.bmp");
    caseDrapeau = chargerTexture(renderer, "images/flag.bmp");
    ecranMenu = chargerTexture(renderer, "assets/EcranTitre.bmp");
    ecranVictoire = chargerTexture(renderer, "assets/Victoire.bmp");
    ecranDefaite = chargerTexture(renderer, "assets/Defaite.bmp");
}

SDL_Texture *chargerTexture(SDL_Renderer *renderer, const char *cheminImage) {
    SDL_Surface *surface = SDL_LoadBMP(cheminImage);
    if (!surface) {
        printf("Erreur lors du chargement de l'image : %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void dessinerCase(SDL_Renderer *renderer, int x, int y) {
    SDL_Rect rect;
    rect.x = x * TAILLE_CASE;
    rect.y = y * TAILLE_CASE;
    rect.w = TAILLE_CASE;
    rect.h = TAILLE_CASE;

    // Couleur de fond
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
    SDL_RenderFillRect(renderer, &rect);

    // Couleur de bordure
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
    SDL_RenderDrawRect(renderer, &rect);
}

void dessinerChiffre(Plateau *plateau, SDL_Renderer *renderer, int x, int y) {
    if (plateau->cases[y][x].decouverte && !plateau->cases[y][x].bombe) {
        SDL_Texture *chiffreTexture = chiffres[plateau->cases[y][x].bombesVoisines];
        SDL_Rect destRect;
        destRect.x = x * TAILLE_CASE + TAILLE_CASE / 2 - TAILLE_CASE / 4;
        destRect.y = y * TAILLE_CASE + TAILLE_CASE / 2 - TAILLE_CASE / 4;
        destRect.w = TAILLE_CASE / 2;
        destRect.h = TAILLE_CASE / 2;
        SDL_RenderCopy(renderer, chiffreTexture, NULL, &destRect);
    }
}

void afficherJeu(SDL_Renderer *renderer, Plateau *plateau) {
    // Boucle pour afficher chaque case du plateau
    for (int y = 0; y < plateau->hauteur; y++) {
        for (int x = 0; x < plateau->largeur; x++) {
            // Dessiner la case
            dessinerCase(renderer, x, y);

            // Dessiner le chiffre (si la case est découverte)
            dessinerChiffre(plateau, renderer, x, y);
        }
    }
}

void quitterSDL(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window *initSDL(int largeur, int hauteur) {
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return NULL;
    }

    window = SDL_CreateWindow("Démineur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeur, hauteur, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre SDL : %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}
