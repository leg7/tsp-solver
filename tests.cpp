#include <iostream>
#include <filesystem>

#include "import.h"
#include "data.h"
#include "heuristics.h"
#include "tests.h"

bool test_export_solution_header(std::string filename)
{
	std::filesystem::path p(filename);
	filename = p.replace_extension(".solution");
	std::ifstream file(filename);

	if (!file.good())
		return false;

	std::string line = "";
	std::getline(file, line);
	if (line != "NAME : " + filename)
		return false;

	std::getline(file, line);
	std::string comment ="COMMENT : Best solution found by tsp-solver of ";
	if (line != comment + std::string(p.stem()))
		return false;

	std::getline(file, line);
	if (line != "TYPE : TOUR")
		return false;

	std::getline(file, line);
	p.replace_extension(".tsp");
	if (line != "DIMENSION : " + get_tsp_size(std::string(p)))
		return false;

	std::getline(file, line);
	if (line != "TOUR SECTION")
		return false;

	return true;
}

bool test_export_solution(solution s, std::string filename)
{
	if (!test_export_solution_header(filename))
		return false;

	return true;
}

bool test_tour_data(tour t)
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
	bool valid = (test_tour_data(t));
	delete[] t.data;

	return valid;
}

bool test_generation_data(generation g)
{
	for (size_t i = 0; i < g.size; ++i)
		if (!test_tour_data(g.member[i]))
		{
			std::cerr << "Tour data invalid\n";
			return false;
		}

	return true;
}

bool test_generation_lengths(generation g, matrix tsp)
{
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

	if (!test_generation_data(g))
		return false;

	if (!test_generation_lengths(g, tsp))
		return false;

	return true;
}

bool generation_is_sorted(generation g)
{
	for (size_t i = 0; i < g.size - 1; ++i)
		if (g.member[i].length > g.member[i + 1].length)
			return false;

	return true;
}

bool test_sort_generation(matrix tsp)
{
	generation g;
	make_random_generation(g, 1000, tsp);
	sort_generation(g);

	if (!generation_is_sorted(g))
		return false;

	if (!test_generation_data(g))
		return false;

	return true;
}

int main()
{
	/* ---------- *
	 * UNIT TESTS *
	 * ---------- */
	matrix test_matrix;
	std::string test_instance = "./tsp/bayg29.tsp";
	init_matrix(test_matrix, test_instance);
	import_tsp(test_matrix, test_instance);

	// test d'heuristiques genetiques
	bool g1 = test_make_random_tour(test_matrix);
	bool g2 = test_make_random_generation(test_matrix);
	/* bool g3 = test_sort_generation(test_matrix); */

	std::cout << "\n\nHEURISTICS\n\n";
	std::cout << "test_make_random_tour : " << (g1 ? "OK" : "NOT OK") << std::endl;
	std::cout << "test_make_random_generation : " << (g2 ? "OK" : "NOT OK") << std::endl;
	/* std::cout << "test_sort_generation : " << (g3 ? "OK" : "NOT OK") << std::endl; */

	// test d'export

	solution test_s = nullptr;
	find_greedy_optimized_solution(test_s, test_matrix, test_instance);

	bool e1 = test_export_solution_header(test_instance);

	std::cout << "\n\nEXPORT\n\n";
	std::cout << "test_export_solution_header : " << (e1 ? "OK" : "NOT OK") << std::endl;

	std::cout << std::endl;
	delete_matrix(test_matrix);

	return 0;
}
