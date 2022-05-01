#include "import.h"
#include "calcul-itineraire.h"
#include <iostream>

destination get_destination(matrix &tsp, unsigned int line)
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

destination* glouton(matrix &tsp)
{
	destination *t = new destination[tsp.n];
	t[0].distance = 0;
	t[0].num      = 0;

	for (unsigned int i = 1; i < tsp.n; ++i)
	{
		t[i] = get_destination(tsp,t[i-1].num);
		/* print_matrix(tsp); */
		/* std::cout << t[i] << std::endl << std::endl; */
	}
	return t;
}
