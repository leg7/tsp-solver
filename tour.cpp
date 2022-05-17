#include "matrix.h"
#include "import.h"
#include "tour.h"
#include "calcul-tour.h"

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

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
	std::string color = "\033[";
	std::string end_color = "\033[0m";

	std::cout << "le tour serait d'une longueur de " << t.length
		<< " : \n\n";

	for (size_t k = 0; k < t.size; ++k)
	{
		if (k % 7 == 0 and k != 0)
			std::cout << "\n\n";

		if (k != t.size - 1)
		{
			clock_t goal = 100000 + clock();
			while (goal > clock());
			std::cout << "\t" << t.data[k].id + 1 << "\t==>";
		}
		else
			std::cout << "\t" << t.data[k].id + 1 << end_color + "\n\n";
	}
	std::cout << std::endl;
}

void insert_tour_to_solution_head(tour t, solution &s)
{
	solution temp = new iteration;
	temp->t = t;
	temp->next = s;
	s = temp;
}

void insert_tour_to_solution_tail(tour t, solution &s)
{
	if (s == nullptr)
		insert_tour_to_solution_head(t, s);
	else
		insert_tour_to_solution_tail(t, s->next);
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
