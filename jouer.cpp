#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jouer.h"

// [DEBUT] Affichage : Affiche du texte par TTF_Font
void EcricreTexte(SDL_Surface *ecran, TTF_Font *police, char txt[20], int positionX, int positionY)
{
    SDL_Surface *texte;
    SDL_Rect positionTxt;
    SDL_Color ColorPolice = {0, 0, 0};

    texte = TTF_RenderText_Blended(police, txt, ColorPolice);

    positionTxt.x = (RESOLUTION_X / 2) - (texte->w / 2) + positionX;
    positionTxt.y = positionY;

    SDL_BlitSurface(texte, NULL, ecran, &positionTxt);
    SDL_FreeSurface(texte);
}
// [FIN] Affichage : Affiche du texte par TTF_Font

// [DEBUT] Affichage : Affiche un pion
void AffichePion(SDL_Surface *pion, SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int x, int y, char nom, int nb)
{
    if(nb > 0)
    {
        SDL_Rect position;
        SDL_Color ColorPolice = {0, 0, 0};
        char NB[3];

        x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) + TAILLE_CASE * x;
        y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2) + TAILLE_CASE * y;

        if(nom == 'C')
        {
            // Chèvre
            position.x = x - (pion->w / 4) - 3;
            position.y = y - (pion->h) + 12;
        }
        else
        {
            // Tigre
            position.x = x - (pion->w / 2) + 2;
            position.y = y - (pion->h) + 12;
        }
        SDL_BlitSurface(pion, NULL, ecran, &position);

        if(nb > 1)
        {
            sprintf(NB, "%d", nb);
            texte = TTF_RenderText_Blended(police, NB, ColorPolice);
            position.x = x - (texte->w / 2) + 6;
            position.y = y - 15;
            SDL_BlitSurface(texte, NULL, ecran, &position);
        }
    }
    return;
}
// [FIN] Affichage : Affiche du texte par TTF_Font

// [DEBUT] Données : Initialisation du tableau de jeu
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
// [FIN] Données : Initialisation du tableau de jeu

// [DEBUT] Affichage : Messages d'informations (tour, fin de partie, ...)
void AfficheTour(SDL_Surface *ecran, TTF_Font *police, TTF_Font *police2, TTF_Font *police3, int joueur, int cas)
{
    if(joueur < 0)
    {
        if(joueur == -1)
        {
            EcricreTexte(ecran, police3, "Il reste moins de 5 chèvres !", 0, 33);
        }
        else
        {
            EcricreTexte(ecran, police3, "Les tigres sont bloqués !", 0, 33);
        }
        EcricreTexte(ecran, police, "Fin de la partie", 0, 5);
    }
    else
    {
        if(joueur == 1)
        {
            EcricreTexte(ecran, police, "Au tour de la", -101, 5);
            EcricreTexte(ecran, police2, " chèvre ", 18, 5);
            EcricreTexte(ecran, police, "de jouer !", 119, 5);
        }
        else
        {
            EcricreTexte(ecran, police, "Au tour du", -91, 5);
            EcricreTexte(ecran, police2, " tigre ", 5, 5);
            EcricreTexte(ecran, police, "de jouer !", 95, 5);
        }

        if(cas == 1)
        {
            EcricreTexte(ecran, police3, "Mauvaise sélection ! Merci de rejouer.", 0, 33);
        }
        else if(cas == 2)
        {
            EcricreTexte(ecran, police3, "Vous pouvez rejouer ou passer votre tour.", 0, 33);
        }
    }

    /* Calcul des coordonnées pour la méthode d'utilisation de la fonction
    test = (texte->w / 2) + (texte2->w / 2);
    sprintf(texteb, "%d", test);
    EcricreTexte(ecran, police, texteb, 0, 100);
    */
}
// [FIN] Affichage : Messages d'informations (tour, fin de partie, ...)

