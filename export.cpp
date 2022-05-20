#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "import.h"
#include "export.h"
#include "data.h"

// Sert a exporter l'entete d'un fichier .solution
void export_solution_header(solution s, std::string filename)
{
	std::filesystem::path p(filename);
	std::string export_file = std::string(p.replace_extension(".solution"));

	std::ofstream file(export_file);
	if (file.good())
	{
		file << "NAME : " + std::string(p.filename()) + '\n'
			<< "COMMENT : Best solution found by tsp-solver of "
			<< std::string(p.stem()) + '\n'
			<< "TYPE : TOUR\n"
			<< "DIMENSION : " << get_tsp_size(filename) << '\n'
			<< "LENGTH : " << get_solution_result_length(s) << '\n'
			<< "TOUR SECTION\n";
	}
}

// Sert a exporter le meilleure tour dans le fichier .solution
void export_solution_data(solution s, std::string filename)
{
	std::filesystem::path p(filename);
	filename = p.replace_extension(".solution");
	std::ofstream file(filename, std::ios::app);
	if (file.good())
	{
		go_to_target(filename, "TOUR SECTION", 1);

		while (s->next != nullptr)
			s = s->next;
		for (size_t i = 0; i < s->t.size; ++i)
			file << s->t.data[i].id + 1 << '\n';
	}
}

void export_solution(solution s, std::string filename)
{
	export_solution_header(s,filename);
	export_solution_data(s,filename);
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

// Exporte une iteration pour que gnuplot l'affiche de manière animé
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

// Exporte une iteration pour que gnuplot ne l'animé pas
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
