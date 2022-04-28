/* Ce fichier est une boucle main temporaire pour permettre de complier le code */
#include "import.h"

int main()
{
	/* std::string instance = "tsp/att48.tsp"; */
	std::string instance = "tsp/bayg29.tsp";

	matrix tsp;
	build_matrix(tsp,instance);
	import_tsp(tsp,instance);
	print_matrix(tsp);

	return 0;
}
