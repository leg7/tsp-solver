#pragma once

#include "matrix.h"
#include "import.h"
#include "tour.h"

extern size_t OPT_SWAPS;

/* echange a et b */
void swap(auto &a, auto &b);

/*
 * Fonction qui trouve et renvoie la distance entre deux villes @start et @end
 * dans la matrice d'adjacence.
 * Cette fonction sert a determiner si un opt-swap est judicieux et calculer
 * la longeure d'un tour.
 */
double get_distance(matrix tsp, size_t start, size_t end);

/*
 * Fonction qui verifie si la trajet depuis la ville @start vers @end
 * est possible. Utilisé pour construire une solution sans repasser par
 * une ville plus d'une fois.
 */
bool is_valid_path(matrix tsp, size_t start, size_t end);

/*
 * Marque une ville comme visité dans la matrice d'adjacence @tsp pour ne
 * pas repasser par cette ville ulterieurement
 */
void mark_visited(matrix &tsp, size_t city);

/*
 * Cette fonction retourne la destination la plus proche de la ville passé en
 * paramètre @line dans la matrice d'adjacence @tsp. De plus les status
 * des points de la destination trouvés sont mis a jour pour ne pas revenir
 * sur ceux-cis plus tard.
 */
destination get_greedy_destination(matrix &tsp, size_t start);

/*
 * Cette procedure calcule un tour de manière gloutonne grâce a la
 * fonction get_greedy_destination()
 * L'tour @t est calcule à partir d'une matrice d'adjacence @tsp
 */
void make_greedy_tour(tour &t, matrix &tsp, std::string instance);
void find_greedy_solution(solution &s, matrix &tsp, std::string instance);

 /* Fonction qui retourne un tour optimisé par un échange 2-opt */
tour two_opt_swap(tour t, matrix tsp, size_t a, size_t b);
/* optimize un tour au maximum avec des echanges 2-opt */
void two_opt_optimize(tour &t, matrix tsp, std::string instance);

void find_greedy_optimized_solution(solution &s, matrix &tsp, std::string instance);
