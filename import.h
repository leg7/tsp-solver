#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

struct point
{
	unsigned int x;
	unsigned int y;
};

/*
 * Cette fonction retourne la distance entre deux points @a et @b
 * Elle sert a creer une matrice d'adjacence si l'instance passé en paramètre
 * n'en possède deja pas une
 */
double distance(point a, point b);

/*
 * Fonction qui renvoie une matrice dynamique d'adjacence créée à partir
 * d'une instance decrite en coordonées.
 * Le paramètre @file est le nom du fichier de l'instance.
 */
double** import_tsp_cord(std::string file);

/*
 * Fonction qui renvoie une matrice dynamique d'adjacence créée à partir
 * d'une instance decrite par une matrice d'adjacence.
 * Le paramètre @file est le nom du fichier de l'instance.
 */
double** import_tsp_matrice(std::string file);

/*
 * Cette fonction détermine le format du fichier de l'instance passé en param.
 * Une fois le format déterminé (matrice d'adjacence ou coordonées de points)
 * la fonction appelle la fonction d'import aproprié
 */
double** import_tsp(std::string file);
