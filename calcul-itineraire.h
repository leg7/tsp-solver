#pragma once

struct destination
{
	unsigned int num; // Le numero de ville de la destination
	double  distance; // La distance pour aller à cette ville
};

struct itinerary
{
	destination *data; // Un tableau de destination (e.g un itineraire)
	double length; // La longeure de l'itineraire
};

destination get_destination(matrix &tsp, unsigned int line);

void glouton(matrix &tsp, itinerary &i);
