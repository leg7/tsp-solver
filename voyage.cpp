#include "matrix.h"
#include "import.h"
#include "tour.h"
#include "calcul-tour.h"

#include <bits/stdc++.h>
#include <string>

int main(int argc, char *argv[])
{
	/* if (argc < 3) */
	/* { */
	/* 	std::cout << "\n\tUsage : ./voyage [OPTION] [input-file]\n\n" */

	/* 	<< "\tOptions :\n" */

	/* 	<< "\t\tCréation du tour :\n" */
	/* 	<< "\t\t\t-g , --glouton\n" */
	/* 	<< "\t\t\t\tTrouve un tour avec l'algorithme Glouton\n" */
	/* 	<< std::endl */

	/* 	<< "\t\tOptimisation du tour (IMPORTANT : nécessite un tour !)\n" */
	/* 	<< "\t\t\t-o , --2-opt\n" */
	/* 	<< "\t\t\t\tOptimise un tour par méthode 2-opt\n" */
	/* 	<< std::endl; */

	/* 	return 1; */
	/* } */

	/* bool glouton = false; */
	/* bool two_opt = false; */

	/* bool file_ok = false; */

	std::string instance = "tsp/att48.tsp";
	/* std::string instance = "tsp/bayg29.tsp"; */

	matrix tsp;
	build_matrix(tsp, instance);
	import_tsp(tsp, instance);

	solution s = nullptr;
	find_greedy_optimized_solution(s, tsp, instance);
	print_solution_result(s);

	delete_matrix(tsp);

	char gnuplot;
	std::cout << "\tVoulez-vous créer un .gif des résultats ? (y/N) : ";
	std::cin >> gnuplot;

	switch (gnuplot)
	{
	case 'y':
	case 'Y':
	{
		std::cout << "\tCréation du fichier .gif..." << std::endl;
		std::string com = "gnuplot -e \"filename = \\\"./" + instance + ".dat\\\"\" ./tsp/plot.gp  2>/dev/null";
		build_gnuplot_datafile(s, instance);
		system(com.c_str());
		break;
	}
	case 'n':
	case 'N':
		std::cout << "\tLe fichier .gif ne sera pas créé" << std::endl;
		break;
	default:
		std::cout << "\tJe n'ai pas compris !" << std::endl;
	}

	return 0;
}
