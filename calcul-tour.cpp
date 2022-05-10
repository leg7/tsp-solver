#include "matrix.h"
#include "import.h"
#include "calcul-tour.h"
#include "tour.h"

#include <iostream>
#include <stdexcept>

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

	destination d;
	d.distance = 1000000000;

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
void make_greedy_tour(matrix &tsp, tour &t)
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

	update_tour(tsp, t);
}

void find_greedy_solution(solution &s, matrix &tsp, std::string instance)
{
	tour best;
	init_tour(best, 0, instance);

	make_greedy_tour(tsp, best);
	import_tour_coord(best, instance);
	append_to_solution(s, best);

	for (size_t i = 1; i < tsp.size + 1; ++i)
	{
		tour temp;
		init_tour(temp, i, instance);

		make_greedy_tour(tsp, temp);
		import_tour_coord(temp, instance);
		append_to_solution(s, temp);

		if (temp.length < best.length)
			best = temp;
	}

	import_tour_coord(best, instance);
	append_to_solution(s, best);
}

tour two_opt_swap(matrix tsp, tour t, size_t a, size_t b)
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

	update_tour(tsp, swapped);

	return swapped;
}

void two_opt_optimize(matrix tsp, tour &t)
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
				optimized = two_opt_swap(tsp, t, i, j);

				if (optimized.length < t.length)
				{
					t = optimized;
					improved = true;
					goto start_over;
				}
			}
	}
}

/* testé ok */
void find_greedy_optimized_solution(solution &s, matrix &tsp, std::string instance)
{
	tour best;
	init_tour(best, 0, instance);

	make_greedy_tour(tsp, best);
	import_tour_coord(best, instance);
	append_to_solution(s, best);

	two_opt_optimize(tsp, best);
	import_tour_coord(best, instance);
	append_to_solution(s, best);

	for (size_t i = 1; i < tsp.size + 1; ++i)
	{
		tour temp;
		init_tour(temp, i, instance);

		make_greedy_tour(tsp, temp);
		import_tour_coord(temp, instance);
		append_to_solution(s, temp);

		two_opt_optimize(tsp, temp);
		import_tour_coord(temp, instance);
		append_to_solution(s, temp);

		if (temp.length < best.length)
			best = temp;
	}

	import_tour_coord(best, instance);
	append_to_solution(s, best);
}
