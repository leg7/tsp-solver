#pragma once

#include "matrix.h"
#include "import.h"

struct point
{
	double x;
	double y;
};

struct destination
{
	unsigned int num; // Le numero de ville de la destination
	point p; // coordonnées du point
	double  distance; // La distance pour aller à cette ville
};

struct itinerary
{
	destination *data;  // Un tableau de destination (e.g un itineraire)
	unsigned int size;  // Le nombre de destinations de l'itineraire
	double length;      // La longeure de l'itineraire
};

/*
 * Verifie si le coordonnées @i et @j dans la matrice @tsp
 * donc tsp[i][j] appartient bien à la matrice pour eviter
 * de l'undefined behaviour
 */
bool is_valid_destination(matrix tsp, unsigned int i, unsigned int j);

/*
 * Fonction qui renvoie si @tsp.m[i][j] est
 * la prochaine destination valide la plus proche
 */
bool is_closest_destination(matrix tsp, unsigned int i, unsigned int j, destination d);

/*
 * Fonction qui trouve et renvoie la distance entre deux villes @a et @b
 * dans la matrice d'adjacence.
 * Cette fonction sert a determiner si un opt-swap est judicieux
 */
double get_distance(matrix tsp, unsigned int a, unsigned int b);

/*
 * Marque une ville comme visité dans la matrice d'adjacence
 */
void mark_visited(matrix &tsp, unsigned int town);

/*
 * Cette fonction retourne la destination la plus proche de la ville passé en
 * paramètre @line dans la matrice d'adjacence @tsp. De plus les status
 * des points de la destination trouvés sont mis a jour pour ne pas revenir
 * sur ceux-cis plus tard.
 */
destination get_greedy_destination(matrix &tsp, unsigned int line);

/*
 * Cette procedure calcule un itineraire de manière gloutonne grâce a la
 * fonction get_greedy_destination()
 * L'itineraire @it est calcule à partir d'une matrice d'adjacence @tsp
 */
void make_greedy_itinerary(matrix &tsp, itinerary &it);
