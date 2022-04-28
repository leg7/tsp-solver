/* Ce fichier est une boucle main temporaire pour permettre de complier le code */
#include "import.h"

int main()
{
	std::string instance = "tsp/att48.tsp";
	double **m;
	m = import_tsp(instance);
	print_matrix(m, get_tsp_size(instance));
	return 0;
}