// [DEBUT] Affichage : Nombre de Chèvres restant
void AfficheChevresRestant(SDL_Surface *ecran, TTF_Font *police, SDL_Surface *texte, TTF_Font *police2, SDL_Surface *texte2, int nb)
{
    SDL_Rect positionTxt1, positionTxt2;
    SDL_Color ColorPolice = {0, 0, 0};
    char NbChevresTXT[3];

    if(nb < 0)
    {
        if(nb == -1)
        {
            texte = TTF_RenderText_Blended(police, "Les Chèvres remportent la partie", ColorPolice);
        }
        else
        {
            texte = TTF_RenderText_Blended(police, "Les Tigres remportent la partie", ColorPolice);
        }
        positionTxt1.x = (RESOLUTION_X / 2) - (texte->w / 2);
    }
    else
    {
        sprintf(NbChevresTXT, "%d", nb);
        texte = TTF_RenderText_Blended(police, "Nombre de Chèvres restant : ", ColorPolice);
        texte2 = TTF_RenderText_Blended(police2, NbChevresTXT, ColorPolice);
        positionTxt1.x = (RESOLUTION_X / 2) - (texte->w / 2) - (texte2->w / 2);
    }

    positionTxt1.y = RESOLUTION_Y - 35;

    SDL_BlitSurface(texte, NULL, ecran, &positionTxt1);

    if(nb >= 0)
    {
        positionTxt2.x = (RESOLUTION_X / 2) + (texte->w / 2) - (texte2->w / 2);
        positionTxt2.y = RESOLUTION_Y - 35;
        SDL_BlitSurface(texte2, NULL, ecran, &positionTxt2);
    }
}
// [FIN] Affichage : Nombre de Chèvres restant

// [DEBUT] Données : Compte le nombre de chèvres restant
int detectionChevres(t_plateau plateau_jeu[5][5], int active, int joueur)
{
    int x, y;
    int nb = 0;
    for(y = 0; y <= 4; y++)
    {
        for(x = 0; x <= 4; x++)
        {
            if(plateau_jeu[x][y].nom == 'C')
            {
                nb = nb + plateau_jeu[x][y].nb;
            }
        }
    }

    if(active == 1 && joueur == 1)
    {
        nb = nb + 1;
    }
    return nb;
}
// [FIN] Données : Compte le nombre de chèvres restant

// [DEBUT] Affichage : Affiche tous les pions en se basant sur le tableau de données
void AffichePionsTotal(SDL_Surface *ecran, SDL_Surface *tigre, SDL_Surface *tigre_hover, SDL_Surface *tigre_active,
SDL_Surface *chevre, SDL_Surface *chevre_hover, SDL_Surface *chevre_active,
TTF_Font *police, SDL_Surface *texte, t_plateau plateau_jeu[5][5], int CursorX, int CursorY, int joueur, t_plateau pionActif, int active)
{
    int x, y;
    for(y = 0; y <= 4; y++)
    {
        for(x = 0; x <= 4; x++)
        {
            if(plateau_jeu[x][y].nom == 'C')
            {
                if(x == CursorX && y == CursorY && joueur == 1)
                {
                    AffichePion(chevre_hover, ecran, texte, police, x, y, plateau_jeu[x][y].nom, plateau_jeu[x][y].nb);
                }
                else
                {
                    AffichePion(chevre, ecran, texte, police, x, y, plateau_jeu[x][y].nom, plateau_jeu[x][y].nb);
                }
            }
            else if(plateau_jeu[x][y].nom == 'T')
            {
                if(x == CursorX && y == CursorY && joueur == 2)
                {
                    AffichePion(tigre_hover, ecran, texte, police, x, y, plateau_jeu[x][y].nom, plateau_jeu[x][y].nb);
                }
                else
                {
                    AffichePion(tigre, ecran, texte, police, x, y, plateau_jeu[x][y].nom, plateau_jeu[x][y].nb);
                }
            }
        }
    }

    if(active == 1 && pionActif.nom == 'C' && joueur == 1)
    {
        AffichePion(chevre_active, ecran, texte, police, CursorX, CursorY, pionActif.nom, pionActif.nb);
    }
    else if(active == 1 && pionActif.nom == 'T' && joueur == 2)
    {
        AffichePion(tigre_active, ecran, texte, police, CursorX, CursorY, pionActif.nom, pionActif.nb);
    }
}
// [FIN] Données : Affiche tous les pions en se basant sur le tableau de données

