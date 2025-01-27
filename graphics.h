#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdbool.h>
#include <SDL.h>
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600


typedef struct {
    bool bombe; // Indique si la case contient une bombe
    bool decouverte; // Indique si la case est découverte par le joueur
    bool drapeau; // Indique si la case est marquée d'un drapeau par le joueur
    int bombesVoisines; // Nombre de bombes voisines de la case
} Case;

typedef struct {
    int largeur; // Largeur du plateau
    int hauteur; // Hauteur du plateau
    int nombreBombes; // Nombre de bombes sur le plateau
    Case **cases; // Grille de cases du plateau
} Plateau;

SDL_Window *initSDL(int largeur, int hauteur);
void chargerImagesChiffres(SDL_Renderer *renderer);
void dessinerCase(SDL_Renderer *renderer, int x, int y);
void dessinerChiffre(Plateau *plateau, SDL_Renderer *renderer, int x, int y);
void afficherJeu(SDL_Renderer *renderer, Plateau *plateau);
void quitterSDL(SDL_Renderer *renderer, SDL_Window *window);
void chargerTextures(SDL_Renderer *renderer);
SDL_Texture *chargerTexture(SDL_Renderer *renderer, const char *cheminImage);
void afficherMenuPrincipal(SDL_Renderer *renderer);
SDL_Window *initSDL(int largeur, int hauteur);

// Déclaration des variables globales pour les textures
extern SDL_Texture *chiffres[10];
extern SDL_Texture *caseRevelee;
extern SDL_Texture *caseNonRevelee;
extern SDL_Texture *caseDrapeau;
extern SDL_Texture *ecranMenu;
extern SDL_Texture *ecranVictoire;
extern SDL_Texture *ecranDefaite;

#endif /* GRAPHICS_H */
