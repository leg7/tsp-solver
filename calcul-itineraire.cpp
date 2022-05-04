#include "matrix.h"
#include "import.h"
#include "calcul-itineraire.h"
#include "itineraire.h"

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
void make_greedy_itinerary(matrix &tsp, itinerary &it)
{
	init_matrix_status(tsp);

	for (size_t k = 1; k < it.size - 1; ++k)
	{
		it.data[k] = get_greedy_destination(tsp, it.data[k-1].id);
		it.length += it.data[k].distance;
		mark_visited(tsp, it.data[k-1].id);
	}

	/* Pour terminer le cycle hamiltonien */
	size_t end = it.size - 1;
	it.data[end].id = it.data[0].id;
	it.data[end].distance = get_distance(tsp, it.data[end-1].id, it.data[end].id);

	update_itinerary(tsp, it);
}

itinerary two_opt_swap(matrix tsp, itinerary it, size_t a, size_t b)
{
	if (a == b or a >= it.size or b >= it.size)
		throw std::invalid_argument("ta mère");

	itinerary swapped;
	swapped.size = it.size;
	swapped.data = new destination[swapped.size];

	/* On met le debut dans l'ordre */
	size_t i = 0;
	while (i < a)
	{
		swapped.data[i].id = it.data[i].id;
		++i;
	}

	/* Une fois arrive à "a" on les mets à l'envers */
	size_t j = b;
	while (j >= a)
	{
		swapped.data[i].id = it.data[j].id;

		if (j == 0)
		{
			++i; // cas particulier si l'on inverse l'itineraire
			break;
		}
		--j;
		++i;
	}

	/* Puis on mets le reste */
	while (i < swapped.size)
	{
		swapped.data[i].id = it.data[i].id;
		++i;
	}

	update_itinerary(tsp, swapped);

	return swapped;
}

void two_opt_optimize(matrix tsp, itinerary &it)
{
	itinerary optimized;
	optimized.size = it.size;
	optimized.data = new destination[it.size];

	bool improved = true;
	while (improved)
	{
		improved = false;

		start_over:
		for (size_t i = 1; i < it.size - 2; ++i)
			for (size_t j = i + 1; j < it.size - 1; ++j)
			{
				optimized = two_opt_swap(tsp, it, i, j);

				if (optimized.length < it.length)
				{
					it = optimized;
					improved = true;
					goto start_over;
				}
			}
	}
}

/* testé ok */
itinerary find_best_optimized_greedy_itinerary(matrix &tsp, std::string instance)
{
	itinerary best;
	init_itinerary(best, 0, instance);
	make_greedy_itinerary(tsp, best);
	/* append_itinerary */

	two_opt_optimize(tsp, best);
	/* append_itinerary */

	for (size_t i = 1; i < tsp.size + 1; ++i)
	{
		itinerary temp;
		init_itinerary(temp, i, instance);
		make_greedy_itinerary(tsp, temp);
		/* append_itinerary */

		two_opt_optimize(tsp, temp);
		/* append_itinerary */

		if (temp.length < best.length)
			best = temp;
	}

	return best;
	/* append_itinerary */
}