// [DEBUT] Données : Vérification d'un déplacement normal
int verifCoordonnees(t_plateau plateau_jeu[5][5], int x, int y, int xN, int yN)
{
    int erreur = 1;
    if(x == xN && y == yN)
    {
        erreur = 0;
    }
    else
    {
        if(((x % 2) == 0 && (y % 2) == 0) || ((x % 2) == 1 && (y % 2) == 1))
        {
            if(((xN == x - 1) && (yN == y - 1 || yN == y || yN == y + 1)) || ((xN == x) && (yN == y - 1 || yN == y || yN == y + 1)) || ((xN == x + 1) && (yN == y - 1 || yN == y || yN == y + 1)))
            {
                erreur = 1;
            }
            else
            {
                erreur = 0;
            }
        }
        else if((((x % 2) == 0 && (y % 2) == 1) || ((x % 2) == 1 && (y % 2) == 0)))
        {
            if((xN == x && (yN == y - 1 || yN == y + 1)) || (yN == y && (xN == x - 1 || xN == x + 1)))
            {
                erreur = 1;
            }
            else
            {
                erreur = 0;
            }
        }
        else
        {
            erreur = 0;
        }
    }
    return erreur;
}
// [FIN] Données : Vérification d'un déplacement normal

// [DEBUT] Données : Calcul les coordonnées du milieu
int calculMilieu(int x, int y, int xN, int yN, char coordonnee)
{
    double xTemp, yTemp;
    int xM, yM;
    int result = -1;

    xTemp = (x + xN) / 2.0;
    yTemp = (y + yN) / 2.0;

    xM = (int)xTemp;
    yM = (int)yTemp;

    if((xTemp == xM && yTemp == yM)/* && (x != col || y != lig)*/)
    {
        if(coordonnee == 'x')
        {
            result = xM;
        }
        else if(coordonnee == 'y')
        {
            result = yM;
        }
    }
    return result;
}
// [FIN] Données : Calcul les coordonnées du milieu

// [DEBUT] Données : Vérification d'un déplacement possible
int verifDeplacement(t_plateau plateau_jeu[5][5], int x, int y, int xN, int yN)
{
    int xC, yC;
    int erreur = 0;

    if(verifCoordonnees(plateau_jeu, x, y, xN, yN) == 1)
    {
        erreur = 1;
        // printf("Verif deplacement possible : (%d ; %d) => (%d ; %d)\n", x, y, xN, yN);
    }
    else if(plateau_jeu[x][y].nom == 'T')
    {
        xC = calculMilieu(x, y, xN, yN, 'x');
        yC = calculMilieu(x, y, xN, yN, 'y');

        if(xC != -1 && yC != -1)
        {
            if(plateau_jeu[xC][yC].nom == 'C' && plateau_jeu[xN][yN].nom == 0 && verifCoordonnees(plateau_jeu, xC, yC, xN, yN) == 1)
            {
                erreur = 2;
                // printf("Verif saut possible : (%d ; %d) => (%d ; %d) : chevre (%d ; %d)\n", x, y, xN, yN, xC, yC);
            }
        }
    }
    return erreur;
}
// [FIN] Données : Vérification d'un déplacement possible

// [DEBUT] Données : Vérification d'un saut possible
int verifSautMultiple(t_plateau plateau_jeu[5][5], int x, int y, int fin)
{
    int cpt, cpt2;
    int erreur = 0;

    for(cpt = y - 2; cpt <= y + 2; cpt = cpt + 1)
    {
        for(cpt2 = x - 2; cpt2 <= x + 2; cpt2 = cpt2 + 1)
        {
            if((cpt >= 0 && cpt <= 4) && (cpt2 >= 0 && cpt2 <= 4))
            {
                if(plateau_jeu[cpt2][cpt].nom == 0 && plateau_jeu[cpt2][cpt].nb == 0)
                {
                    if(verifDeplacement(plateau_jeu, x, y, cpt2, cpt) == 2)
                    {
                        erreur = 1;
                        // printf("Saut possible : (%d ; %d) => (%d ; %d)\n", x, y, cpt2, cpt);
                    }

                    if(fin == 1 && verifDeplacement(plateau_jeu, x, y, cpt2, cpt) == 1)
                    {
                        erreur = 1;
                        // printf("Deplacement possible : (%d ; %d) => (%d ; %d)\n", x, y, cpt2, cpt);
                    }
                }
            }
        }
    }
    return erreur;
}
// [FIN] Données : Vérification d'un saut possible

