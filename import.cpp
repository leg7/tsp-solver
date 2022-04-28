#include "import.h"

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
void build_matrix(matrix &tsp, std::string filename)
{
	tsp.n = get_tsp_size(filename);
	if (tsp.n > 0)
	{
		tsp.m = new double*[tsp.n];

		unsigned int x = tsp.n - 1;
		for (unsigned int i = 0; i < tsp.n; ++i)
		{
			tsp.m[i] = new double[x];
			--x;
		}
	}
	else
		std::cout << "Erreur critique : la taille de votre instance "
			<< "est <= 0 donc la matrice n'as pas été faite.\n";
}

/* testé ok */
void print_matrix(matrix tsp)
{
	unsigned int x = tsp.n - 1;
	for (unsigned int i = 0; i < tsp.n; ++i)
	{
		for (unsigned int j = 0; j < x;  ++j)
			std::cout << tsp.m[i][j] << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
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
double distance(point a, point b)
{
    return sqrt(pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
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
