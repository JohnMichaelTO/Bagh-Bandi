#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jouer.h"

int main(int argc, char *argv[])
{
    // Initialisation de SDL TTF : gestion de la police & erreur
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Variables SDL
    SDL_Surface *ecran = NULL;
    SDL_Surface *menu = NULL;
    SDL_Surface *fond = NULL;
    SDL_Surface *fond_menu = NULL;
    SDL_Surface *fond_menu2 = NULL;
    TTF_Font *police = NULL;
    SDL_Rect positionMenu;
    SDL_Rect positionFond;
    SDL_Rect positionTexteHaut;
    SDL_Rect positionTexteBas;
    SDL_Color ColorPolice = {0, 0, 0};
    SDL_Event event;

    // Variables du jeu et lors d'une pause
    int continuer = 1;
    int joueur = 1;
    int pCursorX = 0;
    int pCursorY = 0;
    t_plateau plateau_jeu[5][5];

    // Initialisation du plateau de jeu
    initPlateau(plateau_jeu);

    // Chargement de la police
    police = TTF_OpenFont("Ressources/comic.ttf", 26);

    // Position de l'image de fond
    positionFond.x = 0;
    positionFond.y = 0;

    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);

    /* Chargement de l'icône */
    SDL_WM_SetIcon(IMG_Load("Ressources/icone.png"), NULL);

    ecran = SDL_SetVideoMode(RESOLUTION_X, RESOLUTION_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) // Si l'ouverture a échoué, on écrit l'erreur et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Titre de la fenêtre
    SDL_WM_SetCaption("Bagh Bandi", NULL);

    // Chargement des images
    menu = IMG_Load("Ressources/boite-jeu.png");
    fond_menu = IMG_Load("Ressources/table-fond.png");
    fond_menu2 = IMG_Load("Ressources/table-fond2.png");
    fond = IMG_Load("Ressources/table.png");

    // Positon de la boîte du jeu (image)
    positionMenu.x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) + 60;
    positionMenu.y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2);

/***********************************************/
    do
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_F1:
                        continuer = jouer(ecran, fond, positionFond, plateau_jeu, &joueur, &pCursorX, &pCursorY);
                        break;
                    case SDLK_F2:
                        // Gestion des touches du menu lors d'une pause
                        if(continuer == 2)
                        {
                            initPlateau(plateau_jeu);
                            joueur = 1;
                            pCursorX = 0;
                            pCursorY = 0;
                            continuer = jouer(ecran, fond, positionFond, plateau_jeu, &joueur, &pCursorX, &pCursorY);
                        }
                        else
                        {
                            continuer = aide(ecran, fond, positionFond, continuer);
                        }
                        break;
                    case SDLK_F3:
                        if(continuer == 2)
                        {
                            continuer = aide(ecran, fond, positionFond, continuer);
                        }
                        break;
                    case SDLK_a: // Q = A (clavier QWERTY)
                        continuer = 0;
                        break;
                }
                break;
        }

        // Effacement & affichage de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        // Gestion de l'image du menu lors d'une pause
        if(continuer == 2)
        {
            SDL_BlitSurface(fond_menu2, NULL, ecran, &positionFond);
        }
        else
        {
            SDL_BlitSurface(fond_menu, NULL, ecran, &positionFond);
        }
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        EcricreTexte(ecran, police, "BAGH BANDI", 0, 5);
        EcricreTexte(ecran, police, "Tapez l'option voulue !", 0, (RESOLUTION_Y - 45));
        SDL_Flip(ecran);
    } while(continuer != 0);
/***********************************************************/

    // Fermeture de la police
    TTF_CloseFont(police);
    TTF_Quit();

    // Libération de mémoire
    SDL_FreeSurface(menu);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(fond_menu);
    SDL_FreeSurface(fond_menu2);

    // Arrêt de la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