// [DEBUT] Données : Changement de joueur
void changementJoueur(int *joueur)
{
    if(*joueur == 1)
    {
        *joueur = 2;
        // printf("Changement de joueur !! TIGRE QUI JOUE !\r\n\n");
    }
    else
    {
        *joueur = 1;
        // printf("Changement de joueur !! CHEVRE QUI JOUE !\r\n\n");
    }
}
// [FIN] Données : Changement de joueur

// [DEBUT] Données : Déplacement effectué et mise du pion déplacé dans le tableau
void plateauDeplacement(t_plateau plateau_jeu[5][5], int CursorXT, int CursorYT, char pionNom, int pionNb)
{
    plateau_jeu[CursorXT][CursorYT].nom = pionNom;
    plateau_jeu[CursorXT][CursorYT].nb = pionNb;
}
// [FIN] Données : Déplacement effectué et mise du pion déplacé dans le tableau

// [DEBUT] Données : Sélection d'un pion
void selectPion (t_plateau plateau_jeu[5][5], char *PionActifNom, int *PionActifNb, int *CursorXtemp, int *CursorYtemp, int CursorX, int CursorY, int *active)
{
    *PionActifNom = plateau_jeu[CursorX][CursorY].nom;
    *CursorXtemp = CursorX;
    *CursorYtemp = CursorY;
     plateau_jeu[CursorX][CursorY].nb--;
    *active = 1;
    *PionActifNb = 1;
}
// [FIN] Données : Sélection d'un pion

// [DEBUT] Données : Annuler la sélection / validation
void erreurValidation(t_plateau plateau_jeu[5][5], char PionActifNom, int PionActifNb, int CursorXtemp, int CursorYtemp, int *CursorX, int *CursorY, int *active, int multiple, int *etat, int etatNum)
{
    if(multiple == 0)
    {
        *active = 0;

        if(plateau_jeu[CursorXtemp][CursorYtemp].nom == PionActifNom)
        {
            *CursorX = CursorXtemp;
            *CursorY = CursorYtemp;
            plateau_jeu[CursorXtemp][CursorYtemp].nb = plateau_jeu[CursorXtemp][CursorYtemp].nb + PionActifNb;
            *etat = etatNum;
        }
    }
    else
    {
        *CursorX = CursorXtemp;
        *CursorY = CursorYtemp;
    }
}
// [FIN] Données : Annuler la sélection / validation

// [DEBUT] Données : Vérification de la fin de partie
int finPartie(t_plateau plateau_jeu[5][5], int active, int joueur)
{
    int cpt, cpt2;
    int erreur = 0;
    int continuer = 0;

    for(cpt = 0; cpt <= 4; cpt = cpt + 1)
    {
        for(cpt2 = 0; cpt2 <= 4; cpt2 = cpt2 + 1)
        {
            if(plateau_jeu[cpt2][cpt].nom == 'T' && verifSautMultiple(plateau_jeu, cpt2, cpt, 1) == 1)
            {
                erreur = erreur + 1;
            }
        }
    }

    if(detectionChevres(plateau_jeu, active, joueur) < 5 && erreur > 0)
    {
        continuer = 1; // Les chèvres perdent la partie
        initPlateau(plateau_jeu);
    }
    else if(erreur == 0)
    {
        continuer = 2; // Les tigres perdent la partie
        initPlateau(plateau_jeu);
    }
    else
    {
        continuer = 0;
    }
    return continuer;
}
// [FIN] Données : Vérification de la fin de partie

