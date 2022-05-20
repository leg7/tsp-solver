#include <fstream>
#include <iostream>
#include <string>

#include "export.h"
#include "data.h"

void export_solution_header(std::string filename)
{
	int tmp;
}

void export_solution(solution s, std::string filename)
{
}

void make_gnuplot_datafile(std::string filename)
{
	std::ofstream file(filename);
	if (file.good())
		file << "";
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

void append_progressive_iteration(iteration i, std::string filename)
{
	std::ofstream file(filename, std::ios::app);
	if (file.good())
	{
		for (size_t j = 1; j < i.t.size; ++j)
		{
			file << std::endl << std::endl;
			for (size_t k = 0; k < j; ++k)
				file << i.t.data[k].coord.x << ' '
				     << i.t.data[k].coord.y << ' '
				     << i.t.data[k].id + 1 << std::endl;
		}
	}
}

void append_iteration(iteration i, std::string filename)
{
	std::ofstream file(filename, std::ios::app);
	if (file.good())
	{
		file << std::endl << std::endl;
		for (size_t j = 0; j < i.t.size; ++j)
			file << i.t.data[j].coord.x << ' '
			     << i.t.data[j].coord.y << ' '
			     << i.t.data[j].id + 1 << std::endl;
	}
}

void build_gnuplot_datafile(solution s, std::string filename)
{
	if (s == nullptr)
	{
		std::cerr << "Error: impossible d'exporter une solution vide !";
		return;
	}

	make_gnuplot_datafile(filename);
	std::ofstream file(filename, std::ios::app);
	if (file.good())
	{
		/* affichage "progressif" */
		append_progressive_iteration(*s, filename);
		s = s->next;

		while (s != nullptr)
		{
			/* affichage "brut" */
			append_iteration(*s, filename);
			s = s->next;
		}

	}
	else
		std::cout << "Erreur : le fichier " << filename
		          << "n'as pas pu être lu" << std::endl;
}
