#include "import.h"
#include "calcul-itineraire.h"
#include <iostream>

void init_matrix_status(matrix &tsp)
{
	unsigned int x = tsp.n - 1;
	for (unsigned int i = 0; i < tsp.n; ++i)
	{
		for (unsigned int j = 0; j < x; ++j)
			tsp.m[i][j].checked = false;
		--x;
	}
}

void print_matrix_status(matrix &tsp)
{
	unsigned int x = tsp.n - 1;
	for (unsigned int i = 0; i < tsp.n; ++i)
	{
		for (unsigned int j = 0; j < x; ++j)
			std::cout << tsp.m[i][j].checked << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool is_closest_destination(matrix &tsp, unsigned int i, unsigned int j, destination d)
{
	return (tsp.m[i][j].distance < d.distance and
		tsp.m[i][j].checked == false);
}

destination get_greedy_destination(matrix &tsp, unsigned int origin)
{
	destination d;
	d.distance = 10000000000;

	/* min line */
	if (origin != tsp.n - 1)
	{
		/* k < taille de la ligne */
		for (unsigned int j = 0; j < tsp.n - 1 - origin; ++j)
		{
			if (is_closest_destination(tsp, origin, j, d))
			{
				d.distance = tsp.m[origin][j].distance;
				d.num      = origin + 1 + j;
			}
			tsp.m[origin][j].checked = true;
		}
	}

	/* min diagonale */
	if (origin != 0)
	{
		unsigned int i = origin - 1;
		unsigned int j = 0;
		while (i != 0)
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

	it.length = 0;

	it.data = new destination[tsp.n];
	it.data[0].distance = 0;
	it.data[0].num      = 0;

	for (unsigned int k = 1; k < tsp.n; ++k)
	{
		it.data[k] = get_greedy_destination(tsp, it.data[k-1].num);
		it.length += it.data[k].distance;
		print_matrix_status(tsp);
		/* std::cout << t[i] << std::endl << std::endl; */
	}
}
