#include <iostream>
#include <filesystem>
#include <string>

#include "import.h"
#include "export.h"
#include "data.h"
#include "heuristics.h"
#include "tests.h"

void print_test(bool test, std::string message)
{
	std::string error = "\033[1;97;101m";
	std::string blink = "\033[5;97;101m";
	std::string pass = "\033[1;32m";
	std::string end_color = "\033[0m";

	if (!test)
		std::cout << error + message;
	else
		std::cout << pass + message;
	std::cout << (test ? + "OK" : blink + "NOT OK")
		<< end_color << std::endl;
}

bool test_export_solution_header(solution s, std::string filename)
{
	export_solution_header(s, filename);

	std::filesystem::path p(filename);
	filename = std::string(p.replace_extension(".solution"));
	std::ifstream file(filename);

	std::string name = "test_export_solution_header: ";

	if (!file.good())
	{
		std::cerr << name + "Can't open file\n";
		return false;
	}

	std::string line = "";
	std::getline(file, line);
	if (line != "NAME : " + std::string(p.filename()))
	{
		std::cerr << name + "NAME incorrect\n";
		return false;
	}

	std::getline(file, line);
	std::string comment ="COMMENT : Best solution found by tsp-solver of ";
	if (line != comment + std::string(p.stem()))
	{
		std::cerr << name + "COMMENT incorrect\n";
		return false;
	}

	std::getline(file, line);
	if (line != "TYPE : TOUR")
	{
		std::cerr << name + "TYPE incorrect\n";
		return false;
	}

	std::getline(file, line);
	p.replace_extension(".tsp");
	std::string size = std::to_string(get_tsp_size(std::string(p)));
	if (line != "DIMENSION : " + size)
	{
		std::cerr << name + "DIMENSION incorrect\n";
		return false;
	}

	std::getline(file, line);
	size = std::to_string(get_solution_result_length(s));
	if (line != "LENGTH : " + size )
	{
		std::cerr << name + "LENGTH incorrect\n";
		return false;
	}

	std::getline(file, line);
	if (line != "TOUR SECTION")
	{
		std::cerr << name + "TOUR SECTION incorrect\n";
		return false;
	}

	return true;
}

bool test_export_solution_data(solution s, std::string filename)
{
	export_solution_data(s, filename);

	std::string name = "test_export_solution_data : ";

	if (s == nullptr)
	{
		std::cerr << name + "Solution empty\n";
		return false;
	}

	std::filesystem::path p(filename);
	filename = p.replace_extension(".solution");
	std::ifstream file(filename);
	file = go_to_target(filename, "TOUR SECTION", 0);

	while (s->next != nullptr)
		s = s->next;

	std::string line = "";
	for (size_t i = 0; i < s->t.size; ++i)
	{
		std::getline(file, line);
		if (std::to_string(s->t.data[i].id + 1) != line)
		{
			std::cerr << name + "Exported solution is not the best\n";
			return false;
		}
	}

	return true;
}

bool test_export_solution(solution s, std::string filename)
{
	export_solution(s, filename);

	if (!test_export_solution_header(s, filename))
		return false;
	if (!test_export_solution_data(s, filename))
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
	std::string title = "\033[1;97m";
	std::string end_color = "\033[0m";

	std::cout << title + "------------------\n" +
		"=== UNIT TESTS ===\n" +
		"------------------\n" + end_color;

	matrix tsp;
	std::string instance = "./tsp/bayg29.tsp";
	init_matrix(tsp, instance);
	import_tsp(tsp, instance);

	// test heuristiques
	std::cout << title + "\n\nHEURISTICS :\n\n" + end_color;

	bool g1 = test_make_random_tour(tsp);
	print_test(g1, "test_make_random_tour : ");

	bool g2 = test_make_random_generation(tsp);
	print_test(g2, "test_make_random_generation : ");

	// bool g3 = test_sort_generation(test_matrix);
	// print_test(g3, "test_sort_generation : ");


	// test expport
	solution s = nullptr;
	find_greedy_optimized_solution(s, tsp, instance);

	std::cout << title + "\n\nEXPORT :\n\n" + end_color;

	bool e1 = test_export_solution_header(s, instance);
	print_test(e1, "test_export_solution_header : ");
	bool e2 = test_export_solution_data(s, instance);
	print_test(e2, "test_export_solution_data : ");
	bool e3 = test_export_solution(s, instance);
	print_test(e3, "test_export_solution : ");

	// Cleanup
	std::cout << std::endl;
	delete_matrix(tsp);
	delete_solution(s);

	return 0;
}
