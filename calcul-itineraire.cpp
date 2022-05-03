#include "import.h"
#include "matrix.h"
#include "calcul-itineraire.h"

#include <iostream>
#include <stdexcept>

void swap(auto &a, auto &b)
{
	auto temp = a;
	a = b;
	b = temp;
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
bool is_shortest_valid_path(matrix tsp, size_t start, size_t end, destination d)
{
	return (is_valid_path(tsp, start, end) and
		get_distance(tsp, start, end) < d.distance and
		get_distance(tsp, start, end) > 0);
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
		if (is_shortest_valid_path(tsp, start, i, d))
		{
			d.distance = get_distance(tsp, start, i);
			d.id = i;
		}

	return d;
}

/* testé ok */
void make_greedy_itinerary(matrix &tsp, itinerary &it)
{
	init_matrix_status(tsp);

	for (size_t k = 1; k < it.size; ++k)
	{
		it.data[k] = get_greedy_destination(tsp, it.data[k-1].id);
		it.length += it.data[k].distance;
		mark_visited(tsp, it.data[k-1].id);
	}
}

void update_itinerary(itinerary &it, matrix tsp)
{
	it.data[0].distance = 0;
	for (size_t k = 1; k < it.size; ++k)
		it.data[k].distance = get_distance(tsp, it.data[k-1].id , it.data[k].id);

	it.length = 0;
	for (size_t k = 0; k < it.size; ++k)
		it.length += it.data[k].distance;
}

itinerary two_opt_swap(itinerary it, size_t a, size_t b, matrix tsp)
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

	update_itinerary(swapped,tsp);

	return swapped;
}

void two_opt_optimize(itinerary &it, matrix tsp)
{
	itinerary optimized;
	optimized.size = it.size;
	optimized.data = new destination[it.size];

	bool improved = true;
	while (improved)
	{
		improved = false;

		start_over:
		for (size_t i = 0; i < it.size - 1; ++i)
			for (size_t j = i + 1; j < it.size; ++j)
			{
				optimized = two_opt_swap(it, i, j, tsp);

				if (optimized.length < it.length)
				{
					it = optimized;
					improved = true;
					goto start_over;
				}
			}
	}
}