// [DEBUT] Données : Fonction principal du jeu
int jouer(SDL_Surface *ecran, SDL_Surface *fond, SDL_Rect positionFond, t_plateau plateau_jeu[5][5], int *joueur, int *pCursorX, int *pCursorY)
{
    // Initialisation de SDL TTF : gestion de la police
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialisation des variables et pointeurs
    SDL_Surface *plateau = NULL;
    SDL_Surface *plateau_fin = NULL;
    SDL_Surface *tigre = NULL, *tigre_hover = NULL, *tigre_active = NULL;
    SDL_Surface *chevre = NULL, *chevre_hover = NULL, *chevre_active = NULL;
    SDL_Surface *texte = NULL;
    SDL_Surface *texte2 = NULL;
    SDL_Surface *texte3 = NULL;
    SDL_Surface *cursor = NULL;
    TTF_Font *police = NULL, *police2 = NULL, *police3 = NULL, *police4 = NULL;
    SDL_Rect position, positionPlateau, positionPlateauFin, positionCursor;
    position.x = 0;
    position.y = 0;

    // Chargement des polices
    police = TTF_OpenFont("Ressources/comic.ttf", 24);
    police2 = TTF_OpenFont("Ressources/comicbd.ttf", 24);
    police3 = TTF_OpenFont("Ressources/comic.ttf", 20);
    police4 = TTF_OpenFont("Ressources/comic.ttf", 16);

    /* Chargement des images */
    plateau = IMG_Load("Ressources/plateau.png");
    plateau_fin = IMG_Load("Ressources/plateau_fin.png");
    tigre = IMG_Load("Ressources/tigre.png");
    tigre_hover = IMG_Load("Ressources/tigre_hover.png");
    tigre_active = IMG_Load("Ressources/tigre_active.png");
    chevre = IMG_Load("Ressources/chevre.png");
    chevre_hover = IMG_Load("Ressources/chevre_hover.png");
    chevre_active = IMG_Load("Ressources/chevre_active.png");
    cursor = IMG_Load("Ressources/curseur.png");

    positionPlateau.x = (RESOLUTION_X / 2) - (PLATEAU_X / 2);
    positionPlateau.y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2);

    positionPlateauFin.x = (RESOLUTION_X / 2) - (321 / 2);
    positionPlateauFin.y = (RESOLUTION_Y / 2) - (372 / 2);

    /* Affichage de l'image plateau */
    SDL_BlitSurface(plateau, NULL, ecran, &positionPlateau);

