/* Ce fichier est une boucle main temporaire pour permettre de complier le code */
#include "import.h"
#include "calcul-itineraire.h"
#include <iostream>

void delete_matrix(matrix &tsp)
{
	for (unsigned int i = 0; i < tsp.n; ++i)
		delete[] tsp.m[i];
	delete[] tsp.m;
}

void print_itinerary(matrix tsp, itinerary it)
{
	std::cout << "L'itineraire serait d'une longeure de " << it.length
		<< " : \n\n";

	for (unsigned int k = 0; k < tsp.n; ++k)
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
	make_greedy_itinerary(tsp,i);
	print_itinerary(tsp,i);

	delete[] i.data;
	delete_matrix(tsp);

	return 0;
}
