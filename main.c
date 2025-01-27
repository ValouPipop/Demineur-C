#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>
#include "demineur.h"

void dessinerCaseNDecouverte(SDL_Renderer* renderer, int x, int y) {
    SDL_Surface* surface = SDL_LoadBMP("../images/NonDecouvert.bmp");
    if (surface == NULL) {
        printf("Impossible de charger l'image : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        printf("Impossible de créer la texture : %s\n", SDL_GetError());
        return;
    }

    int largeur, hauteur;
    SDL_QueryTexture(texture, NULL, NULL, &largeur, &hauteur);

    SDL_Rect destinationRect = {x, y, largeur, hauteur};

    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);

    SDL_DestroyTexture(texture);
}

void dessinerCaseDecouverte(SDL_Renderer* renderer, int x, int y, int nombreBombes) {
    char imagePath[100];
    snprintf(imagePath, sizeof(imagePath), "../images/%d.bmp", nombreBombes);
    SDL_Surface* surface = SDL_LoadBMP(imagePath);
    if (surface == NULL) {
        printf("Impossible de charger l'image : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        printf("Impossible de créer la texture : %s\n", SDL_GetError());
        return;
    }

    int largeur, hauteur;
    SDL_QueryTexture(texture, NULL, NULL, &largeur, &hauteur);

    SDL_Rect destinationRect = {x, y, largeur, hauteur};

    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);

    SDL_DestroyTexture(texture);
}
void Drapeau(SDL_Renderer* renderer, int x, int y) {
    SDL_Surface* surface = SDL_LoadBMP("../images/flag.bmp");
    if (surface == NULL) {
        printf("Impossible de charger l'image : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        printf("Impossible de créer la texture : %s\n", SDL_GetError());
        return;
    }

    int largeur, hauteur;
    SDL_QueryTexture(texture, NULL, NULL, &largeur, &hauteur);

    SDL_Rect destinationRect = {x, y, largeur, hauteur};

    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);

    SDL_DestroyTexture(texture);
}


void AfficherPlateau(SDL_Renderer* renderer,Plateau* plateau,int x,int y) {
    for (int i = 0; i < plateau->hauteur; ++i) {
        for (int j = 0; j < plateau->largeur; ++j) {
            if (plateau->cases[i][j].drapeau){
                Drapeau(renderer,x+(20*i),y+(20*j));
            }
            if(plateau->cases[i][j].drapeau==false) {
                if (plateau->cases[i][j].decouverte) {
                    dessinerCaseDecouverte(renderer, x + (20 * i), y + (20 * j), plateau->cases[i][j].bombesVoisines);
                } else {
                    dessinerCaseNDecouverte(renderer, x + (20 * i), y + (20 * j));
                }
            }
        }
        printf("\n");
    }
}


void AfficherMenu(SDL_Renderer* renderer) {
    SDL_Surface* surface = SDL_LoadBMP("../images/accueil.bmp");
    if (surface == NULL) {
        printf("Impossible de charger l'image : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        printf("Impossible de créer la texture : %s\n", SDL_GetError());
        return;
    }

    int largeur, hauteur;
    SDL_QueryTexture(texture, NULL, NULL, &largeur, &hauteur);

    SDL_Rect destinationRect = {0, 0, largeur, hauteur};

    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);


    SDL_DestroyTexture(texture);
}
void Defaite(SDL_Renderer* renderer) {
    SDL_Surface *surface = SDL_LoadBMP("../images/ecranloose.bmp");
    if (surface == NULL) {
        printf("Impossible de charger l'image : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        printf("Impossible de créer la texture : %s\n", SDL_GetError());
        return;
    }


    int largeur, hauteur;
    SDL_QueryTexture(texture, NULL, NULL, &largeur, &hauteur);

    SDL_Rect destinationRect = {0, 0, largeur, hauteur};

    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);


    SDL_DestroyTexture(texture);
}
void Victoire(SDL_Renderer* renderer) {
    SDL_Surface *surface = SDL_LoadBMP("../images/ecranwin.bmp");
    if (surface == NULL) {
        printf("Impossible de charger l'image : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        printf("Impossible de créer la texture : %s\n", SDL_GetError());
        return;
    }


    int largeur, hauteur;
    SDL_QueryTexture(texture, NULL, NULL, &largeur, &hauteur);

    SDL_Rect destinationRect = {0, 0, largeur, hauteur};

    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);


    SDL_DestroyTexture(texture);
}
int ClicSurCase(SDL_Renderer* renderer, int mouseX, int mouseY, int gamestate, Plateau* plateau,int x,int y) {
    if (gamestate == 1) {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            // Si un clic droit est détecté
            for (int i = 0; i < plateau->hauteur; i++) {
                for (int j = 0; j < plateau->largeur; j++) {
                    int caseX = i * 20;
                    int caseY = j * 20;
                    if (mouseX >= caseX +x && mouseX < caseX + 20+x && mouseY >= caseY+y && mouseY < caseY + 20+y) {
                        if (!plateau->cases[i][j].bombe) {
                            RevelerCase(plateau, i, j);
                            printf("Clic droit sur la case %d, %d\n", i, j);
                            return gamestate;
                        } else {
                            return 2;
                        }
                    }
                }
            }
        }
    }
    // Si aucun clic droit valide n'a été détecté, retourner le même gamestate
    return gamestate;
}
void ClicDrapeau(SDL_Renderer* renderer, int mouseX, int mouseY, Plateau* plateau,int x,int y) {
    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        // Si un clic droit est détecté
        for (int i = 0; i < plateau->hauteur; i++) {
            for (int j = 0; j < plateau->largeur; j++) {
                int caseX = i * 20;
                int caseY = j * 20;
                if (mouseX >= caseX+x && mouseX < caseX + 20+x && mouseY >= caseY+y && mouseY < caseY + 20+y) {
                    if (!plateau->cases[i][j].decouverte) {
                        PlacerDrapeau(plateau,i,j);
                        printf("Drapeau placé sur la case %d, %d\n", i, j);
                    }
                    return; // Sortir de la fonction après avoir placé le drapeau
                }
            }
        }
    }
}

