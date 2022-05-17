#pragma once

#include <fstream>
#include <string>

#include "data.h"

/* trouve la taille du tsp (nombre de villes) */
size_t get_tsp_size(std::string filename);

/* operations sur fichiers tsplib */
std::ifstream go_to_target(std::string filename, std::string target, size_t n);
bool find_target(std::string filename, std::string target);

/* import des données tsplib dans la matrice d'adjacence */
double distance(point a, point b);
void import_tsp_cord(matrix &tsp, std::string filename);
void import_tsp_matrix(matrix &tsp, std::string filename);
void import_tsp(matrix &tsp, std::string filename);

/* import des données tsplib dans un tour */
void import_destination_coord(destination &d, std::string target, std::string filename);
void import_tour_coord(tour &t, std::string instance);
