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

struct tour
{
	destination *data;  // Un tableau de destination (e.g un tour)
	size_t      size;   // Le nombre de destinations du tour
	double      length; // La longeure du tour
};

void init_tour(tour &t, size_t start, std::string instance);

/* Procedure qui mets a jour la distance totale d'un tour */
void update_tour(matrix tsp, tour &t);

void print_tour(tour t);

void export_tour(tour t, std::string filename);

void export_append_tour(tour t, std::string filename);
