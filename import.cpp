#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "data.h"
#include "import.h"

size_t get_tsp_size(std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		std::string word;
		bool found = false;

		/* si i >= 30 on considère que dimension est absent */
		size_t i = 0;
		while (not found and i < 30)
		{
			file >> word;
			if (word == "DIMENSION:" or word == "DIMENSION")
			{
				found = true;

				file >> word;
				if (word == ":")
					file >> word;
			}
			++i;
		}
		if (found == true)
			return std::stoi(word);
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;

	return 0;
}

/* testé ok */
std::ifstream go_to_target(std::string filename, std::string target, size_t n)
{
	std::ifstream file(filename);
	if (file.good())
	{
		/* on se place au niveau des coordonnées des points */
		std::string line;
		do
		{
			std::getline(file,line);
		}
		while (line != target and !file.eof());

		std::string trash;
		for (;n > 0 ; --n)
			std::getline(file,trash);
	}

	return file;
}

bool find_target(std::string filename, std::string target)
{
	std::ifstream file(filename);
	if (file.good())
	{
		std::string line;
		while (not file.eof())
		{
			std::getline(file,line);
			if (line == target)
				return true;
		}
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;

	return false;
}

/* testé ok */
size_t distance(point a, point b)
{
    return sqrt(pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
}

/*
 * fonction de calcul de distances "pseudo-euclidienne" pour les instances
 * avec "EDGE_WEIGHT_TYPE : ATT".
 * Cette fonction est copié de la specification tsplib95.
 */
size_t att_distance(point i, point j)
{
	int xd = i.x - j.x;
	int yd = i.y - j.y;
	double rij = sqrt((xd*xd + yd*yd) / 10.0);
	size_t tij = size_t(rij);

	if (tij < rij)
		return tij + 1;
	else
		return tij;
}

bool is_att_instance(std::string filename)
{
	return find_target(filename, "EDGE_WEIGHT_TYPE : ATT");
}

/* testé ok */
void import_att_instance(matrix &tsp, std::string filename)
{
	if (!is_att_instance(filename))
		throw std::invalid_argument("Instance pas de type ATT");

	std::ifstream file(filename);
	if (file.good())
	{
		/* on remplit la matrice d'adjacence */
		size_t x = tsp.size;
		for (size_t i = 0; i < tsp.size; ++i)
		{
			/* on se place au bonne endroit */
			file = go_to_target(filename, "NODE_COORD_SECTION", i);
			std::string ignore;
			file >> ignore;

			/* on prend le premier numero */
			std::string number;
			file >> number;
			point a;
			a.x = std::stoi(number);

			/* le deuxième */
			file >> number;
			a.y = std::stoi(number);

			/* on passe a la ligne */
			std::getline(file,ignore);

			/* on calcule la distance avec tous les autres points */
			for (size_t j = 0; j < x; ++j)
			{
				file >> ignore;
				if (ignore == "EOF")
					break;

				/* on prend le premier numero */
				file >> number;
				point b;
				b.x = std::stoi(number);

				/* le deuxième */
				file >> number;
				b.y = std::stoi(number);

				tsp.data[i][j].distance = att_distance(a, b);
			}
		}
	}
}

/* testé ok */
void import_tsp_matrix(matrix &tsp, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		file = go_to_target(filename, "EDGE_WEIGHT_SECTION", 0);

		/* on remplit la matrice d'adjacence */
		size_t x = tsp.size;
		for (size_t i = 0; i < tsp.size; ++i)
		{
			for (size_t j = 0; j < x; ++j)
			{
				std::string number;
				file >> number;
				tsp.data[i][j].distance = std::stoi(number);
			}
			--x;
		}
	}
}

/* pas testé */
void import_tsp(matrix &tsp, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		if (is_att_instance(filename))
			import_att_instance(tsp, filename);
		else
			import_tsp_matrix(tsp, filename);
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

void import_destination_coord(destination &d, std::string target, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		file = go_to_target(filename, target, d.id);
		std::string ignore;

		file >> ignore;
		file >> d.coord.x;
		file >> d.coord.y;
	}
}

void import_tour_coord(tour &t, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		if (find_target(filename, "NODE_COORD_SECTION"))
			for (size_t i = 0; i < t.size; ++i)
				import_destination_coord(t.data[i], "NODE_COORD_SECTION", filename);
		else
			for (size_t i = 0; i < t.size; ++i)
				import_destination_coord(t.data[i], "DISPLAY_DATA_SECTION", filename);
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

