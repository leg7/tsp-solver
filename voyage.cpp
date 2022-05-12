#include "matrix.h"
#include "import.h"
#include "tour.h"
#include "calcul-tour.h"

#include <bits/stdc++.h>
#include <string>

int main(int argc, char *argv[])
{
	std::string red = "\033[1;31m";
	std::string end_color = "\033[0m";
	std::string center = "\t\t";

	std::string clear = "clear";
	system(clear.c_str());

	if (argc < 3)
	{
		error:
		std::cout << "\n\tUsage : ./voyage [OPTION] [input-file]\n\n"

		<< "\tOptions " + red + "(IMPORTANT : choisissez qu'un seul algorithme !)" + end_color +" :\n"
		<< "\t\tCréation d'un tour :\n"
		<< "\t\t\t-g , --glouton\n"
		<< "\t\t\t\tTrouve un itinéraire avec l'algorithme Glouton\n"
		<< "\t\t\t-f , --fourmis\n"
		<< "\t\t\t\tTrouve un itinéraire avec l'algorithme des fourmis\n"
		<< "\t\t\t-G , --genetique\n"
		<< "\t\t\t\tTrouve un itinéraire avec un algorithme génétique\n"
		<< std::endl

		<< "\t\tOptimisation du tour " + red + "(IMPORTANT : nécessite un tour !)" + end_color +" :\n"
		<< "\t\t\t-o , --2-opt\n"
		<< "\t\t\t\tOptimise un tour par méthode 2-opt\n"
		<< std::endl;
		return 1;
	}

	std::string instance = std::string(argv[argc - 1]);
	std::ifstream test(instance);
	if (!test.good())
	{
		std::cerr << "\n" + center + red + "ERREUR, IMPOSSIBLE DE LIRE LE FICHIER !\n" + end_color;
		goto error;
	}


	bool glouton = false;
	bool fourmis = false;
	bool genetique = false;
	bool two_opt = false;

	int i = 0;
	while (i < argc - 1)
	{
		if (std::string(argv[i]) == "-g" or std::string(argv[i]) == "--glouton")
		{
			glouton = true;
			++i;
		}

		else if (std::string(argv[i]) == "-f" or std::string(argv[i]) == "--fourmis")
		{
			fourmis = true;
			++i;
		}

		else if (std::string(argv[i]) == "-G" or std::string(argv[i]) == "--genetique")
		{
			genetique = true;
			++i;
		}
		else if (std::string(argv[i]) == "-o" or std::string(argv[i]) == "--2-opt")
		{
			two_opt = true;
			++i;
		}
		else
			++i;
	}

	if (glouton + fourmis + genetique > 1)
	{
		std::cerr << "\n" + center + red +"ERREUR CHOISISSEZ QU'UN SEUL ALGORITHME !\n " + end_color;
		goto error;
	}

	if (glouton + fourmis + genetique == 0)
	{
		std::cerr << "\n" + center + red + "ERREUR, VOUS N'AVEZ PAS CHOISIT D'ALGORITHME !\n" + end_color;
		goto error;
	}

	matrix tsp;
	build_matrix(tsp, instance);
	if (tsp.size == 0)
	{
		std::cerr << "\n" + center + red + "ERREUR, VOTRE FICHIER N'EST PAS COMPATIBLE,\n"
				+ center + "VEUILLEZ UTILISER UN AUTRE FICHIER.\n\n" + end_color;
		goto end;
	}

	import_tsp(tsp, instance);

	solution s = nullptr;

	if (glouton == true and two_opt == false)
	{
		find_greedy_solution(s, tsp, instance);
		std::cout << "\nVoici le meilleur itinéraire glouton, ";
	}

	if (glouton == true and two_opt == true)
	{
		find_greedy_optimized_solution(s, tsp, instance);
		std::cout << "\nVoici le meilleur itinéraire glouton avec une optimisation 2-opt, "
			  << "Pour le trouver " << OPT_SWAPS
			  << " échanges 2-opt ont étés realisés\n";
	}

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

		char affichage;
		std::cout << "\tVoulez-vous afficher le fichier .gif ? (y/N) : ";
		std::cin >> affichage;

		switch (affichage)
		{
		case 'y':
		case 'Y':
		{
			std::cout << "\tAffichage du fichier .gif..." << std::endl;
			std::string com_open = "xdg-open " + instance + ".dat.gif 2>/dev/null";
			system(com_open.c_str());
			break;
		}
		case 'n':
		case 'N':
			std::cout <<"\tLe gif ne sera pas affiché." << std::endl;
			break;
		default:
			std::cout << "\tJe n'ai pas compris !" << std::endl;
		}
		break;
	}
	case 'n':
	case 'N':
		std::cout << "\tLe fichier .gif ne sera pas créé" << std::endl;
		break;
	default:
		std::cout << "\tJe n'ai pas compris !" << std::endl;
	}

	end:
	return 0;
}
