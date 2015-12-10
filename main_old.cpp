#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define RESOLUTION_X 640
#define RESOLUTION_Y 640
#define PLATEAU_X    407
#define PLATEAU_Y    340
#define TAILLE_CASE  100

/*
void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEMOTION:
                position.x = event.motion.x;
                position.y = event.motion.y;
                break;
        }

        SDL_BlitSurface(chevre, NULL, ecran, &position);
        SDL_Flip(ecran);
    }
}
*/

void AfficheTigre(SDL_Surface *tigre, SDL_Surface *ecran, int x, int y)
{
    SDL_Rect position;
    SDL_Color ColorPolice = {0, 0, 0};

    x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) + TAILLE_CASE * x;
    y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2) + TAILLE_CASE * y;

    // Tigre
    position.x = x - (tigre->w / 2) + 2;
    position.y = y - (tigre->h) + 12;
    SDL_BlitSurface(tigre, NULL, ecran, &position);
    return;
}

void AfficheChevre(SDL_Surface *chevre, SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int x, int y, int nb)
{
    if(nb > 0)
    {
        SDL_Rect position;
        SDL_Color ColorPolice = {0, 0, 0};
        char NbChevres[3];

        x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) + TAILLE_CASE * x;
        y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2) + TAILLE_CASE * y;

        // Chèvre
        position.x = x - (chevre->w / 4) - 3;
        position.y = y - (chevre->h) + 12;
        SDL_BlitSurface(chevre, NULL, ecran, &position);

        if(nb > 1)
        {
            sprintf(NbChevres, "%d", nb);
            texte = TTF_RenderText_Blended(police, NbChevres, ColorPolice);
            position.x = x - (texte->w / 2) + 6;
            position.y = y - 15;
            SDL_BlitSurface(texte, NULL, ecran, &position);
        }
    }
    return;
}

typedef struct s_plateau
{
    char nom;
    int nb;
} t_plateau;

void initPlateau(t_plateau plateau_jeu[5][5])
{
    int x, y;
    for(y = 0; y <= 4; y++)
    {
        for(x = 0; x <= 4; x++)
        {
            plateau_jeu[x][y].nb = 0;
            plateau_jeu[x][y].nom = 0;
        }
    }
    plateau_jeu[2][1].nb = 1;
    plateau_jeu[2][1].nom = 'T';

    plateau_jeu[2][3].nb = 1;
    plateau_jeu[2][3].nom = 'T';

    plateau_jeu[1][0].nb = 5;
    plateau_jeu[1][0].nom = 'C';

    plateau_jeu[3][0].nb = 5;
    plateau_jeu[3][0].nom = 'C';

    plateau_jeu[1][2].nb = 5;
    plateau_jeu[1][2].nom = 'C';

    plateau_jeu[3][2].nb = 5;
    plateau_jeu[3][2].nom = 'C';
}

