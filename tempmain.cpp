/* Ce fichier est une boucle main temporaire pour permettre de complier le code */
#include "matrix.h"
#include "import.h"
#include "calcul-itineraire.h"

#include <iostream>

void init_itinerary(itinerary &it, std::string instance)
{
	it.length = 0;

	it.size = get_tsp_size(instance);

	it.data = new destination[it.size];
	it.data[0].distance = 0;
	it.data[0].num      = 0;
}

void print_itinerary(matrix tsp, itinerary it)
{
	std::cout << "L'itineraire serait d'une longeure de " << it.length
		<< " : \n\n";

	for (unsigned int k = 0; k < it.size; ++k)
		std::cout << "\t" << it.data[k].num + 1 << std::endl;

	std::cout << std::endl;
}

int main()
{
	/* std::string instance = "tsp/att48.tsp"; */
	std::string instance = "tsp/bayg29.tsp";

	matrix tsp;
	build_matrix(tsp,instance);
	import_tsp(tsp,instance);
	print_matrix_distance(tsp);

	itinerary i;
	init_itinerary(i,instance);

	make_greedy_itinerary(tsp,i);
	print_itinerary(tsp,i);

	delete[] i.data;
	delete_matrix(tsp);

	return 0;
}
