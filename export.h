#pragma once

#include <string>

#include "tour.h"

/* fonctions pour exporter une solution dans un fichier .dat pour gnuplot */
void make_gnuplot_datafile(std::string filename);
void append_progressive_iteration(iteration i, std::string filename);
void append_iteration(iteration i, std::string filename);
void build_gnuplot_datafile(solution s, std::string filename);
