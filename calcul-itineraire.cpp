#include "import.h"
#include "calcul-itineraire.h"
#include <iostream>

unsigned int get_min_and_zero(matrix &tsp, unsigned int line)
{
	unsigned int destination = 1000000;
	unsigned int distance = 1000000;

	/* min line */
	if (line != tsp.n - 1)
	{
		// k < taille de la ligne
		for (unsigned int k = 0; k < tsp.n - 1 - line; ++k)
		{
			if (tsp.m[line][k] < distance and tsp.m[line][k] != 0)
			{
				distance = tsp.m[line][k];
				destination = line + k + 1;
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
			if (tsp.m[i][j] < distance and tsp.m[i][j] != 0)
			{
				distance = tsp.m[i][j];
				destination = i;
			}
			tsp.m[i][j] = 0;

			--i;
			++j;
		}
	}

	return destination;
}

unsigned int* glouton(matrix &tsp)
{
	unsigned int *t = new unsigned int[tsp.n];
	t[0] = 0;

	for (unsigned int i = 1; i < tsp.n; ++i)
	{
		t[i] = get_min_and_zero(tsp,t[i-1]);
		/* print_matrix(tsp); */
		/* std::cout << t[i] << std::endl << std::endl; */
	}
	return t;
}
