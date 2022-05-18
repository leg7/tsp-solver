#pragma once

#include "data.h"

/* compteur d'echanges opt */
extern size_t OPT_SWAPS;

/* operations elementaires necessaires pour "resoudre" le tsp */
void swap(auto &a, auto &b);
size_t get_distance(matrix tsp, size_t start, size_t end);
void mark_visited(matrix &tsp, size_t city);
bool is_valid_path(matrix tsp, size_t start, size_t end);

/* algo glouton */
destination get_greedy_destination(matrix &tsp, size_t start);
void make_greedy_tour(tour &t, matrix &tsp, std::string instance);
void find_greedy_solution(solution &s, matrix &tsp, std::string instance);

/* optimizations */
tour two_opt_swap(tour t, matrix tsp, size_t a, size_t b);
void two_opt_optimize(tour &t, matrix tsp, std::string instance);
void find_greedy_optimized_solution(solution &s, matrix &tsp, std::string instance);

/* recuit simulé */
bool should_make_random_swap(int ti, int t);
size_t pick_random_neighbor(size_t a, tour t);
void swap_random_neighbors(tour &t);
void simmulated_annealing(solution &s, matrix &tsp, std::string instance);
