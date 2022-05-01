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

/* testé ok */
double get_distance(matrix tsp, unsigned int a, unsigned int b)
{
	if (a >= tsp.n + 1 or a < 0 or
	    b >= tsp.n + 1 or b < 0)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	if (b == a)
		return 0;

	if (b < a)
	{
		double temp = b;
		b = a;
		a = temp;
	}
	return tsp.m[a][b-a-1].distance;
}

void mark_visited(matrix &tsp, unsigned int town)
{
	if (town >= tsp.n + 1 or town < 0)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	for (unsigned int j = 0; j < tsp.n - town; ++j)
		tsp.m[town][j].checked = true;

	/* min diagonale */
	if (town > 0)
	{
		unsigned int i = town - 1;
		unsigned int j = 0;
		while (i > 0)
		{
			tsp.m[i][j].checked = true;
			--i;
			++j;
		}
	}
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

			--i;
			++j;
		}
	}

	mark_visited(tsp,origin);
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
