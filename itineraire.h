#pragma once

# include <string>

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

void init_itinerary(itinerary &it, size_t start, std::string instance);

/* Procedure qui mets a jour la distance totale d'un itineraire */
void update_itinerary(matrix tsp, itinerary &it);

void print_itinerary(itinerary it);

void export_itinerary(itinerary it, std::string filename);

void export_append_itinerary(itinerary it, std::string filename);
