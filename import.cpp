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
		unsigned int x = tsp.n - 1;
		for (unsigned int i = 0; i < tsp.n - 1; ++i)
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

				tsp.m[i][j] = distance(a, b);
			}
		}
	}
}

/* testé ok */
void import_tsp_matrice(matrix &tsp, std::string filename)
{
	std::ifstream file(filename);
	if (file.good())
	{
		file = go_to("EDGE_WEIGHT_SECTION", target, 0);

		/* on remplit la matrice d'adjacence */
		unsigned int x = tsp.n - 1;
		for (unsigned int i = 0; i < tsp.n; ++i)
		{
			for (unsigned int j = 0; j < x; ++j)
			{
				std::string num;
				file >> num;
				tsp.m[i][j] = std::stoi(num);
			}
			--x;
		}
	}
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
