#include "matrix.h"
#include "import.h"
#include "tour.h"
#include "calcul-tour.h"

#include <fstream>
#include <iostream>

void init_tour(tour &t, size_t start, std::string instance)
{
	t.length = 0;

	/* + 1 parcequ'il faut revenir au point de depart */
	t.size = get_tsp_size(instance) + 1;

	t.data = new destination[t.size];
	t.data[0].distance = 0;
	t.data[0].id       = start;
}

void update_tour(matrix tsp, tour &t)
{
	t.data[0].distance = 0;
	for (size_t k = 1; k < t.size; ++k)
		t.data[k].distance = get_distance(tsp, t.data[k-1].id , t.data[k].id);

	t.length = 0;
	for (size_t k = 0; k < t.size; ++k)
		t.length += t.data[k].distance;
}

void print_tour(tour t)
{
	std::cout << "Le tour serait d'une longueur de " << t.length
		<< " : \n\n";

	for (size_t k = 0; k < t.size; ++k)
		std::cout << "\t" << t.data[k].id + 1 << std::endl;

	std::cout << std::endl;
}

void export_tour(tour t, std::string filename)
{
	std::ofstream file(filename+".dat");
	if (file.good())
	{
		for (size_t j = 1; j < t.size; ++j)
		{
			for (size_t k = 0; k < j; ++k)
			{
				file << t.data[k].coord.x
					<< ' '
					<< t.data[k].coord.y
					<< ' '
					<< t.data[k].id + 1
					<< std::endl;
			}
			file << std::endl << std::endl;
		}
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

void export_append_tour(tour t, std::string filename)
{
	std::ofstream file(filename+".dat", std::ios::app);
	if (file.good())
	{
		file << std::endl << std::endl;
		for (size_t k = 0; k < t.size; ++k)
		{
			file << t.data[k].coord.x
				<< ' '
				<< t.data[k].coord.y
				<< ' '
				<< t.data[k].id + 1
				<< std::endl;
		}
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}
