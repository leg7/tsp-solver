#pragma once

struct destination
{
	unsigned int num; // Le numero de ville de la destination
	double  distance; // La distance pour aller à cette ville
};

struct itinerary
{
	destination *data;  // Un tableau de destination (e.g un itineraire)
	double length;      // La longeure de l'itineraire
};

/* Procedure qui initialise le status de la matrice */
void init_matrix_status(matrix &tsp);

/* Procedure qui affiche le status de la matrice */
void print_matrix_status(matrix &tsp);

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