/* ******************************************************************* */


    SDL_EnableKeyRepeat(100, 100);
    SDL_Event event;

    // Variables du jeu
    int NbChevres;
    int continuer = 1;
    int fin = 0;
    int CursorX = *pCursorX;
    int CursorY = *pCursorY;
    int CursorXtemp = 0;
    int CursorYtemp = 0;
    int active = 0;
    int Deplacement = 0;
    int verifierDeplacement;
    int xC = 0, yC = 0;
    int etat = 0;
    int multiple = 0;
    t_plateau pionActif;

    do
    {
        if(active == 0)
        {
            pionActif.nom = 0;
            pionActif.nb = 0;
        }

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
                    case SDLK_ESCAPE:
                        continuer = 2;
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
                    case SDLK_BACKSPACE:
                        initPlateau(plateau_jeu);
                        *joueur = 1;
                        break;
                    case SDLK_RETURN: // Passer le tour
                        if(multiple == 1 && active == 1)
                        {
                            changementJoueur(joueur);
                            multiple = 0;
                            etat = 0;
                            active = 0;

                            if(plateau_jeu[CursorXtemp][CursorYtemp].nom == pionActif.nom)
                            {
                                CursorX = CursorXtemp;
                                CursorY = CursorYtemp;
                                plateau_jeu[CursorXtemp][CursorYtemp].nb = plateau_jeu[CursorXtemp][CursorYtemp].nb + pionActif.nb;
                            }
                        }
                    break;
                }
                break;
            // [FIN] Gestion des événements clavier

            // [DEBUT] Gestion des evenements souris
            case SDL_MOUSEBUTTONDOWN:
                // Sélectionner un pion
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    etat = 0;
                    if(plateau_jeu[CursorX][CursorY].nom != 0 && plateau_jeu[CursorX][CursorY].nb != 0 && active == 0)
                    {
                        if(plateau_jeu[CursorX][CursorY].nom == 'C' && plateau_jeu[CursorX][CursorY].nb > 0 &&  *joueur == 1)
                        {
                            selectPion(plateau_jeu, &pionActif.nom , &pionActif.nb, &CursorXtemp, &CursorYtemp, CursorX, CursorY, &active);
                        }
                        else if(plateau_jeu[CursorX][CursorY].nom == 'T' && plateau_jeu[CursorX][CursorY].nb > 0 && *joueur == 2)
                        {
                            selectPion(plateau_jeu, &pionActif.nom , &pionActif.nb, &CursorXtemp, &CursorYtemp, CursorX, CursorY, &active);
                        }
                    }
                }
                // Valider le déplacement d'un pion
                if(event.button.button == SDL_BUTTON_MIDDLE)
                {
                    verifierDeplacement = verifDeplacement(plateau_jeu, CursorXtemp, CursorYtemp, CursorX, CursorY);
                    if(verifierDeplacement == 1 && multiple == 0 || verifierDeplacement == 2)
                    {
                        if(verifierDeplacement == 1 && pionActif.nom == 'C' && plateau_jeu[CursorX][CursorY].nom != 'T' && plateau_jeu[CursorX][CursorY].nom != 'C')
                        {
                            plateauDeplacement(plateau_jeu, CursorX, CursorY, pionActif.nom, pionActif.nb);
                            Deplacement = 1;
                            if(plateau_jeu[CursorXtemp][CursorYtemp].nb <= 0)
                            {
                                plateau_jeu[CursorXtemp][CursorYtemp].nom = 0;
                            }
                        }
                        else if(pionActif.nom == 'T' && plateau_jeu[CursorX][CursorY].nom != 'C' && plateau_jeu[CursorX][CursorY].nom != 'T')
                        {
                            if(verifierDeplacement == 2) // Saut
                            {
                                xC = calculMilieu(CursorXtemp, CursorYtemp, CursorX, CursorY, 'x');
                                yC = calculMilieu(CursorXtemp, CursorYtemp, CursorX, CursorY, 'y');

                                plateau_jeu[xC][yC].nb = plateau_jeu[xC][yC].nb - 1;
                                if(plateau_jeu[xC][yC].nb <= 0)
                                {
                                    plateauDeplacement(plateau_jeu, xC, yC, 0, 0);
                                }

                                multiple = 1; // Active la vérification du saut multiple
                            }

                            plateauDeplacement(plateau_jeu, CursorX, CursorY, pionActif.nom, pionActif.nb);
                            Deplacement = 1;
                            if(plateau_jeu[CursorXtemp][CursorYtemp].nb <= 0)
                            {
                                plateauDeplacement(plateau_jeu, CursorXtemp, CursorYtemp, 0, 0);
                            }
                        }
                        else
                        {
                            erreurValidation(plateau_jeu, pionActif.nom, pionActif.nb, CursorXtemp, CursorYtemp, &CursorX, &CursorY, &active, multiple, &etat, 1);
                        }
                    }
                    else
                    {
                        erreurValidation(plateau_jeu, pionActif.nom, pionActif.nb, CursorXtemp, CursorYtemp, &CursorX, &CursorY, &active, multiple, &etat, 1);
                    }
                }
                // Annuler la sélection d'un pion
                if(event.button.button == SDL_BUTTON_RIGHT && multiple == 0)
                {
                    erreurValidation(plateau_jeu, pionActif.nom, pionActif.nb, CursorXtemp, CursorYtemp, &CursorX, &CursorY, &active, multiple, &etat, 0);
                }
                // Déplacement fait & Gestion des variables pour les sauts multiples
                if(Deplacement == 1)
                {
                    active = 0;
                    Deplacement = 0;
                    CursorXtemp = CursorX;
                    CursorYtemp = CursorY;

                    // Saut multiple ?
                    if(plateau_jeu[CursorXtemp][CursorYtemp].nom == 'T' && verifSautMultiple(plateau_jeu, CursorXtemp, CursorYtemp, 0) == 1 && multiple == 1)
                    {
                        etat = 2;

                        if(plateau_jeu[xC][yC].nom == 'C' && plateau_jeu[xC][yC].nb >= 1)
                        {
                            changementJoueur(joueur);
                            etat = 0;
                            multiple = 0;
                        }
                        else
                        {
                            if(plateau_jeu[CursorX][CursorY].nom == 'C' && plateau_jeu[CursorX][CursorY].nb > 0 &&  *joueur == 1)
                            {
                                selectPion(plateau_jeu, &pionActif.nom , &pionActif.nb, &CursorXtemp, &CursorYtemp, CursorX, CursorY, &active);
                            }
                            else if(plateau_jeu[CursorX][CursorY].nom == 'T' && plateau_jeu[CursorX][CursorY].nb > 0 && *joueur == 2)
                            {
                                selectPion(plateau_jeu, &pionActif.nom , &pionActif.nb, &CursorXtemp, &CursorYtemp, CursorX, CursorY, &active);
                            }
                        }
                    }
                    else
                    {
                        changementJoueur(joueur);
                        etat = 0;
                        multiple = 0;
                    }
                }
                break;
            //[FIN] SOURIS
        }

        // Délimitation du cuseur
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

        // Position du curseur
        positionCursor.x = (RESOLUTION_X / 2) - (PLATEAU_X / 2) - (cursor->w / 2) + TAILLE_CASE * CursorX + 5;
        positionCursor.y = (RESOLUTION_Y / 2) - (PLATEAU_Y / 2) - (cursor->h / 2) + TAILLE_CASE * CursorY;

        // Effacement et affichage de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_BlitSurface(plateau, NULL, ecran, &positionPlateau);
        SDL_BlitSurface(cursor, NULL, ecran, &positionCursor);

        AffichePionsTotal(ecran, tigre, tigre_hover, tigre_active, chevre, chevre_hover, chevre_active, police3, texte, plateau_jeu, CursorX, CursorY, *joueur, pionActif, active);

        NbChevres = detectionChevres(plateau_jeu, active, *joueur); // Détermination du nombre de chèvres restant

        AfficheTour(ecran, police, police2, police4, *joueur, etat);
        AfficheChevresRestant(ecran, police, texte2, police2, texte3, NbChevres);
        SDL_Flip(ecran);

        if(continuer == 1)
        {
            fin = finPartie(plateau_jeu, active, *joueur);
        }
    } while(continuer == 1 && fin == 0);
