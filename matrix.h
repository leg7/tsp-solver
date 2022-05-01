#pragma once

#include <string>

struct matrix_data
{
	double distance; // La distance
	bool    checked; // Si le point à été traité
};

struct matrix
{
	matrix_data **m;
	unsigned int  n;
};

/* Procedure qui initialise le status de la matrice */
void init_matrix_status(matrix &tsp);

/* Procedure qui affiche le status de la matrice */
void print_matrix_status(matrix &tsp);

/*
 * Procedure qui construit une matrice d'adjacence vide passé en paramètere
 * (@tsp). Cette fonction determine le taille de la matrice grâce a la fonction
 * get_tsp_size ci dessus.
 */
void build_matrix(matrix &tsp, std::string filename);

/* Procedure qui affiche une matrice d'adjacence @tsp */
void print_matrix_distance(matrix tsp);

/* desalloue une matrice dynamique */
void delete_matrix(matrix &tsp);
