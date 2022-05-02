#include "import.h"
#include "matrix.h"
#include "calcul-itineraire.h"

#include <iostream>
#include <stdexcept>

/* testé ok */
bool is_valid_path(matrix tsp, size_t origin, size_t town)
{
	if (town > tsp.n or origin > tsp.n)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	if (origin == town)
		return false;

	if (origin > town)
	{
		size_t temp = origin;
		origin = town;
		town = temp;
	}

	if (tsp.m[origin][town-origin-1].checked == false)
		return true;
	else
		return false;
}

/* testé ok */
bool is_shortest_valid_path(matrix tsp, size_t origin, size_t town, destination d)
{
	return (is_valid_path(tsp,origin,town) and
		get_distance(tsp,origin,town) < d.distance and
		get_distance(tsp,origin,town) > 0);
}

/* testé ok */
double get_distance(matrix tsp, size_t a, size_t b)
{
	if (a > tsp.n or b > tsp.n)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	if (b == a)
		return 0;

	if (b < a)
	{
		double temp = b;
		b = a;
		a = temp;
	}
	return tsp.m[a][b-a-1].distance;
}

/* testé ok */
void mark_visited(matrix &tsp, size_t town)
{
	if (town > tsp.n)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	for (size_t j = 0; j < tsp.n - town; ++j)
		tsp.m[town][j].checked = true;

	/* min diagonale */
	if (town > 0)
	{
		int i = town - 1;
		int j = 0;
		while (i >= 0)
		{
			tsp.m[i][j].checked = true;
			--i;
			++j;
		}
	}
}

/* testé ok */
destination get_greedy_destination(matrix &tsp, size_t origin)
{
	if (origin > tsp.n)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	destination d;
	d.distance = 1000000000;

	for (size_t i = 0; i <= tsp.n; ++i)
		if (is_shortest_valid_path(tsp,origin,i,d))
		{
			d.distance = get_distance(tsp,origin,i);
			d.num = i;
		}

	return d;
}

/* testé ok */
void make_greedy_itinerary(matrix &tsp, itinerary &it)
{
	init_matrix_status(tsp);

	for (size_t k = 1; k < it.size; ++k)
	{
		it.data[k] = get_greedy_destination(tsp, it.data[k-1].num);
		mark_visited(tsp, it.data[k-1].num);
		it.length += it.data[k].distance;
		/* print_matrix_status(tsp); */
		/* std::cout << t[i] << std::endl << std::endl; */
	}
}

void update_itinerary(itinerary &it, matrix tsp)
{
	it.data[0].distance = 0;
	for (size_t k = 1; k < it.size; ++k)
		it.data[k].distance = get_distance(tsp, it.data[k - 1].num , it.data[k].num);

	it.length = 0;
	for (size_t k = 0; k < it.size; ++k)
		it.length += it.data[k].distance;
}

itinerary two_opt_swap(itinerary it, size_t a, size_t b, matrix tsp)
{
	if (a == b)
		throw std::invalid_argument("ta mère");

	itinerary swapped;
	swapped.size = it.size;
	swapped.data = new destination[swapped.size];

	/* On met le debut dans l'ordre */
	size_t i = 0;
	while (i < a)
	{
		swapped.data[i].num = it.data[i].num;
		++i;
	}

	/* Une fois arrive à "a" on les mets à l'envers */
	size_t j = b;
	while (j >= a)
	{
		swapped.data[i].num = it.data[j].num;

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
		swapped.data[i].num = it.data[i].num;
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
		for (size_t i = 0; i <= it.size - 1; ++i)
			for (size_t j = i + 1; j <= it.size; ++j)
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
