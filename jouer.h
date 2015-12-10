typedef struct s_plateau
{
    char nom;
    int nb;
} t_plateau;

void AffichePion(SDL_Surface *pion, SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int, int, char, int);

void initPlateau(t_plateau plateau_jeu[5][5]);

void AfficheTour(SDL_Surface *ecran, TTF_Font *police, TTF_Font *police2, TTF_Font *police3, int, int);

void AfficheChevresRestant(SDL_Surface *ecran, TTF_Font *police, SDL_Surface *texte, TTF_Font *police2, SDL_Surface *texte2, int);

int detectionChevres(t_plateau plateau_jeu[5][5], int, int);

void AffichePionsTotal(SDL_Surface *ecran, SDL_Surface *tigre, SDL_Surface *tigre_hover, SDL_Surface *tigre_active,
SDL_Surface *chevre, SDL_Surface *chevre_hover, SDL_Surface *chevre_active,
TTF_Font *police, SDL_Surface *texte, t_plateau plateau_jeu[5][5], int, int, int, t_plateau pionActif, int);

int verifCoordonnees(t_plateau plateau_jeu[5][5], int, int, int, int);

int calculMilieu(int, int, int, int, char);

int verifDeplacement(t_plateau plateau_jeu[5][5], int, int, int, int);

int verifSautMultiple(t_plateau plateau_jeu[5][5], int, int, int);

void changementJoueur(int *);

void plateauDeplacement(t_plateau plateau_jeu[5][5], int, int, char, int);

void selectPion (t_plateau plateau_jeu[5][5], char *PionActifNom, int *PionActifNb, int *CursorXtemp, int *CursorYtemp, int, int, int *active);

int finPartie(t_plateau plateau_jeu[5][5], int, int);

int jouer(SDL_Surface *ecran, SDL_Surface *fond, SDL_Rect positionFond, t_plateau plateau_jeu[5][5], int *, int *, int *);
