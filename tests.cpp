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
