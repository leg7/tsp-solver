#include "matrix.h"
#include "import.h"

#include <iostream>
#include <string>

/* testé ok */
void build_matrix(matrix &tsp, std::string filename)
{
	tsp.n = get_tsp_size(filename);

	--tsp.n;

	if (tsp.n > 0)
	{
		tsp.m = new matrix_data*[tsp.n];

		unsigned int x = tsp.n;
		for (unsigned int i = 0; i < tsp.n; ++i)
		{
			tsp.m[i] = new matrix_data[x];
			--x;
		}
	}
	else
		std::cout << "Erreur critique : la taille de votre instance "
			<< "est <= 0 donc la matrice n'as pas été faite.\n";
}

void init_matrix_status(matrix &tsp)
{
	unsigned int x = tsp.n;
	for (unsigned int i = 0; i < tsp.n; ++i)
	{
		for (unsigned int j = 0; j < x; ++j)
			tsp.m[i][j].checked = false;
		--x;
	}
}

void print_matrix_status(matrix &tsp)
{
	unsigned int x = tsp.n;
	for (unsigned int i = 0; i < tsp.n; ++i)
	{
		for (unsigned int j = 0; j < x; ++j)
			std::cout << tsp.m[i][j].checked << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/* testé ok */
void print_matrix_distance(matrix tsp)
{
	unsigned int x = tsp.n;
	for (unsigned int i = 0; i < tsp.n; ++i)
	{
		for (unsigned int j = 0; j < x;  ++j)
			std::cout << tsp.m[i][j].distance << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void delete_matrix(matrix &tsp)
{
	for (unsigned int i = 0; i < tsp.n; ++i)
		delete[] tsp.m[i];
	delete[] tsp.m;
}
