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
	point   coord;      // coordonnées du point
	double  distance;   // La distance pour aller à cette ville
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

/* liste chaînée qui represente la solution au tsp, utile pour gnuplot */
using solution = iteration*;

void init_tour(tour &t, size_t start, std::string instance);
void update_tour_distances(tour &t, matrix tsp);
void update_tour_length(tour &t, matrix tsp);
void update_tour(tour &t, matrix tsp, std::string instance);
void print_tour(tour t);

void insert_to_solution(solution &s, tour t);
void append_to_solution(solution &s, tour t);
void print_solution_result(solution s);

void make_gnuplot_datafile(std::string filename);
void append_progressive_iteration(iteration i, std::string filename);
void append_iteration(iteration i, std::string filename);
void build_gnuplot_datafile(solution s, std::string filename);
