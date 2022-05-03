/* Ce fichier est une boucle main temporaire pour permettre de complier le code */
#include "matrix.h"
#include "import.h"
#include "calcul-itineraire.h"

#include <iostream>
#include <fstream>

void init_itinerary(itinerary &it, std::string instance)
{
	it.length = 0;

	it.size = get_tsp_size(instance);

	it.data = new destination[it.size];
	it.data[0].distance = 0;
	it.data[0].id      = 0;
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
	std::ofstream file(filename+".out");
	if (file.good())
	{
		for (size_t w = 0; w < it.size; ++w)
		{
			file << it.data[w].coord.x;
			file << ' ';
			file << it.data[w].coord.y;
			file << std::endl;
		}
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

int main()
{
	std::string instance = "tsp/att48.tsp";
	/* std::string instance = "tsp/bayg29.tsp"; */

	matrix tsp;
	build_matrix(tsp, instance);
	import_tsp(tsp, instance);
	print_matrix_distance(tsp);

	itinerary i;
	init_itinerary(i, instance);

	make_greedy_itinerary(tsp, i);
	print_itinerary(i);

	two_opt_optimize(tsp, i);
	print_itinerary(i);

	import_itinerary_coord(i, instance);
	export_itinerary(i, instance);

	delete[] i.data;
	delete_matrix(tsp);

	return 0;
}
