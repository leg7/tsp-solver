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

void build_matrix(matrix &tsp, std::string filename);
void init_matrix_status(matrix &tsp);

void print_matrix_status(matrix &tsp);
void print_matrix_distance(matrix tsp);

void delete_matrix(matrix &tsp);
