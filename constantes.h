#define RESOLUTION_X 640
#define RESOLUTION_Y 640
#define PLATEAU_X    407
#define PLATEAU_Y    340
#define TAILLE_CASE  100

void EcricreTexte(SDL_Surface *ecran, TTF_Font *police, char txt[20], int positionX, int positionY);

int aide(SDL_Surface *ecran, SDL_Surface *fond, SDL_Rect positionFond, int continuer);
