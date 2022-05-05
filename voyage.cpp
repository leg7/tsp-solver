#include "matrix.h"
#include "import.h"
#include "itineraire.h"
#include "calcul-itineraire.h"

#include <bits/stdc++.h>
#include <string>

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "\n\tUsage : ./voyage [OPTION] [input-file]\n\n"

		<< "\tOptions :\n"

		<< "\t\tCréation d'itinéraire :\n"
		<< "\t\t\t-g , --glouton\n"
		<< "\t\t\t\tTrouve un itinéraire avec l'algorithme Glouton\n"
		<< std::endl

		<< "\t\tOptimisation d'itinéraire (IMPORTANT : nécessite un itinéraire !)\n"
		<< "\t\t\t-o , --2-opt\n"
		<< "\t\t\t\tOptimise un itinéraire par méthode 2-opt\n"
		<< std::endl;
		
		return 1;
	}

	bool glouton = false;
	bool two_opt = false;

	bool file_ok = false;


	// /* std::string instance = "tsp/att48.tsp"; */
	// std::string instance = "tsp/bayg29.tsp";

	// matrix tsp;
	// build_matrix(tsp, instance);
	// import_tsp(tsp, instance);
	// /* print_matrix_distance(tsp); */

	// itinerary i;

	// i = find_best_optimized_greedy_itinerary(tsp, instance);
	// print_itinerary(i);

	// char gnuplot;
	// std::cout << "\tVoulez-vous créer un .gif des résultats ? (y/N) : ";
	// std::cin >> gnuplot;

	// switch (gnuplot)
	// {
	// case 'y':
	// case 'Y':
	// {
	// 	std::string com = "gnuplot -e \"filename = \\\"./" + instance + ".dat\\\"\" ./tsp/plot.gp  2>/dev/null";
	// 	const char *command = com.c_str();
	// 	std::cout << "\tCréation du fichier .gif..." << std::endl;
	// 	system(command);
	// 	break;
	// }
	// case 'n':
	// case 'N':
	// 	std::cout << "\tLe fichier .gif ne sera pas créé" << std::endl;
	// 	break;
	// default:
	// 	std::cout << "\tJe n'ai pas compris !" << std::endl;
	// }

	// delete[] i.data;
	// delete_matrix(tsp);

	return 0;
}
