#include "matrix.h"
#include "import.h"
#include "calcul-tour.h"
#include "tour.h"

#include <iostream>
#include <stdexcept>

size_t OPT_SWAPS = 0;

/* testé ok */
void swap(auto &a, auto &b)
{
	auto temp = a;
	a = b;
	b = temp;
}

/* testé ok */
double get_distance(matrix tsp, size_t start, size_t end)
{
	if (start > tsp.size or end > tsp.size)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	if (start == end)
		return 0;

	if (start > end)
		swap(start, end);

	return tsp.data[start][end-start-1].distance;
}

/* testé ok */
bool is_valid_path(matrix tsp, size_t start, size_t end)
{
	if (end > tsp.size or start > tsp.size)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	if (start == end)
		return false;

	if (start > end)
		swap(start, end);

	return (tsp.data[start][end-start-1].visited == false);
}

/* testé ok */
void mark_visited(matrix &tsp, size_t city)
{
	if (city > tsp.size)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	for (size_t j = 0; j < tsp.size - city; ++j)
		tsp.data[city][j].visited = true;

	/* min diagonale */
	if (city > 0)
	{
		int i = city - 1;
		int j = 0;
		while (i >= 0)
		{
			tsp.data[i][j].visited = true;
			--i;
			++j;
		}
	}
}

/* testé ok */
destination get_greedy_destination(matrix &tsp, size_t start)
{
	if (start > tsp.size)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	double double_max = 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0000000000000000;

	destination d;
	d.distance = double_max;

	for (size_t i = 0; i <= tsp.size; ++i)
	{
		if (is_valid_path(tsp, start, i) and
		    get_distance(tsp, start, i) < d.distance and
		    get_distance(tsp, start, i) > 0)
		{
			d.distance = get_distance(tsp, start, i);
			d.id = i;
		}
	}

	return d;
}

/* testé ok */
void make_greedy_tour(tour &t, matrix &tsp, std::string instance)
{
	init_matrix_status(tsp);

	for (size_t k = 1; k < t.size - 1; ++k)
	{
		t.data[k] = get_greedy_destination(tsp, t.data[k-1].id);
		t.length += t.data[k].distance;
		mark_visited(tsp, t.data[k-1].id);
	}

	/* Pour terminer le cycle hamiltonien */
	size_t end = t.size - 1;
	t.data[end].id = t.data[0].id;
	t.data[end].distance = get_distance(tsp, t.data[end-1].id, t.data[end].id);

	update_tour(t, tsp, instance);
}

void find_greedy_solution(solution &s, matrix &tsp, std::string instance)
{
	tour best;
	init_tour(best, 0, instance);

	make_greedy_tour(best, tsp, instance);
	insert_tour_to_solution_tail(best, s);

	for (size_t i = 1; i < tsp.size + 1; ++i)
	{
		tour temp;
		init_tour(temp, i, instance);

		make_greedy_tour(temp, tsp, instance);
		insert_tour_to_solution_tail(temp, s);

		if (temp.length < best.length)
			best = temp;
	}

	insert_tour_to_solution_tail(best, s);
}

tour two_opt_swap(tour t, matrix tsp, size_t a, size_t b)
{
	if (a == b or a >= t.size or b >= t.size)
		throw std::invalid_argument("ta mère");

	tour swapped;
	swapped.size = t.size;
	swapped.data = new destination[swapped.size];

	/* On met le debut dans l'ordre */
	size_t i = 0;
	while (i < a)
	{
		swapped.data[i].id = t.data[i].id;
		++i;
	}

	/* Une fois arrive à "a" on les mets à l'envers */
	size_t j = b;
	while (j >= a)
	{
		swapped.data[i].id = t.data[j].id;

		if (j == 0)
		{
			++i; // cas particulier si l'on inverse le tour
			break;
		}
		--j;
		++i;
	}

	/* Puis on mets le reste */
	while (i < swapped.size)
	{
		swapped.data[i].id = t.data[i].id;
		++i;
	}

	/* on ne mets pas a jour les coordonées tout de suite
	 * parceque ça mets bcp trop de temps */
	update_tour_length(swapped, tsp);
	++OPT_SWAPS;
	return swapped;
}

void two_opt_optimize(tour &t, matrix tsp, std::string instance)
{
	tour optimized;
	optimized.size = t.size;
	optimized.data = new destination[t.size];

	bool improved = true;
	while (improved)
	{
		improved = false;

		start_over:
		for (size_t i = 1; i < t.size - 2; ++i)
			for (size_t j = i + 1; j < t.size - 1; ++j)
			{
				optimized = two_opt_swap(t, tsp, i, j);

				if (optimized.length < t.length)
				{
					t = optimized;
					improved = true;
					goto start_over;
				}
			}
	}
	import_tour_coord(t, instance);
}

/* testé ok */
void find_greedy_optimized_solution(solution &s, matrix &tsp, std::string instance)
{
	/* init best */
	tour best;
	init_tour(best, 0, instance);

	make_greedy_tour(best, tsp, instance);
	insert_tour_to_solution_tail(best, s);

	two_opt_optimize(best, tsp, instance);
	insert_tour_to_solution_tail(best, s);

	/* find new best */
	for (size_t i = 1; i < tsp.size + 1; ++i)
	{
		tour temp;
		init_tour(temp, i, instance);

		make_greedy_tour(temp, tsp, instance);
		insert_tour_to_solution_tail(temp, s);

		two_opt_optimize(temp, tsp, instance);
		insert_tour_to_solution_tail(temp, s);

		if (temp.length < best.length)
			best = temp;
	}

	insert_tour_to_solution_tail(best, s);
}
