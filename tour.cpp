#include "matrix.h"
#include "import.h"
#include "tour.h"
#include "calcul-tour.h"

#include <fstream>
#include <iostream>

void init_tour(tour &t, size_t start, std::string instance)
{
	t.length = 0;

	/* + 1 parcequ'il faut revenir au point de depart */
	t.size = get_tsp_size(instance) + 1;

	t.data = new destination[t.size];
	t.data[0].distance = 0;
	t.data[0].id       = start;
}

void update_tour_distances(tour &t, matrix tsp)
{
	t.data[0].distance = 0;
	for (size_t k = 1; k < t.size; ++k)
		t.data[k].distance = get_distance(tsp, t.data[k-1].id , t.data[k].id);
}

void update_tour_length(tour &t, matrix tsp)
{
	update_tour_distances(t, tsp);
	t.length = 0;
	for (size_t k = 0; k < t.size; ++k)
		t.length += t.data[k].distance;
}

void update_tour(tour &t, matrix tsp, std::string instance)
{
	update_tour_length(t, tsp);
	import_tour_coord(t, instance);
}

void print_tour(tour t)
{
	std::cout << "le tour serait d'une longueur de " << t.length
		<< " : \n\n";

	for (size_t k = 0; k < t.size; ++k)
	{
		if (k % 10 == 0)
			std::cout << "\n\n";
		if (k != t.size - 1)
			std::cout << "\t" << t.data[k].id + 1 << "\t==>";
		else
			std::cout << "\t" << t.data[k].id + 1 << "\n\n";
	}
	std::cout << std::endl;
}

void insert_to_solution(solution &s, tour t)
{
	solution temp = new iteration;
	temp->t = t;
	temp->next = s;
	s = temp;
}

void append_to_solution(solution &s, tour t)
{
	if (s == nullptr)
		insert_to_solution(s, t);
	else
		append_to_solution(s->next, t);
}

void print_solution_result(solution s)
{
	if (s == nullptr)
		return;

	if (s->next == nullptr)
		print_tour(s->t);
	else
		print_solution_result(s->next);
}

void make_gnuplot_datafile(std::string filename)
{
	std::ofstream file(filename+".dat");

	if (file.good())
		file << "";
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}

void build_gnuplot_datafile(solution s, std::string filename)
{
	make_gnuplot_datafile(filename);
	std::ofstream file(filename+".dat", std::ios::app);
	if (file.good())
	{
		for (size_t i = 1; i < s->t.size; ++i)
		{
			for (size_t j = 0; j < i; ++j)
				file << s->t.data[j].coord.x
					<< ' '
					<< s->t.data[j].coord.y
					<< ' '
					<< s->t.data[j].id + 1
					<< std::endl;

			file << std::endl << std::endl;
		}
		s = s->next;

		while (s != nullptr)
		{
			file << std::endl << std::endl;

			for (size_t k = 0; k < s->t.size; ++k)
				file << s->t.data[k].coord.x
					<< ' '
					<< s->t.data[k].coord.y
					<< ' '
					<< s->t.data[k].id + 1
					<< std::endl;

			s = s->next;
		}
	}
	else
		std::cout << "Erreur : le fichier " << filename
			<< "n'as pas pu être lu" << std::endl;
}
