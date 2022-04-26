#include <string>
#include <fsteam>

struct point
{
	unsigned int x;
	unsigned int y;
};

/*
 * Cette fonction retourne la distance entre deux points @a et @b
 * Elle sert a creer une matrice d'adjacence si l'instance passé en paramètre
 * n'en possède deja pas une
 */
double distance(point a, point b);

/*
 * Cette procedure construit rempli une matrice d'adjacence
 * dynamique avec la fonction distance
 */
void import_fic_cord(double **t, std::string file);


/*
 * Cette procedure rempli une matrice d'adjacence dynamique avec les données
 * fouries par l'instance à resoudre
 */
void import_fic_matrice(double **t, std::string file);

/*
 * Cette procedure determine quelle type d'instance est passé en paramètre
 * Soit une instance avec une matrice d'adjacence déja fournie ou une
 * instance de coordonées pour ensuite appeler la fonction d'import aproprié
 */
void import(std::string file);
