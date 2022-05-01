#include "import.h"
#include "calcul-itineraire.h"
#include <iostream>

unsigned int get_min_and_zero(matrix &tsp, unsigned int line)
{
	unsigned int lmin = 1000000;
	unsigned int min = 1000000;

	bool exception = false;
	if (line == tsp.n - 1)
		exception = true;

	/* init */
	unsigned int i = line;
	unsigned int j = 0;

	if (tsp.m[i][j] != 0 and not exception)
	{
		min = tsp.m[i][j];
		lmin = line + 1;
		tsp.m[i][j] = 0;
	}
	--i;


	/* min diagonale */
	if (line != 0)
	{
		while (i != 0)
		{
			if (tsp.m[i][j] < min and tsp.m[i][j] != 0)
			{
				min = tsp.m[i][j];
				lmin = i;
			}
			tsp.m[i][j] = 0;

			--i;
			++j;
		}
	}

		/* min line (et donc du tout) */
	unsigned int k = 1;
	while (k < tsp.n - 1 - line and not exception)
	{
		if (tsp.m[line][k] < min and tsp.m[line][k] != 0)
		{
			min = tsp.m[line][k];
			lmin = line + k + 1;
		}
		tsp.m[line][k] = 0;
		++k;
	}

	return lmin;
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