int main(int argc, char *argv[])
{
    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Initialisation de SDL TTF : gestion de la police
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialisation des variables et pointeurs
    SDL_Surface *ecran = NULL;
    SDL_Surface *fond = NULL;
    SDL_Surface *plateau = NULL;
    SDL_Surface *texte = NULL;
    SDL_Surface *texte2 = NULL;
    SDL_Surface *texte3 = NULL;
    SDL_Surface *texte4 = NULL;
    SDL_Surface *texte5 = NULL;
    SDL_Surface *tigre = NULL, *tigre_hover = NULL, *tigre_active = NULL;
    SDL_Surface *chevre = NULL, *chevre_hover = NULL, *chevre_active = NULL;
    SDL_Surface *cursor = NULL;
    TTF_Font *police = NULL, *police2 = NULL, *police3 = NULL;
    SDL_Rect positionFond, position, positionPlateau, positionCursor, positionTxt1, positionTxt2, positionTxt3, positionTxt4, positionTxt5;
    positionFond.x = 0;
    positionFond.y = 0;
    position.x = 0;
    position.y = 0;

    SDL_Color ColorPolice = {0, 0, 0};

    // Variables du jeu
    int joueur = 1;
    int NbChevres = 20;
    char NbChevresTXT[3];
    int x, y;
    t_plateau plateau_jeu[5][5];

    // Initialisation du plateau de jeu
    initPlateau(plateau_jeu);

    // Chargement de la police
    police = TTF_OpenFont("Ressources/comic.ttf", 24);
    police2 = TTF_OpenFont("Ressources/comicbd.ttf", 24);
    police3 = TTF_OpenFont("Ressources/comic.ttf", 20);

    /* Chargement de l'icône */
    SDL_WM_SetIcon(SDL_LoadBMP("Ressources/icone.bmp"), NULL);

    ecran = SDL_SetVideoMode(RESOLUTION_X, RESOLUTION_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) // Si l'ouverture a échoué, on écrit l'erreur et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Titre de la fenêtre
    SDL_WM_SetCaption("Bagh Bandi", NULL);

    /* Chargement des images */
    fond = IMG_Load("Ressources/table.png");
    plateau = IMG_Load("Ressources/plateau.png");
    tigre = IMG_Load("Ressources/tigre.png");
    tigre_hover = IMG_Load("Ressources/tigre_hover.png");
    tigre_active = IMG_Load("Ressources/tigre_active.png");
    chevre = IMG_Load("Ressources/chevre.png");
    chevre_hover = IMG_Load("Ressources/chevre_hover.png");
    chevre_active = IMG_Load("Ressources/chevre_active.png");

    // Couleur de fond (blanc)
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(fond, NULL, ecran, &positionFond);

    positionPlateau.x = (RESOLUTION_X / 2) - (PLATEAU_X / 2);
    positionPlateau.y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2);

    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(plateau, NULL, ecran, &positionPlateau);

    // [DEBUT] Affichage : Tour du joueur
    if(joueur == 1)
    {
        texte = TTF_RenderText_Blended(police, "Au tour de la", ColorPolice);
        texte2 = TTF_RenderText_Blended(police2, " chèvre ", ColorPolice);
    }
    else
    {
        texte = TTF_RenderText_Blended(police, "Au tour du", ColorPolice);
        texte2 = TTF_RenderText_Blended(police2, " tigre ", ColorPolice);
    }

    texte3 = TTF_RenderText_Blended(police, "de jouer !", ColorPolice);

    positionTxt1.x = (RESOLUTION_X / 2) - (texte->w / 2) - (texte2->w / 2) - (texte3->w / 2);
    positionTxt1.y = 5;

    positionTxt2.x = (RESOLUTION_X / 2) + (texte->w / 2) - (texte2->w / 2) - (texte3->w / 2);
    positionTxt2.y = 5;

    positionTxt3.x = (RESOLUTION_X / 2) + (texte->w / 2) + (texte2->w / 2) - (texte3->w / 2);
    positionTxt3.y = 5;

    /*
    SDL_BlitSurface(texte, NULL, ecran, &positionTxt1);
    SDL_BlitSurface(texte2, NULL, ecran, &positionTxt2);
    SDL_BlitSurface(texte3, NULL, ecran, &positionTxt3);
    */
    // [FIN] Affichage : Tour du joueur

    // [DEBUT] Affichage : Nombre de Chèvres restant

    sprintf(NbChevresTXT, "%d", NbChevres);
    texte4 = TTF_RenderText_Blended(police, "Nombre de Chèvres restant : ", ColorPolice);
    texte5 = TTF_RenderText_Blended(police2, NbChevresTXT, ColorPolice);


    positionTxt4.x = (RESOLUTION_X / 2) - (texte4->w / 2) - (texte5->w / 2);
    positionTxt4.y = RESOLUTION_Y - 35;

    positionTxt5.x = (RESOLUTION_X / 2) + (texte4->w / 2) - (texte5->w / 2);
    positionTxt5.y = RESOLUTION_Y - 35;

    /*
    SDL_BlitSurface(texte4, NULL, ecran, &positionTxt4);
    SDL_BlitSurface(texte5, NULL, ecran, &positionTxt5);
    */
    // [FIN] Affichage : Nombre de Chèvres restant

    // [DEBUT] Affichage : Joueur
    /*
    for(y = 0; y <= 4; y++)
    {
        for(x = 0; x <= 4; x++)
        {
            if(plateau_jeu[x][y].nom == 'C')
            {
                AfficheChevre(chevre, ecran, texte, police3, x, y, plateau_jeu[x][y].nb);
            }
            else if(plateau_jeu[x][y].nom == 'T')
            {
                AfficheTigre(tigre, ecran, x, y);
            }
        }
    }
    */
    // [FIN] Affichage : Joueur

