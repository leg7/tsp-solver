#include "import.h"

double distance(point a, point b)
{
    return sqrt(pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
}

double** import_tsp_cord(std::string file);

double** import_tsp_matrice(std::string file);

/* pas testé */
double** import_tsp(std::string file)
{
	std::ifstream f(file);

	if (f.is_open())
	{
		std::string target = "NODE_COORD_SECTION";
		std::string line;
		bool match = false;
		unsigned int i = 0;

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
