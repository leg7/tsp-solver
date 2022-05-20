#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#include "heuristics.h"
#include "data.h"
#include "import.h"

void init_matrix_size(matrix &tsp, std::string filename)
{
	tsp.size = get_tsp_size(filename);
	// parceque la derniere ville ne figure pas dans la matrice d'adjacence
	--tsp.size;
}

void init_matrix_distances(matrix &tsp)
{
	size_t x = tsp.size;
	for (size_t i = 0; i < tsp.size; ++i)
	{
		for (size_t j = 0; j < x; ++j)
			tsp.data[i][j].distance = 0;
		--x;
	}
}

void init_matrix_status(matrix &tsp)
{
	size_t x = tsp.size;
	for (size_t i = 0; i < tsp.size; ++i)
	{
		for (size_t j = 0; j < x; ++j)
			tsp.data[i][j].visited = false;
		--x;
	}
}

void init_matrix_data(matrix &tsp)
{
	init_matrix_distances(tsp);
	init_matrix_status(tsp);
}

void init_matrix(matrix &tsp, std::string filename)
{
	init_matrix_size(tsp, filename);
	if (tsp.size > 0)
	{
		tsp.data = new matrix_data*[tsp.size];

		size_t x = tsp.size;
		for (size_t i = 0; i < tsp.size; ++i)
		{
			tsp.data[i] = new matrix_data[x];
			--x;
		}
		init_matrix_data(tsp);
	}
	else
		std::cout << "\nErreur critique : la taille de votre instance "
			<< "est <= 0 donc la matrice n'as pas été faite.\n";
}

void print_matrix_status(matrix &tsp)
{
	size_t x = tsp.size;
	for (size_t i = 0; i < tsp.size; ++i)
	{
		for (size_t j = 0; j < x; ++j)
			std::cout << tsp.data[i][j].visited << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print_matrix_distance(matrix tsp)
{
	size_t x = tsp.size;
	for (size_t i = 0; i < tsp.size; ++i)
	{
		for (size_t j = 0; j < x;  ++j)
			std::cout << tsp.data[i][j].distance << ' ';
		--x;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void delete_matrix(matrix &tsp)
{
	for (size_t i = 0; i < tsp.size; ++i)
		delete[] tsp.data[i];
	delete[] tsp.data;
}

void init_tour_length(tour &t)
{
	t.length = 0;
}

void init_tour_size(tour &t, std::string instance)
{
	/* + 1 parcequ'il faut revenir au point de depart */
	t.size = get_tsp_size(instance) + 1;
}

void init_tour_size(tour &t, matrix tsp)
{
	t.size = tsp.size + 2;
}

void init_tour_data(tour &t, size_t start)
{
	t.data = new destination[t.size];
	t.data[0].distance = 0;
	t.data[0].id       = start;

	for (size_t i = 1; i < t.size; ++i)
	{
		t.data[i].distance = 0;
		t.data[i].id       = 0;
		t.data[i].coord.x  = 0;
		t.data[i].coord.y  = 0;
	}
}

void init_tour(tour &t, size_t start, std::string instance)
{
	init_tour_length(t);
	init_tour_size(t, instance);
	init_tour_data(t, start);
}

void init_tour(tour &t, size_t start, matrix tsp)
{
	init_tour_length(t);
	init_tour_size(t, tsp);
	init_tour_data(t, start);
}

void update_tour_distances(tour &t, matrix tsp)
{
	t.data[0].distance = 0;
	for (size_t k = 1; k < t.size; ++k)
		t.data[k].distance = get_distance(tsp, t.data[k-1].id , t.data[k].id);
}

void update_tour_length(tour &t)
{
	t.length = 0;
	for (size_t k = 0; k < t.size; ++k)
		t.length += t.data[k].distance;
}

void update_tour(tour &t, matrix tsp, std::string instance)
{
	update_tour_distances(t, tsp);
	update_tour_length(t);
	import_tour_coord(t, instance);
}

void print_tour(tour t)
{
	std::cout << "le tour serait d'une longueur de " << t.length
		<< " : \n\n";

	for (size_t k = 0; k < t.size; ++k)
	{
		if (k % 7 == 0 and k != 0)
			std::cout << "\n\n";
		if (k != t.size - 1)
			std::cout << "\t" << t.data[k].id + 1 << "\t==>";
		else
			std::cout << "\t" << t.data[k].id + 1 <<  "\n\n";

		std::cout.flush();
		usleep(30000);
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

size_t get_solution_result_length(solution s)
{
	if (s->next != nullptr)
		return get_solution_result_length(s->next);
	else
		return s->t.length;
}

void delete_iteration(solution &s)
{
	solution next = s->next;
	delete s;
	s = next;
}

void delete_solution(solution &s)
{
	while (s != nullptr)
		delete_iteration(s);
}

/*
 * Cette fonction sert a supprimer des iterations redondantes
 * de la solution pour que l'animation gnuplot soit coherente
 */
void delete_duplicates(solution &s)
{
	if (s->next != nullptr)
	{
		bool twin = true;
		size_t i = 0;
		while (i < s->t.size and twin)
		{
			if (s->t.data[i].id != s->next->t.data[i].id)
				twin = false;
			++i;
		}

		if (twin == true)
		{
			delete_iteration(s);
			delete_duplicates(s);
		}
		else
			delete_duplicates(s->next);
	}
}