/* ******************************************************************* */

    cursor = IMG_Load("Ressources/curseur.png");
    SDL_EnableKeyRepeat(100, 100);

    int continuer = 1;
    SDL_Event event;
    positionCursor.x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) - (cursor->w / 2);
    positionCursor.y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2) - (cursor->h / 2);

    int CursorX = 0;
    int CursorY = 0;
    int CursorXtemp = 0;
    int CursorYtemp = 0;
    int active = 0;
    t_plateau pionActif;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            // [DEBUT] Gestion des événements clavier
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        if(active == 1)
                        {
                            if(CursorXtemp != CursorX || CursorYtemp != CursorY)
                            {
                                // Vérifier le déplacement
                                // plateau_jeu[CursorX][CursorY].nom == 'C';
                                // plateau_jeu[CursorX][CursorY].nb++;
                                //active = 0;
                            }
                            else
                            {
                                if(plateau_jeu[CursorXtemp][CursorYtemp].nom == 'C')
                                {
                                    plateau_jeu[CursorXtemp][CursorYtemp].nb++;
                                }
                                active = 0;
                            }
                        }
                        else if(plateau_jeu[CursorX][CursorY].nom != 0 && plateau_jeu[CursorX][CursorY].nb != 0 && active == 0)
                        {
                            active = 1;
                            pionActif.nom = plateau_jeu[CursorX][CursorY].nom;
                            pionActif.nb = 1;
                            if(plateau_jeu[CursorX][CursorY].nom == 'C' && plateau_jeu[CursorX][CursorY].nb > 0)
                            {
                                CursorXtemp = CursorX;
                                CursorYtemp = CursorY;
                                plateau_jeu[CursorX][CursorY].nb--;
                            }
                        }
                        break;
                    case SDLK_UP:
                        CursorY--;
                        break;
                    case SDLK_DOWN:
                        CursorY++;
                        break;
                    case SDLK_RIGHT:
                        CursorX++;
                        break;
                    case SDLK_LEFT:
                        CursorX--;
                        break;
                }
                break;
                /*
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        if(active == 1)
                        {
                            if(CursorXtemp != CursorX && CursorYtemp != CursorY)
                            {
                                // Vérifier le déplacement
                                printf("Deplacement OK");
                            }
                            else
                            {
                                plateau_jeu[CursorXtemp][CursorYtemp].nb++;
                                active = 0;
                            }
                        }
                        break;
                }
                break;
                */
            // [FIN] Gestion des événements clavier
            // [DEBUT] Gestion des evenements souris
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(plateau_jeu[CursorX][CursorY].nom != 0 && plateau_jeu[CursorX][CursorY].nb != 0 && active == 0)
                    {
                        active = 1;
                        pionActif.nom = plateau_jeu[CursorX][CursorY].nom;
                        pionActif.nb = 1;
                        if(plateau_jeu[CursorX][CursorY].nom == 'C' && plateau_jeu[CursorX][CursorY].nb > 0)
                        {
                            CursorXtemp = CursorX;
                            CursorYtemp = CursorY;
                            plateau_jeu[CursorX][CursorY].nb--;
                        }
                    }
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    active = 0;

                    CursorX = CursorXtemp;
                    CursorY = CursorYtemp;

                    plateau_jeu[CursorXtemp][CursorYtemp].nb++;
                }
                break;

            //[FIN] SOURIS
        }

        if(CursorX > 4)
        {
            CursorX = 4;
        }
        else if(CursorX < 0)
        {
            CursorX = 0;
        }

        if(CursorY > 4)
        {
            CursorY = 4;
        }
        else if(CursorY < 0)
        {
            CursorY = 0;
        }
        positionCursor.x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) - (cursor->w / 2) + TAILLE_CASE * CursorX + 5;
        positionCursor.y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2) - (cursor->h / 2) + TAILLE_CASE * CursorY;

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_BlitSurface(plateau, NULL, ecran, &positionPlateau);
        SDL_BlitSurface(texte, NULL, ecran, &positionTxt1);
        SDL_BlitSurface(texte2, NULL, ecran, &positionTxt2);
        SDL_BlitSurface(texte3, NULL, ecran, &positionTxt3);
        SDL_BlitSurface(texte4, NULL, ecran, &positionTxt4);
        SDL_BlitSurface(texte5, NULL, ecran, &positionTxt5);
        SDL_BlitSurface(cursor, NULL, ecran, &positionCursor);

        for(y = 0; y <= 4; y++)
        {
            for(x = 0; x <= 4; x++)
            {
                if(plateau_jeu[x][y].nom == 'C')
                {
                    if(x == CursorX && y == CursorY && joueur == 1)
                    {
                        AfficheChevre(chevre_hover, ecran, texte, police3, x, y, plateau_jeu[x][y].nb);
                    }
                    else
                    {
                        AfficheChevre(chevre, ecran, texte, police3, x, y, plateau_jeu[x][y].nb);
                    }
                }
                else if(plateau_jeu[x][y].nom == 'T')
                {
                    if(x == CursorX && y == CursorY && joueur == 2)
                    {
                        AfficheTigre(tigre_hover, ecran, x, y);
                    }
                    else
                    {
                        AfficheTigre(tigre, ecran, x, y);
                    }
                }
            }
        }

        if(active == 1 && pionActif.nom == 'C' && joueur == 1)
        {
            AfficheChevre(chevre_active, ecran, texte, police3, CursorX, CursorY, 1);
        }
        else if(active == 1 && pionActif.nom == 'T' && joueur == 2)
        {
            AfficheTigre(tigre_hover, ecran, CursorX, CursorY);
        }
        SDL_Flip(ecran);
    }
/* ******************************************************************* */

    // Fermeture de la police
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
    TTF_CloseFont(police3);
    TTF_Quit();

    // Libération de la mémoire
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(texte4);
    SDL_FreeSurface(texte5);
    SDL_FreeSurface(tigre);
    SDL_FreeSurface(tigre_hover);
    SDL_FreeSurface(chevre);
    SDL_FreeSurface(chevre_hover);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(plateau);

    // Arrêt de la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