/* ******************************************************************* */

    // [DEBUT] Données : Affichage de la fin de partie & du gagnant
    while(fin > 0)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_BlitSurface(plateau_fin, NULL, ecran, &positionPlateauFin);
        if(fin == 1)
        {
            AfficheTour(ecran, police, police2, police4, -1, 0);
            AfficheChevresRestant(ecran, police, texte2, police2, texte3, -2);
        }
        else
        {
            AfficheTour(ecran, police, police2, police4, -2, 0);
            AfficheChevresRestant(ecran, police, texte2, police2, texte3, -1);
        }
        SDL_Flip(ecran);

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                        continuer = 0;
                        fin = 0;
                    break;
                    case SDLK_ESCAPE:
                        fin = -1;
                    break;
                }
                break;
        }
    }
    // [FIN] Données : Affichage de la fin de partie & du gagnant

    // Fermeture des polices
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
    TTF_CloseFont(police3);
    TTF_CloseFont(police4);
    TTF_Quit();

    // Libération de la mémoire
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(plateau_fin);
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(tigre);
    SDL_FreeSurface(tigre_hover);
    SDL_FreeSurface(chevre);
    SDL_FreeSurface(chevre_hover);

    // [DEBUT] Données : Fin de partie - gestion du retour au menu
    if(fin > 0 || fin == -1)
    {
        continuer = 1;
    }

    *pCursorX = CursorX;
    *pCursorY = CursorY;
    // [FIN] Données : Fin de partie - gestion du retour au menu

    return continuer;
}
// [FIN] Données : Fonction principal du jeu
