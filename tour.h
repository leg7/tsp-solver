#pragma once

#include <string>

#include "matrix.h"

struct point
{
	double x,
	       y;
};

struct destination
{
	size_t  id;         // Le numero de ville de la destination
	double  distance;   // La distance pour aller à cette ville
	point   coord;      // coordonnées du point (pour l'export gnuplot)
};

struct tour
{
	destination *data;  // Un tableau de destination (e.g un tour)
	size_t      size;   // Le nombre de destinations du tour
	double      length; // La longeur du tour
};

/* Maillon qui contient une iteration de la solution trouvé au tsp */
struct iteration
{
	tour t;
	iteration *next;
};

/* liste chaînée qui represente la solution du tsp, utile pour gnuplot */
using solution = iteration*;

/* manipulation d'un tour */
void init_tour(tour &t, size_t start, std::string instance);
void update_tour_distances(tour &t, matrix tsp);
void update_tour_length(tour &t, matrix tsp);
void update_tour(tour &t, matrix tsp, std::string instance);
void print_tour(tour t);

/* manipulation d'une solution */
void insert_tour_to_solution_head(tour t, solution &s);
void insert_tour_to_solution_tail(tour t, solution &s);
void print_solution_result(solution s);
