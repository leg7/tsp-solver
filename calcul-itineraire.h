#pragma once

#include "matrix.h"
#include "import.h"

struct point
{
	double x,
	       y;
};

struct destination
{
	size_t  id;         // Le numero de ville de la destination
	point   coord;      // coordonnées du point
	double  distance;   // La distance pour aller à cette ville
};

struct itinerary
{
	destination *data;  // Un tableau de destination (e.g un itineraire)
	size_t      size;   // Le nombre de destinations de l'itineraire
	double      length; // La longeure de l'itineraire
};

/* echange a et b */
void swap(auto &a, auto &b);

/*
 * Fonction qui trouve et renvoie la distance entre deux villes @start et @end
 * dans la matrice d'adjacence.
 * Cette fonction sert a determiner si un opt-swap est judicieux et calculer
 * la longeure d'un itineraire.
 */
double get_distance(matrix tsp, size_t start, size_t end);

/*
 * Fonction qui verifie si la trajet depuis la ville @start vers @end
 * est possible. Utilisé pour construire une solution sans repasser par
 * une ville plus d'une fois.
 */
bool is_valid_path(matrix tsp, size_t start, size_t end);

/*
 * Cette fonction retourne la destination la plus proche de la ville passé en
 * paramètre @line dans la matrice d'adjacence @tsp. De plus les status
 * des points de la destination trouvés sont mis a jour pour ne pas revenir
 * sur ceux-cis plus tard.
 */
destination get_greedy_destination(matrix &tsp, size_t start);

/*
 * Marque une ville comme visité dans la matrice d'adjacence @tsp pour ne
 * pas repasser par cette ville ulterieurement
 */
void mark_visited(matrix &tsp, size_t city);

/*
 * Cette procedure calcule un itineraire de manière gloutonne grâce a la
 * fonction get_greedy_destination()
 * L'itineraire @it est calcule à partir d'une matrice d'adjacence @tsp
 */
void make_greedy_itinerary(matrix &tsp, itinerary &it);

/* Procedure qui mets a jour la distance totale d'un itineraire */
void update_itinerary(matrix tsp, itinerary &it);

 /* Fonction qui retourne un itineraire optimisé par un échange 2-opt */
itinerary two_opt_swap(matrix tsp, itinerary it, size_t a, size_t b);

/* optimize un itineraire au maximum avec des echanges 2-opt */
void two_opt_optimize(matrix tsp, itinerary &it);
