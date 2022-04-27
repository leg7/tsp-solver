#include "import.h"

/* testé ok */
double** build_matrix(unsigned int n)
{
	double **m = new double*[n];

	unsigned int x = n - 1;
	for (unsigned int i = 0; i < n; ++i)
	{
		m[i] = new double[x];
		--x;
	}

	return m;
}

/* testé ok */
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

/* testé ok */
double distance(point a, point b)
{
    return sqrt(pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
}

/* à faire */
double** import_tsp_cord(std::string file);

/* testé ok */
double** import_tsp_matrice(std::string file)
{
	unsigned int size = get_tsp_size(file);
	double **m = build_matrix(size);

	std::ifstream f(file);
	if (f.good())
	{
		/* on se place au niveau des données de la matrice */
		std::string line;
		do
		{
			std::getline(f,line);
		}
		while(line != "EDGE_WEIGHT_SECTION" and !f.eof());

		/* on remplit la matrice d'adjacence */
		unsigned int x = size - 1;
		for (unsigned int i = 0; i < size; ++i)
		{
			for (unsigned int j = 0; j < x; ++j)
			{
				std::string num;
				f >> num;
				m[i][j] = std::stoi(num);
			}
			--x;
		}
		return m;
	}
	else
		return nullptr;
}

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
