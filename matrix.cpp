#include "matrix.h"
#include "import.h"

#include <iostream>
#include <string>

/* testé ok */
void build_matrix(matrix &tsp, std::string filename)
{
	tsp.size = get_tsp_size(filename);

	--tsp.size;

	if (tsp.size > 0)
	{
		tsp.data = new matrix_data*[tsp.size];

		size_t x = tsp.size;
		for (size_t i = 0; i < tsp.size; ++i)
		{
			tsp.data[i] = new matrix_data[x];
			--x;
		}
	}
	else
		std::cout << "Erreur critique : la taille de votre instance "
			<< "est <= 0 donc la matrice n'as pas été faite.\n";
}

void init_matrix_status(matrix &tsp)
{
	size_t x = tsp.size;
	for (size_t i = 0; i < tsp.size; ++i)
	{
		for (size_t j = 0; j < x; ++j)
			tsp.data[i][j].visited = false;
		--x;
	}
}

void print_matrix_status(matrix &tsp)
{
	size_t x = tsp.size;
	for (size_t i = 0; i < tsp.size; ++i)
	{
		for (size_t j = 0; j < x; ++j)
			std::cout << tsp.data[i][j].visited << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/* testé ok */
void print_matrix_distance(matrix tsp)
{
	size_t x = tsp.size;
	for (size_t i = 0; i < tsp.size; ++i)
	{
		for (size_t j = 0; j < x;  ++j)
			std::cout << tsp.data[i][j].distance << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void delete_matrix(matrix &tsp)
{
	for (size_t i = 0; i < tsp.size; ++i)
		delete[] tsp.data[i];
	delete[] tsp.data;
}
