#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "constantes.h"

// [DEBUT] Données : Fonction aide du jeu
int aide(SDL_Surface *ecran, SDL_Surface *fond, SDL_Rect positionFond, int continuer)
{
    // Initialisation de SDL TTF : gestion de la police
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialisation des variables et pointeurs
    SDL_Surface *plateau = NULL;
    SDL_Surface *plateau2 = NULL;
    SDL_Surface *plateau3 = NULL;
    SDL_Surface *plateau4 = NULL;
    SDL_Surface *texte = NULL;
    SDL_Surface *texte2 = NULL;
    SDL_Surface *texte3 = NULL;
    SDL_Surface *texte4 = NULL;
    SDL_Surface *texte5 = NULL;
    SDL_Surface *texte6 = NULL;
    TTF_Font *police = NULL, *police2 = NULL, *police3 = NULL, *police4 = NULL;
    SDL_Rect position, positionPlateau, positionCursor;
    position.x = 0;
    position.y = 0;

    // Chargement de la police
    police = TTF_OpenFont("Ressources/comic.ttf", 24);
    police2 = TTF_OpenFont("Ressources/comicbd.ttf", 24);
    police3 = TTF_OpenFont("Ressources/comic.ttf", 20);
    police4 = TTF_OpenFont("Ressources/comic.ttf", 16);

    /* Chargement des images */
    plateau = IMG_Load("Ressources/feuille.png");
    plateau2 = IMG_Load("Ressources/feuille2.png");
    plateau3 = IMG_Load("Ressources/feuille3.png");
    plateau4 = IMG_Load("Ressources/feuille4.png");

    positionPlateau.x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) + 30;
    positionPlateau.y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2) - 55;

    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(plateau, NULL, ecran, &positionPlateau);

/* ******************************************************************* */
    SDL_EnableKeyRepeat(100, 100);

    SDL_Event event;

    int continuer2 = 1;
    int Cursor = 0;

    while (continuer2 == 1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer2 = 0;
                break;
            // [DEBUT] Gestion des événements clavier
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer2 = 2;
                        break;
                    case SDLK_SPACE:
                        break;
                    case SDLK_LEFT:
                        Cursor--;
                        break;
                    case SDLK_RIGHT:
                        Cursor++;
                        break;
                    case SDLK_BACKSPACE:
                        break;
                    case SDLK_RETURN:
                    break;
                }
                break;
            // [FIN] Gestion des événements clavier
        }

        if(Cursor > 3)
        {
            Cursor = 3;
        }
        else if(Cursor < 0)
        {
            Cursor = 0;
        }

        // Effacement et affichage de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);

        if(Cursor == 1)
        {
            SDL_BlitSurface(plateau2, NULL, ecran, &positionPlateau);
            EcricreTexte(ecran, police3, "Vous pouvez utiliser les flèches <- et ->", 0, (RESOLUTION_Y - 52));
        }
        else if(Cursor == 2)
        {
            SDL_BlitSurface(plateau3, NULL, ecran, &positionPlateau);
            EcricreTexte(ecran, police3, "Vous pouvez utiliser les flèches <- et ->", 0, (RESOLUTION_Y - 52));
        }
        else if(Cursor == 3)
        {
            SDL_BlitSurface(plateau4, NULL, ecran, &positionPlateau);
            EcricreTexte(ecran, police3, "Vous pouvez utiliser la flèche <-", 0, (RESOLUTION_Y - 52));
        }
        else
        {
            SDL_BlitSurface(plateau, NULL, ecran, &positionPlateau);
            EcricreTexte(ecran, police3, "Vous pouvez utiliser la flèche ->", 0, (RESOLUTION_Y - 52));
        }

        EcricreTexte(ecran, police3, "Règles et commandes", 0, 10);
        EcricreTexte(ecran, police4, "pour naviguer à travers les pages", 0, (RESOLUTION_Y - 28));
        SDL_Flip(ecran);
    }
/* ******************************************************************* */

    if(continuer == 1 && continuer2 == 2)
    {
        continuer2 = 1;
    }

    // Fermeture de la police
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
    TTF_CloseFont(police3);
    TTF_CloseFont(police4);
    TTF_Quit();

    // Libération de la mémoire
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(texte4);
    SDL_FreeSurface(texte5);
    SDL_FreeSurface(texte6);
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(plateau2);
    SDL_FreeSurface(plateau3);
    SDL_FreeSurface(plateau4);

    return continuer2;
}
// [FIN] Données : Fonction aide du jeu
