#include <iostream>
#include <limits>
#include <stdexcept>

#include "heuristics.h"
#include "data.h"
#include "import.h"

size_t OPT_SWAPS = 0;

void swap(auto &a, auto &b)
{
	auto temp = a;
	a = b;
	b = temp;
}

size_t get_distance(matrix tsp, size_t start, size_t end)
{
	if (start > tsp.size or end > tsp.size)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	if (start == end)
		return 0;

	if (start > end)
		swap(start, end);

	return tsp.data[start][end-start-1].distance;
}

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

destination get_greedy_destination(matrix &tsp, size_t start)
{
	if (start > tsp.size)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	size_t size_t_max = std::numeric_limits<size_t>::max();

	destination d;
	d.distance = size_t_max;

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
		throw std::invalid_argument("2-opt-swap impossible");

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
	update_tour_distances(swapped, tsp);
	update_tour_length(swapped);
	++OPT_SWAPS;
	return swapped;
}

void two_opt_optimize(tour &t, matrix tsp, std::string instance)
{
	bool improved = true;
	while (improved)
	{
		improved = false;

		start_over:
		for (size_t i = 1; i < t.size - 2; ++i)
			for (size_t j = i + 1; j < t.size - 1; ++j)
			{
				tour optimized = two_opt_swap(t, tsp, i, j);

				if (optimized.length < t.length)
				{
					t = optimized;
					improved = true;
					goto start_over;
				}
				delete[] optimized.data;
			}
	}
	import_tour_coord(t, instance);
}

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

bool should_make_random_swap(int ti, int t)
{
	float probability = rand() % ti;
	return (probability < t);
}

size_t pick_random_neighbor(size_t i, tour t)
{
	size_t n   = 0, // le voisin choisi
	       prv = 0, // le voisin prècedant
	       nxt = 0; // le voisin suivant

	if (i == 1)
	{
		prv = t.size - 2;
		nxt = 2;
	}
	else if (i == t.size - 2)
	{
		prv = t.size - 3;
		nxt = 1;
	}
	else
	{
		prv = i - 1;
		nxt = i + 1;
	}
	n = (rand() % 2 == 0) ? prv : nxt;

	return n;
}

void swap_random_neighbors(tour &t)
{
	size_t i = rand() % (t.size - 2) + 1;
	size_t j = pick_random_neighbor(i, t);
	swap(t.data[i].id, t.data[j].id);
}

void simmulated_annealing(solution &s, matrix &tsp, std::string instance)
{
	tour b;
	init_tour(b, rand() % tsp.size + 1, instance);
	make_greedy_tour(b, tsp, instance);

	int ti = 300,
	    t  = ti;
	while (t >= 0)
	{
		if (should_make_random_swap(ti, t))
		{
			swap_random_neighbors(b);
			update_tour(b, tsp, instance);
		}
		else
		{
			for (size_t i = 1; i < b.size - 2; ++i)
				for (size_t j = i + 1; j < b.size - 1; ++j)
				{
					tour tmp = two_opt_swap(b, tsp, i, j);
					if (tmp.length < b.length)
					{
						b = tmp;
						import_tour_coord(b, instance);
					}
					/* delete[] tmp.data; */
				}
		}
		insert_tour_to_solution_tail(b, s);
		--t;
	}
	two_opt_optimize(b, tsp, instance);
	insert_tour_to_solution_tail(b, s);
}

void find_simmulated_annealing_solution(solution &s, matrix &tsp, std::string instance)
{
	simmulated_annealing(s, tsp, instance);
	for (size_t i = 0; i < 30; ++i)
	{
		solution tmp = nullptr;
		simmulated_annealing(tmp, tsp, instance);

		if (get_solution_result_length(tmp) < get_solution_result_length(s))
		{
			delete_solution(s);
			s = tmp;
		}
	}
}
