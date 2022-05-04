#include "matrix.h"
#include "import.h"
#include "itineraire.h"
#include "calcul-itineraire.h"

#include <string>

int main()
{
	/* std::string instance = "tsp/att48.tsp"; */
	std::string instance = "tsp/bayg29.tsp";

	matrix tsp;
	build_matrix(tsp, instance);
	import_tsp(tsp, instance);
	/* print_matrix_distance(tsp); */

	itinerary i;

	i = find_best_optimized_greedy_itinerary(tsp, instance);
	print_itinerary(i);

	delete[] i.data;
	delete_matrix(tsp);

	return 0;
}
