#include <iostream>

#include "import.h"
#include "data.h"
#include "heuristics.h"

bool tour_data_is_valid(tour t)
{
	if (t.data[0].id != t.data[t.size - 1].id)
	{
		std::cerr << "Tour invalid start != end\n";
		return false;
	}

	for (size_t i = 1; i < t.size - 2; ++i)
		for (size_t j = i + 1; j < t.size - 1; ++j)
			if (t.data[i].id == t.data[j].id and
			    t.data[i].id < t.size - 1)
			{
				std::cerr << "Tour data invalid";
				return false;
			}

	return true;
}

bool test_make_random_tour(matrix tsp)
{
	tour t = make_random_tour(tsp);
	return (tour_data_is_valid(t));
	delete[] t.data;
}

bool test_make_random_generation(matrix tsp)
{
	generation g;
	size_t test_size = 100;
	make_random_generation(g, test_size, tsp);

	if (g.size != test_size)
	{
		std::cerr << "Generation size invalid\n";
		return false;
	}

	if (g.member[0].size != tsp.size + 2)
	{
		std::cerr << "Member size invalid\n";
		return false;
	}

	for (size_t i = 0; i < g.size; ++i)
		if (!tour_data_is_valid(g.member[i]))
		{
			std::cerr << "Tour data invalid\n";
			return false;
		}

	for (size_t i = 0; i < g.size; ++i)
	{
		size_t backup = g.member[i].length;
		update_tour_distances(g.member[i], tsp);
		update_tour_length(g.member[i]);
		if (backup != g.member[i].length)
		{
			std::cerr << "Invalid tour length\n";
			return false;
		}
	}



	return true;
}

bool test_sort_generation(matrix tsp)
{
	generation g;
	make_random_generation(g, 1000, tsp);
	sort_generation(g);

	for (size_t i = 0; i < g.size - 1; ++i)
		if (g.member[i].length > g.member[i + 1].length)
			return false;

	for (size_t i = 0; i < g.size; ++i)
		if (!tour_data_is_valid(g.member[i]))
		{
			std::cerr << "Tour data invalid\n";
			return false;
		}

	return true;
}
