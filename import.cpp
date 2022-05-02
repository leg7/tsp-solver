#include "import.h"
#include "matrix.h"
#include "calcul-itineraire.h"

#include <iostream>
#include <cmath>
#include <fstream>

/* testé ok */
int get_tsp_size(std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		std::string word;
		bool found = false;

		/* si i >= 30 on considère que dimension est absent */
		unsigned int i = 0;
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
		}
		return std::stoi(word);
	}
	return 0;
}

/* testé ok */
std::ifstream go_to(std::string filename, std::string target, unsigned int n)
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

/* testé ok */
double distance(point a, point b)
{
    return sqrt(pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
}

/* testé ok */
void import_tsp_cord(matrix &tsp, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		/* on remplit la matrice d'adjacence */
		unsigned int x = tsp.n;
		for (unsigned int i = 0; i < tsp.n; ++i)
		{
			/* on se place au bonne endroit */
			file = go_to(filename, "NODE_COORD_SECTION", i);
			std::string ignore;
			file >> ignore;

			/* on prend le premier numero */
			std::string num;
			file >> num;
			point a;
			a.x = std::stoi(num);

			/* le deuxième */
			file >> num;
			a.y = std::stoi(num);

			/* on passe a la ligne */
			std::getline(file,ignore);

			/* on calcule la distance avec tous les autres points */
			for (unsigned int j = 0; j < x; ++j)
			{
				file >> ignore;
				if (ignore == "EOF")
					break;

				/* on prend le premier numero */
				file >> num;
				point b;
				b.x = std::stoi(num);

				/* le deuxième */
				file >> num;
				b.y = std::stoi(num);

				tsp.m[i][j].distance = distance(a, b);
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
		file = go_to(filename, "EDGE_WEIGHT_SECTION", 0);

		/* on remplit la matrice d'adjacence */
		unsigned int x = tsp.n;
		for (unsigned int i = 0; i < tsp.n; ++i)
		{
			for (unsigned int j = 0; j < x; ++j)
			{
				std::string num;
				file >> num;
				tsp.m[i][j].distance = std::stoi(num);
			}
			--x;
		}
	}
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

/* pas testé */
void import_tsp(matrix &tsp, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		if (find_target(filename, "NODE_COORD_SECTION"))
			import_tsp_cord(tsp, filename);
		else
			import_tsp_matrix(tsp, filename);
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

void import_itinerary_coord(itinerary &it, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		if (find_target(filename, "NODE_COORD_SECTION"))
			for (unsigned int i = 0; i < it.size; ++i)
				get_destination_coord(it.data[i], "NODE_COORD_SECTION", filename);
		else
			for (unsigned int i = 0; i < it.size; ++i)
				get_destination_coord(it.data[i], "DISPLAY_DATA_SECTION", filename);
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

void get_destination_coord(destination &d, std::string target, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		file = go_to(filename, target, d.num);
		std::string trash;

		file >> trash;
		file >> d.p.x;
		file >> d.p.y;
	}
}