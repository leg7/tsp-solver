#include "data.h"

bool test_tour_data(tour t);

// test d'export du fichier .solution
bool test_export_solution_header(std::string filename);
bool test_export_solution(solution s, std::string filename);

// tests d'heuristiques genetique
bool test_make_random_tour(matrix tsp);
bool test_generation_data(generation g);
bool test_generation_lengths(generation g, matrix tsp);
bool test_make_random_generation(matrix tsp);
bool generation_is_sorted(generation g);
bool test_sort_generation(matrix tsp);
