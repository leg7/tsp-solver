#pragma once

#include <string>

#include "data.h"

// exporter meilleure tour dans un fichier .solution
void export_solution_header(solution s, std::string filename);
void export_solution_data(solution s, std::string filename);
void export_solution(solution s, std::string filename);

// fonctions pour exporter une solution dans un fichier .dat pour gnuplot
void make_gnuplot_datafile(std::string filename);
void append_progressive_iteration(iteration i, std::string filename);
void append_iteration(iteration i, std::string filename);
void build_gnuplot_datafile(solution s, std::string filename);
