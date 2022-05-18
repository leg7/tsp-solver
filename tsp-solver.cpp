#include <bits/stdc++.h>
#include <filesystem>
#include <string>

#include "calcul-tour.h"
#include "data.h"
#include "export.h"
#include "import.h"

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
		help:
		std::cout << "\n\tUsage : ./voyage [OPTION] [input-file]\n\n"

		<< "\tOptions " + red + "(IMPORTANT : choisissez qu'un seul algorithme !)" + end_color +" :\n"
		<< "\t\tCréation d'un tour :\n"
		<< "\t\t\t-g , --glouton\n"
		<< "\t\t\t\tTrouve un itinéraire avec l'algorithme Glouton\n"
		<< "\t\t\t-r , --recuit-simule\n"
		<< "\t\t\t\tTrouve un itinéraire avec un algorithme de recuit simulé\n"
		<< "\t\t\t-f , --fourmis (WIP)\n"
		<< "\t\t\t\tTrouve un itinéraire avec l'algorithme des fourmis (WIP)\n"
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
		<< "\t\t\t--gif\n"
		<< "\t\t\t\tModelise la solution avec gnuplot sous format animé .gif\n"
		<< "\t\t\t--open-gif\n"
		<< "\t\t\t\tOuvre le gif produit par --gif\n"
		<< "\t\t\t-i , --interactif\n"
		<< "\t\t\t\tLe mode intéractif est mis par défault" + red + " (Cette option doit être utilisée SEULE !) "
		<< end_color + "\n"
		<< std::endl;

		return 1;
	}

	std::string instance = std::string(argv[argc - 1]);
	std::ifstream test(instance);
	if (!test.good())
	{
		std::cerr << "\n" + center + red + "ERREUR, IMPOSSIBLE DE LIRE LE FICHIER !\n" + end_color;
		goto help;
	}

	if (get_tsp_size(instance) == 0)
	{
		std::cerr << "\n" + center + red + "ERREUR, VOTRE FICHIER N'EST PAS COMPATIBLE,\n"
				+ center + "VEUILLEZ UTILISER UN AUTRE FICHIER.\n\n" + end_color;
		return 1;
	}

	/* --------- *
	 * RECUP ARG *
	 * --------- */

	bool glouton    = false;
	bool recuit     = false;
	bool fourmis    = false;
	bool genetique  = false;
	bool two_opt    = false;

	bool quiet      = false;
	bool gif        = false;
	bool interactif = false;
	bool open_gif   = false;

	int i = 0;
	while (i < argc - 1)
	{
		if (std::string(argv[i]) == "-g" or
		    std::string(argv[i]) == "--glouton")
		{
			glouton = true;
			++i;
		}
		else if (std::string(argv[i]) == "-r" or
		         std::string(argv[i]) == "--recuit-simule")
		{
			recuit = true;
			++i;
		}
		else if (std::string(argv[i]) == "-f" or
		         std::string(argv[i]) == "--fourmis")
		{
			fourmis = true;
			++i;
		}
		else if (std::string(argv[i]) == "-G" or
		         std::string(argv[i]) == "--genetique")
		{
			genetique = true;
			++i;
		}
		else if (std::string(argv[i]) == "-o" or
		         std::string(argv[i]) == "--2-opt")
		{
			two_opt = true;
			++i;
		}
		else if (std::string(argv[i]) == "-q" or
		         std::string(argv[i]) == "--quiet")
		{
			quiet = true;
			++i;
		}
		else if (std::string(argv[i]) == "--gif")
		{
			gif = true;
			++i;
		}
		else if (std::string(argv[i]) == "--open-gif")
		{
			open_gif = true;
			++i;
		}
		else if (std::string(argv[i]) == "-i" or
		         std::string(argv[i]) == "--interactif")
		{
			interactif = true;
			++i;
		}
		else
			++i;
	}

	/* --------------- *
	 * MODE INTERACTIF *
	 * --------------- */

	if (interactif)
	{
		if (interactif + glouton + fourmis + genetique + two_opt + quiet + gif > 1)
		{
			std::cerr << "\n" + center + red + "ERREUR, CETTE OPTION DOIT ETRE UTILISEE SEULE !\n" + end_color;
			goto help;
		}

		glouton   = false;
		recuit    = false;
		fourmis   = false;
		genetique = false;
		two_opt   = false;

		gif       = false;
		open_gif  = false;  // pour l'interactif
		                   //
		int chance = 2;
		while (glouton + recuit + fourmis + genetique == 0)
		{
			char algo = 0;
			std::cout << "\tQuelle algorithme voulez-vous utiliser ?\n"
					<< "\t\t1 = glouton\n"
					<< "\t\t2 = recuit simulé\n"
					<< "\t\t3 = fourmis (WIP)\n"
					<< "\t\t4 = genetique\n"
					<< "\t: ";
			std::cin >> algo;

			switch (algo)
			{
			case '1':
				glouton = true;
				break;
			case '2':
				recuit = true;
				break;
			case '3':
				fourmis = true;
				break;
			case '4':
				genetique = true;
				break;
			default:
				if (chance > 0)
				{
					std::cout << "Je n'ai pas compris votre reponse.\n";
					--chance;
				}
				else
				{
					std::cout << "Je ne comprends pas ce que vous voulez "
						<< "donc je vais choisir l'algorithme glouton par default.\n";
					glouton = true;
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		chance = 2;
		while (chance >= 0)
		{
			char opti = 0;
			std::cout << "\tVoulez-vous faire une optimisation ? (y,N) : ";
			std::cin >> opti;

			switch (opti)
			{
			case 'y':
			case 'Y':
				two_opt = true;
				chance = -1;
				break;
			case 'n':
			case 'N':
				chance = -1;
				break;
			default:
				if (chance > 0)
				{
					std::cout << "Pas compris !\n";
					--chance;
				}
				else if (chance == 0)
				{
					std::cout << "Je ne comprends pas ce que vous voulez "
						<< "donc je ne vais pas faire d'optimisation par default.\n";
					--chance;
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		chance = 2;
		while (chance >= 0)
		{
			char aff = 0;
			std::cout << "\tVoulez-vous afficher le résultat ? (y,N) : ";
			std::cin >> aff;

			switch (aff)
			{
			case 'y':
			case 'Y':
				chance = -1;
				break;
			case 'n':
			case 'N':
				quiet = true;
				chance = -1;
				break;
			default:
				if (chance > 0)
				{
					std::cout << "\tJe n'ai pas compris !\n\n";
					--chance;
				}
				else if (chance == 0)
				{
					std::cout << "\tJe ne comprends toujours pas, "
						<< "je vais supposer que vous ne voulez pas l'afficher.\n\n";
					--chance;
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		chance = 2;
		while (chance >= 0)
		{
			char gnuplot = 0;
			std::cout << "\tVoulez-vous créer un .gif des résultats ? (y/N) : ";
			std::cin >> gnuplot;

			switch (gnuplot)
			{
			case 'y':
			case 'Y':
				gif = true;
				chance = -1;
				break;
			case 'n':
			case 'N':
				std::cout << "\tLe fichier .gif ne sera pas créé" << std::endl;
				chance = -1;
				break;
			default:
				if (chance > 0)
				{
					std::cout << "\tJe n'ai pas compris !\n";
					--chance;
				}
				else if (chance == 0)
				{
					std::cout << "\tJe ne comprends toujours pas, "
						<< "je suppose que vous ne voulez pas l'afficher\n";
					--chance;
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		if (gif)
		{
			chance = 2;
			while (chance >= 0)
			{
				char aff = 0;
				std::cout << "\tVoulez-vous afficher le fichier .gif ? (y/N) : ";
				std::cin >> aff;

				switch (aff)
				{
				case 'y':
				case 'Y':
					open_gif = true;
					chance = -1;
					break;
				case 'n':
				case 'N':
					std::cout <<"\tLe gif ne sera pas affiché.\n";
					chance = -1;
					break;
				default:
					if (chance > 0)
					{
						std::cout << "\tJe n'ai pas compris !\n";
						--chance;
					}
					else if (chance == 0)
					{
						std::cout << "\tJe ne comprends pas, "
							<< "Je suppose que vous ne voulez pas l'afficher.\n";
						--chance;
					}
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	/* ---------------------- *
	 * EXECUTION DU PROGRAMME *
	 * ---------------------- */

	//init
	matrix tsp;
	init_matrix(tsp, instance);
	import_tsp(tsp, instance);

	solution s = nullptr;

	//tests
	if (glouton + recuit + fourmis + genetique > 1)
	{
		std::cerr << "\n" + center + red +"ERREUR CHOISISSEZ QU'UN SEUL ALGORITHME !\n " + end_color;
		goto help;
	}
	if (glouton + recuit + fourmis + genetique == 0)
	{
		std::cerr << "\n" + center + red + "ERREUR, VOUS N'AVEZ PAS CHOISIT D'ALGORITHME !\n" + end_color;
		goto help;
	}
	if (fourmis)
	{
		std::cout << red + "L'algorithme des fourmis est en cours de developpement et n'est pas fonctionel\n" + end_color;
		goto help;
	}

	if (glouton == true and two_opt == true)
	{
		find_greedy_optimized_solution(s, tsp, instance);
		if (!quiet)
		{
			std::cout << "Voici le meilleur itinéraire glouton avec une optimisation 2-opt, "
				  << "Pour le trouver " << OPT_SWAPS
				  << " échanges 2-opt ont étés realisés\n";
		}
	}
	else if (glouton == true and two_opt == false)
	{
		find_greedy_solution(s, tsp, instance);
		if (!quiet)
			std::cout << "Voici le meilleur itinéraire glouton\n";
	}
	if (recuit == true)
	{
		simmulated_annealing(s, tsp, instance);
		if (!quiet)
			std::cout << "Voici le meilleur itinéraire trouvé avec l'algorithme de recuit simulé\n";
	}

	if (!quiet)
		print_solution_result(s);

	if (gif)
	{
		if (!quiet)
			std::cout << "\tCréation du fichier .gif..." << std::endl;

		std::filesystem::path p(instance);
		std::string filename = p.replace_extension(".dat");
		build_gnuplot_datafile(s, filename);

		filename = p.replace_extension("");
		std::string com = "gnuplot -e \"filename = '" +
		                  filename + "'\"" +
		                  " plot.gp  2>/dev/null";
		make_syscall(com);
	}
	if (open_gif)
	{
		if (!quiet)
			std::cout << "\tAffichage du fichier .gif...\n";
		std::string com_open = "xdg-open " + instance + ".dat.gif 2>/dev/null";
		make_syscall(com_open);
	}

	delete_matrix(tsp);

	return 0;
}
