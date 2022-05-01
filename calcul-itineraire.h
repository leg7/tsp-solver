#pragma once

struct destination
{
	unsigned int num; // Le numero de ville de la destination
	double  distance; // La distance pour aller à cette ville
};

destination get_destination(matrix &tsp, unsigned int line);

destination* glouton(matrix &tsp);
