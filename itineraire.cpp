#include "matrix.h"
#include "import.h"
#include "itineraire.h"
#include "calcul-itineraire.h"

#include <fstream>
#include <iostream>

void init_itinerary(itinerary &it, size_t start, std::string instance)
{
	it.length = 0;

	/* + 1 parcequ'il faut revenir au point de depart */
	it.size = get_tsp_size(instance) + 1;

	it.data = new destination[it.size];
	it.data[0].distance = 0;
	it.data[0].id       = start;
}

void update_itinerary(matrix tsp, itinerary &it)
{
	it.data[0].distance = 0;
	for (size_t k = 1; k < it.size; ++k)
		it.data[k].distance = get_distance(tsp, it.data[k-1].id , it.data[k].id);

	it.length = 0;
	for (size_t k = 0; k < it.size; ++k)
		it.length += it.data[k].distance;
}

void print_itinerary(itinerary it)
{
	std::cout << "L'itineraire serait d'une longueur de " << it.length
		<< " : \n\n";

	for (size_t k = 0; k < it.size; ++k)
		std::cout << "\t" << it.data[k].id + 1 << std::endl;

	std::cout << std::endl;
}

void export_itinerary(itinerary it, std::string filename)
{
	std::ofstream file(filename+".dat");
	if (file.good())
	{
		for (size_t j = 1; j < it.size; ++j)
		{
			for (size_t k = 0; k < j; ++k)
			{
				file << it.data[k].coord.x
					<< ' '
					<< it.data[k].coord.y
					<< ' '
					<< it.data[k].id + 1
					<< std::endl;
			}
			file << std::endl << std::endl;
		}
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

void export_append_itinerary(itinerary it, std::string filename)
{
	std::ofstream file(filename+".dat", std::ios::app);
	if (file.good())
	{
		file << std::endl << std::endl;
		for (size_t k = 0; k < it.size; ++k)
		{
			file << it.data[k].coord.x
				<< ' '
				<< it.data[k].coord.y
				<< ' '
				<< it.data[k].id + 1
				<< std::endl;
		}
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}
