#include "matrix.h"
#include "import.h"
#include "tour.h"
#include "calcul-tour.h"

#include <bits/stdc++.h>
#include <string>

void make_syscall(std::string com)
{
	int sysr = system(com.c_str());
	if (sysr != 0)
	{
		std::cerr << "Error: couldn't execute system call:\n\t"
			<< com << "\n\n";
		std::terminate();
	}

}

int main(int argc, char *argv[])
{
	std::string red = "\033[1;31m";
	std::string end_color = "\033[0m";
	std::string center = "\t\t";

	make_syscall("clear");

	/*--------- *
	 * TEST ARG *
	 * -------- */

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
		<< std::endl

		<< "\t\tUtilisation général " + red + "(IMPORTANT : nécessite un tour !)" + end_color + ":\n"
		<< "\t\t\t-q , --quiet\n"
		<< "\t\t\t\tN'affiche rien mais l'éxécution du programme est réalisé\n"
		<< "\t\t\t-i , --interactif\n"
		<< "\t\t\t\tLe mode intéractif est mis par défault" + red + " (Cette option doit être utilisée SEULE !) "
		<< end_color + "\n"
		<< "\t\t\t--gif\n"
		<< "\t\t\t\tCréation d'un gif des résultats\n"
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

	if (get_tsp_size(instance) == 0)
	{
		std::cerr << "\n" + center + red + "ERREUR, VOTRE FICHIER N'EST PAS COMPATIBLE,\n"
				+ center + "VEUILLEZ UTILISER UN AUTRE FICHIER.\n\n" + end_color;
		return 1;
	}


	bool glouton = false;
	bool fourmis = false;
	bool genetique = false;
	bool two_opt = false;

	bool quiet = false;
	bool gif = false;
	bool interactif = false;

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
		else if (std::string(argv[i]) == "-q" or std::string(argv[i]) == "--quiet")
		{
			quiet = true;
			++i;
		}
		else if (std::string(argv[i]) == "--gif")
		{
			gif = true;
			++i;
		}
		else if (std::string(argv[i]) == "-i" or std::string(argv[i]) == "--interactif")
		{
			interactif = true;
			++i;
		}
		else
			++i;
	}

	if (interactif)
	{
		if (interactif + glouton + fourmis + genetique + two_opt + quiet + gif > 1)
		{
			std::cerr << "\n" + center + red + "ERREUR, CETTE OPTION DOIT ETRE UTILISEE SEULE !\n" + end_color;
			goto error;
		}
	}

	/* ---------------------- *
	 * EXECUTION DU PROGRAMME *
	 * ---------------------- */

	matrix tsp;
	build_matrix(tsp, instance);
	import_tsp(tsp, instance);

	solution s = nullptr;

	if (interactif)
	{
		int chance = 1;
		int chance_opti = 1;

		int algo;
		chance_algorithme:
		std::cout << "\tQuelle algorithme voulez-vous utiliser ?\n"
				<< "\t\t1 = glouton\n"
				<< "\t\t2 = fourmis\n"
				<< "\t\t3 = genetique\n"
				<< "\t: ";
		std::cin >> algo;

		char opti;
		chance_optimisation:
		std::cout << "\n\tVoulez-vous faire une optimisation ? (y,N) : ";
		std::cin >> opti;

		switch (algo)
		{
		case 1:
			if (opti == 'y' or opti == 'Y')
				find_greedy_optimized_solution(s, tsp, instance);
			if (opti == 'n' or opti  == 'N')
				find_greedy_solution(s, tsp, instance);
			if (opti != 'y' and opti != 'Y' and opti != 'n' and opti != 'N')
			{
				if (chance_opti < 3)
				{
					std::cout << "\tJe n'ai pas compris !\n\n";
					++chance_opti;
					goto chance_optimisation;
				}
				else
				{
					std::cout << "\tVous vous êtes trompé trop de fois de suite !\n\n";
					return 1;
				}
			}
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			if (chance < 3)
			{
				std::cout << "\tJe n'ai pas compris !\n\n";
				++chance;
				goto chance_algorithme;
			}
			else
			{
				std::cout << "\tVous vous êtes trompé trop de fois de suite !\n\n";
				return 1;
			}
		}

		chance = 0;

		char affi;
		chance_affichage:
		std::cout << "\tVoulez-vous afficher le résultat ? (y,N) : ";
		std::cin >> affi;

		switch (affi)
		{
		case 'y':
		case 'Y':
			print_solution_result(s);
			break;
		case 'n':
		case 'N':
			break;
		default:
			if (chance < 3)
			{
				std::cout << "\tJe n'ai pas compris !\n\n";
				++chance;
				goto chance_affichage;
			}
			else
			{
				std::cout << "\tVous vous êtes trompé trop de fois de suite !\n\n";
				return 1;
			}
		}

		chance = 0;

		char gnuplot;
		chance_gnuplot:
		std::cout << "\tVoulez-vous créer un .gif des résultats ? (y/N) : ";
		std::cin >> gnuplot;

		switch (gnuplot)
		{
		case 'y':
		case 'Y':
		{
			std::cout << "\tCréation du fichier .gif..." << std::endl;
			build_gnuplot_datafile(s, instance);
			std::string com = "gnuplot -e \"filename = \\\"./" +
					instance + ".dat\\\"\" ./tsp/plot.gp  2>/dev/null";
			make_syscall(com);

			chance = 0;

			char affichage;
			chance_affichage_gnuplot:
			std::cout << "\tVoulez-vous afficher le fichier .gif ? (y/N) : ";
			std::cin >> affichage;

			switch (affichage)
			{
			case 'y':
			case 'Y':
			{
				std::cout << "\tAffichage du fichier .gif..." << std::endl;
				std::string com_open = "xdg-open " + instance + ".dat.gif 2>/dev/null";
				make_syscall(com_open);
				break;
			}
			case 'n':
			case 'N':
				std::cout <<"\tLe gif ne sera pas affiché." << std::endl;
				break;
			default:
				if (chance < 3)
				{
					std::cout << "\tJe n'ai pas compris !\n\n";
					++chance;
					goto chance_affichage_gnuplot;
				}
				else
				{
					std::cout << "\tVous vous êtes trompé trop de fois de suite !\n\n";
					return 1;
				}
			}
			break;
		}
		case 'n':
		case 'N':
			std::cout << "\tLe fichier .gif ne sera pas créé" << std::endl;
			break;
		default:
			if (chance < 3)
			{
				std::cout << "\tJe n'ai pas compris !\n\n";
				++chance;
				goto chance_gnuplot;
			}
			else
			{
				std::cout << "\tVous vous êtes trompé trop de fois de suite !\n\n";
				return 1;
			}
		}
	}

	delete_matrix(tsp);



	return 0;
}