bool VerifierVictoire(Plateau plateau) {
    int casesRevelees = 0;
    int casesTotales = plateau.hauteur* plateau.largeur;
    int casesMines = plateau.nombreBombes;

    for (int i = 0; i < plateau.hauteur; i++) {
        for (int j = 0; j < plateau.largeur; j++) {
            if (plateau.cases[i][j].decouverte) {
                casesRevelees++;
            }
        }
    }

    return casesRevelees == (casesTotales - casesMines);
}


int main(int argc, char** args) {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Échec de l'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Démineur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 619, 400, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Échec de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int mouseX, mouseY;
    int gamestate = 0;
    int PInitialiser = 0;
    int dif;
    Plateau plateau;
    int x;
    int y;

    // Boucle principale
    while (1) {
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Fermer la fenêtre et quitter le programme
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (gamestate == 0) {
                        // Gestion des clics dans le menu
                        if (mouseX >= 32 && mouseX <= 176) {
                            if (mouseY >= 122 && mouseY <= 166) {
                                gamestate = 1;
                                dif = 1;
                            } else if (mouseY >= 202 && mouseY <= 246) {
                                gamestate = 1;
                                dif = 2;
                            } else if (mouseY >= 285 && mouseY <= 326) {
                                gamestate = 1;
                                dif = 3;
                            }
                        }
                    } if(gamestate==1) {
                // Gestion des clics sur les cases du plateau
                gamestate=ClicSurCase(renderer, mouseX, mouseY, gamestate, &plateau,x,y);
                ClicDrapeau(renderer,mouseX,mouseY,&plateau,x,y);
            }if ((gamestate == 2 || gamestate == 3) && mouseX >= 444 && mouseX <= 588 && mouseY >= 282 && mouseY <= 326) {
                gamestate = 0;
                PInitialiser =0;


            }
                    break;
            }
        }
        if (gamestate == 1) {
            if (VerifierVictoire(plateau)) {
                gamestate = 3;
            }
        }

        // Nettoyage de l'écran
        SDL_SetRenderDrawColor(renderer, 170, 162, 162, 0);
        SDL_RenderClear(renderer);

        // Affichage du menu ou du plateau de jeu en fonction de l'état du jeu
        if (gamestate == 0) {
            AfficherMenu(renderer);
        } else {
            if (dif == 1 && PInitialiser == 0) {
                Initialiser(10, 10, 15, &plateau);
                PInitialiser = 1;
                x = 210;
                y= 100;
            } else if (dif == 2 && PInitialiser == 0) {
                Initialiser(15, 15, 30, &plateau);
                PInitialiser = 1;
                x=160;
                y=50;
            } else if (dif == 3 && PInitialiser == 0) {
                Initialiser(20, 20, 50, &plateau);
                PInitialiser = 1;
                x=110;
                y=0;
            }
            if(gamestate==1) {
                AfficherPlateau(renderer, &plateau,x,y);
            }
            if(gamestate==2){
                Defaite(renderer);
            }
            if(gamestate==3){
                Victoire(renderer);
            }

        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}
