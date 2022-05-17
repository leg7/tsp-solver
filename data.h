#pragma once

#include <string>


struct matrix_data
{
	double distance;        // La distance
	bool   visited;         // Si la ville à été visité
};

/* Ceci est une matrice d'adjacence utilisé pour "resoudre" l'instance tsp */
struct matrix
{
	matrix_data **data;
	size_t      size;
};

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

struct iteration
{
	tour t;
	iteration *next;
};
using solution = iteration*;

/* manipulation de matrice d'adjacence */
void init_matrix_size(matrix &tsp, std::string filename);
void build_matrix(matrix &tsp, std::string filename);
void init_matrix_status(matrix &tsp);
void print_matrix_status(matrix &tsp);
void print_matrix_distance(matrix tsp);
void delete_matrix(matrix &tsp);

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
