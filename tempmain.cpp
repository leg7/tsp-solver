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

int main()
{
	/* std::string instance = "tsp/att48.tsp"; */
	std::string instance = "tsp/bayg29.tsp";

	matrix tsp;
	build_matrix(tsp,instance);
	import_tsp(tsp,instance);
	/* print_matrix(tsp); */

	/* std::cout << get_min_and_zero(tsp,27) << std::endl << std::endl; */
	/* std::cout << get_min_and_zero(tsp,2) << std::endl << std::endl; */
	destination *t = glouton(tsp);
	/* print_matrix(tsp); */

	/* std::cout << std::endl; */

	for (unsigned int i = 0; i < tsp.n; ++i)
		std::cout << t[i].num+1 << '\n';

	delete[] t;
	delete_matrix(tsp);

	return 0;
}
