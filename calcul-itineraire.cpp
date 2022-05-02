#include "import.h"
#include "matrix.h"
#include "calcul-itineraire.h"

#include <iostream>
#include <stdexcept>

/* testé ok */
bool is_valid_path(matrix tsp, unsigned int origin, unsigned int town)
{
	if (town > tsp.n or town < 0 or origin > tsp.n or town < 0)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	if (origin == town)
		return false;

	if (origin > town)
	{
		unsigned int temp = origin;
		origin = town;
		town = temp;
	}

	if (tsp.m[origin][town-origin-1].checked == false)
		return true;
	else
		return false;
}

/* testé ok */
bool is_shortest_valid_path(matrix tsp, unsigned int origin, unsigned int town, destination d)
{
	return (is_valid_path(tsp,origin,town) and
		get_distance(tsp,origin,town) < d.distance and
		get_distance(tsp,origin,town) > 0);
}

/* testé ok */
double get_distance(matrix tsp, unsigned int a, unsigned int b)
{
	if (a > tsp.n or a < 0 or b > tsp.n or b < 0)
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
void mark_visited(matrix &tsp, unsigned int town)
{
	if (town > tsp.n or town < 0)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	for (unsigned int j = 0; j < tsp.n - town; ++j)
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
destination get_greedy_destination(matrix &tsp, unsigned int origin)
{
	if (origin > tsp.n or origin < 0)
		throw std::invalid_argument("Cette ligne n'appartient pas à la matrice");

	destination d;
	d.distance = 1000000000;

	for (unsigned int i = 0; i <= tsp.n; ++i)
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

	for (unsigned int k = 1; k < it.size; ++k)
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
	for (unsigned int k = 1; k < it.size; ++k)
		it.data[k].distance = get_distance(tsp, it.data[k - 1].num , it.data[k].num);
	
	for (unsigned int k = 0; k < it.size; ++k)
		it.length += it.data[k].distance;
}

void opt_swap(itinerary &it, unsigned int ville_1, unsigned int ville_2)
{
	destination aux = it.data[ville_1];
	it.data[ville_1] = it.data[ville_2];
	it.data[ville_2] = aux;
}
