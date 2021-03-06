#pragma once

#include "data.h"

// compteur d'echanges opt
extern size_t OPT_SWAPS;

// algo glouton
destination get_greedy_destination(matrix &tsp, size_t start);
void make_greedy_tour(tour &t, matrix &tsp, std::string instance);
void find_greedy_solution(solution &s, matrix &tsp, std::string instance);

// optimizations
tour two_opt_swap(tour t, matrix tsp, size_t a, size_t b);
void two_opt_optimize(tour &t, matrix tsp, std::string instance);
void find_greedy_optimized_solution(solution &s, matrix &tsp, std::string instance);

// recuit simulé
bool should_make_random_swap(int ti, int t);
size_t pick_random_neighbor(size_t a, tour t);
void swap_random_neighbors(tour &t);
void simmulated_annealing(solution &s, matrix &tsp, std::string instance);
void find_simmulated_annealing_solution(solution &s, matrix &tsp, std::string instance);

// algo genetique
tour make_random_tour(matrix tsp);
void make_random_generation(generation &g, size_t size, matrix tsp);
int lomuto_partition(generation &g, int start, int end);
void sort_generation(generation &g, int start, int end);
void sort_generation(generation &g);
