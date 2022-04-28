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

/* testé ok */
std::ifstream go_to(std::string file, std::string target, unsigned int n)
{
	std::ifstream f(file);
	if (f.good())
	{
		/* on se place au niveau des coordonnées des points */
		std::string line;
		do
		{
			std::getline(f,line);
		}
		while (line !=  target and !f.eof());

		std::string trash;
		for (;n > 0 ; --n)
			std::getline(f,trash);
	}
	return f;
}

/* testé ok */
double** import_tsp_cord(std::string file)
{
	std::ifstream f(file);
	if (f.good())
	{
		unsigned int size = get_tsp_size(file);
		double **m = build_matrix(size);

		/* on se place au niveau des coordonnées des points */
		std::string target = "NODE_COORD_SECTION";

		/* on remplit la matrice d'adjacence */
		unsigned int x = size - 1;
		for (unsigned int i = 0; i < size - 1; ++i)
		{
			f = go_to(file, target, i);

			std::string coor;
			f >> coor;
			f >> coor;

			point a;
			a.x = std::stoi(coor);
			f >> coor;
			a.y = std::stoi(coor);

			f.ignore();

			for (unsigned int j = 0; j < x; ++j)
			{
				f >> coor;
				if (coor == "EOF")
					break;

				f >> coor;
				point b;
				b.x = std::stoi(coor);
				f >> coor;
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
double** import_tsp_matrice(std::string file)
{
	std::ifstream f(file);
	if (f.good())
	{
		unsigned int size = get_tsp_size(file);
		double **m = build_matrix(size);

		/* on se place au niveau des données de la matrice */
		std::string target = "EDGE_WEIGHT_SECTION"
		f = go_to(file,target,0);

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
