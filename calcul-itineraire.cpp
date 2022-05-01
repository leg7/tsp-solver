#include "import.h"
#include "calcul-itineraire.h"
#include <iostream>

destination get_greedy_destination(matrix &tsp, unsigned int line)
{
	destination d;
	d.distance = 10000000000;

	/* min line */
	if (line != tsp.n - 1)
	{
		/* k < taille de la ligne */
		for (unsigned int k = 0; k < tsp.n - 1 - line; ++k)
		{
			if (tsp.m[line][k] < d.distance and tsp.m[line][k] != 0)
			{
				d.distance = tsp.m[line][k];
				d.num      = line + k + 1;
			}
			tsp.m[line][k] = 0;
		}
	}

	/* min diagonale */
	if (line != 0)
	{
		unsigned int i = line - 1;
		unsigned int j = 0;
		while (i != 0)
		{
			if (tsp.m[i][j] < d.distance and tsp.m[i][j] != 0)
			{
				d.distance = tsp.m[i][j];
				d.num      = i;
			}
			tsp.m[i][j] = 0;

			--i;
			++j;
		}
	}

	return d;
}

void glouton(matrix &tsp, itinerary &it)
{

	it.length = 0;

	it.data = new destination[tsp.n];
	it.data[0].distance = 0;
	it.data[0].num      = 0;

	for (unsigned int k = 1; k < tsp.n; ++k)
	{
		it.data[k] = get_greedy_destination(tsp, it.data[k-1].num);
		it.length += it.data[k].distance;
		/* print_matrix(tsp); */
		/* std::cout << t[i] << std::endl << std::endl; */
	}
}
