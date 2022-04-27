#include "import.h"

double distance(point a, point b)
{
    return sqrt(pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
}

unsigned int get_tsp_size(std::string file)
{
	std::ifstream f(file);

	if (f.good())
	{
		std::string target1 = "DIMENSION:";
		std::string target2 = "DIMENSION";
		std::string word;
		bool found = false;

		while (not found and !f.eof())
		{
			f >> word;
			if (word == target1 or word == target2)
			{
				found = true;
				f >> word;

				if (word == ":")
					f >> word;
			}
		}
		return std::stoi(word);
	}
	return 0;
}

double** import_tsp_cord(std::string file);

double** import_tsp_matrice(std::string file);

/* pas testé */
double** import_tsp(std::string file)
{
	std::ifstream f(file);

	if (f.good())
	{
		std::string target = "NODE_COORD_SECTION";
		std::string line;
		bool match = false;
		unsigned int i = 0;

		/*
		 * on considère que les informations de l'instance ne dépassent
		 * pas les 10 lignes
		 */
		while (i < 10 and match == false)
		{
			std::getline(f,line);

			if (line == target)
				match = true;

			++i;
		}

		if (match)
			return import_tsp_cord(file);
		else
			return import_tsp_matrice(file);
	}
	else
	{
		std::cout << "Erreur : le fichier " << file
			<< "n'as pas pu être lu" << std::endl;
		return nullptr;
	}
}
