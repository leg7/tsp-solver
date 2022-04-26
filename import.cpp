#include <fstream>
#include <cmath>
#include "import.h"

double distance(point a, point b)
{
    return sqrt( pow(b.y - a.y , 2) + pow(b.x - a.x , 2));
}

void import_fic_cord(double **t, std::string file);

void import_fic_matrice(double **t, std::string file);

void import(std::string s);
