#include "import.h"

#include <iostream>
#include <cmath>
#include <fstream>

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

void print_matrix(double **m, unsigned int n)
{
	unsigned int x = n - 1;
	for (unsigned int i = 0; i < n; ++i)
	{
		for (unsigned int j = 0; j < x;  ++j)
			std::cout << m[i][j] << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/* testé ok */
unsigned int get_tsp_size(std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		std::string target1 = "DIMENSION:";
		std::string target2 = "DIMENSION";
		std::string word;
		bool found = false;

		while (not found and !file.eof())
		{
			file >> word;
			if (word == target1 or word == target2)
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
double distance(point a, point b)
{
    return sqrt(pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
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
		while (line !=  target and !file.eof());

		std::string trash;
		for (;n > 0 ; --n)
			std::getline(file,trash);
	}
	return file;
}

/* testé ok */
double** import_tsp_cord(std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		unsigned int size = get_tsp_size(filename);
		double **m = build_matrix(size);

		/* on se place au niveau des coordonnées des points */
		std::string target = "NODE_COORD_SECTION";

		/* on remplit la matrice d'adjacence */
		unsigned int x = size - 1;
		for (unsigned int i = 0; i < size - 1; ++i)
		{
			file = go_to(filename, target, i);

			std::string coor;
			file >> coor;
			file >> coor;

			point a;
			a.x = std::stoi(coor);
			file >> coor;
			a.y = std::stoi(coor);

			file.ignore();

			for (unsigned int j = 0; j < x; ++j)
			{
				file >> coor;
				if (coor == "EOF")
					break;

				file >> coor;
				point b;
				b.x = std::stoi(coor);
				file >> coor;
				b.y = std::stoi(coor);

				m[i][j] = distance(a, b);
			}
		}
		return m;
	}
	else
		return nullptr;
}

/* testé ok */
double** import_tsp_matrice(std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		unsigned int size = get_tsp_size(filename);
		double **m = build_matrix(size);

		/* on se place au niveau des données de la matrice */
		std::string target = "EDGE_WEIGHT_SECTION";
		file = go_to(filename,target,0);

		/* on remplit la matrice d'adjacence */
		unsigned int x = size - 1;
		for (unsigned int i = 0; i < size; ++i)
		{
			for (unsigned int j = 0; j < x; ++j)
			{
				std::string num;
				file >> num;
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
double** import_tsp(std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
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
			std::getline(file,line);

			if (line == target)
				match = true;

			++i;
		}

		if (match)
			return import_tsp_cord(filename);
		else
			return import_tsp_matrice(filename);
	}
	else
	{
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
		return nullptr;
	}
}
