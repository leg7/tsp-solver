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

/*
 * Cette fonction retourne la destination la plus proche de la ville passé en
 * paramètre @line dans la matrice d'adjacence @tsp. De plus chaque possibilité
 * de la ville est mise a zero pour ne pas pouvoir revenir à cette ville
 * Cette fonction sert a calculer un itineraire de façon gloutonne
 */
destination get_destination(matrix &tsp, unsigned int line);

/*
 * Cette procedure calcule un itineraire de manière gloutonne grâce a la
 * fonction get_destination()
 * L'itineraire @it est calcule à partir d'une matrice d'adjacence @tsp
 */
void glouton(matrix &tsp, itinerary &it);
