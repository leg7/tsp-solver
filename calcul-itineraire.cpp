#include "import.h"
#include "calcul-itineraire.h"

unsigned int get_min_and_zero(matrix &tsp, unsigned int line)
{
	unsigned int lmin = 1000000;
	unsigned int min = 1000000;

	/* init */
	unsigned int i = line;
	unsigned int j = 0;
	if (tsp.m[i][j] != 0)
	{
		min = tsp.m[i][j];
		lmin = line + 1;
		tsp.m[i][j] = 0;
		--i;
	}
	else
		--i;

	/* min diagonale */
	while (true and line != 0)
	{
		if (tsp.m[i][j] < min and tsp.m[i][j] != 0)
		{
			min = tsp.m[i][j];
			lmin = i;
		}
		tsp.m[i][j] = 0;

		if (i == 0)
			break;
		else
		{
			--i;
			++j;
		}
	}

	/* min line (et donc du tout) */
	for (unsigned int z = 1; z < tsp.n - 1 - line; ++z)
	{
		if (tsp.m[line][z] < min and tsp.m[line][z] != 0)
		{
			min = tsp.m[line][z];
			lmin = line + z + 1;
		}
		tsp.m[line][z] = 0;
	}

	return lmin;
}

unsigned int* glouton(matrix &tsp)
{
	unsigned int *t = new unsigned int[tsp.n];
	t[0] = 0;

	for (unsigned int i = 1; i < tsp.n - 1; ++i)
	{
		t[i] = get_min_and_zero(tsp,t[i-1]);
	}
	return t;
}
