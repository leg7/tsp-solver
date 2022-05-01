#include "import.h"
#include "matrix.h"
#include "calcul-itineraire.h"

#include <iostream>
#include <stdexcept>

bool is_valid_destination(matrix tsp, unsigned int i, unsigned int j)
{
	if (tsp.m[i][j].checked == false and
	    i < tsp.n and i >= 0)
		return true;
	else
		return false;
}

bool is_closest_destination(matrix tsp, unsigned int i, unsigned int j, destination d)
{
	return (tsp.m[i][j].distance < d.distance and
		is_valid_destination(tsp,i,j));

}

destination get_greedy_destination(matrix &tsp, unsigned int origin)
{
	if (origin >= tsp.n + 1 or origin < 0)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	destination d;
	d.distance = 1000000000;

	/* min line */

	/* k < taille de la ligne */
	for (unsigned int j = 0; j < tsp.n - origin; ++j)
	{
		if (is_closest_destination(tsp, origin, j, d))
		{
			d.distance = tsp.m[origin][j].distance;
			d.num      = origin + 1 + j;
		}
		tsp.m[origin][j].checked = true;
	}

	/* min diagonale */
	if (origin > 0)
	{
		unsigned int i = origin - 1;
		unsigned int j = 0;
		while (i > 0)
		{
			if (is_closest_destination(tsp, i, j, d))
			{
				d.distance = tsp.m[i][j].distance;
				d.num      = i;
			}
			tsp.m[i][j].checked = true;

			--i;
			++j;
		}
	}
	return d;
}

void make_greedy_itinerary(matrix &tsp, itinerary &it)
{
	init_matrix_status(tsp);

	for (unsigned int k = 1; k < it.size; ++k)
	{
		it.data[k] = get_greedy_destination(tsp, it.data[k-1].num);
		it.length += it.data[k].distance;
		print_matrix_status(tsp);
		/* std::cout << t[i] << std::endl << std::endl; */
	}
}
