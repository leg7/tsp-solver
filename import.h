#pragma once

#include <string>

struct point
{
	int x;
	int y;
};

struct matrix
{
	double **m;
	unsigned int n;
};

/*
 * Fonction qui retourne la taille d'une instance pour pouvoir créer une
 * matrcie de taille adapté.
 * Le paramètre s'agit du nom du fichier de l'instance
 */
int get_tsp_size(std::string filename);

/*
 * Procedure qui construit une matrice d'adjacence vide passé en paramètere
 * (@tsp). Cette fonction determine le taille de la matrice grâce a la fonction
 * get_tsp_size ci dessus.
 */
void build_matrix(matrix &tsp, std::string filename);

/* Procedure qui affiche une matrice d'adjacence @tsp */
void print_matrix(matrix tsp);

/*
 * Cette fonction retourne un ifstreamn à la position des paramètres.
 * @file est le nom du fichier.
 * @target est la position de départ.
 * @n est le nombre de lignes à sauter après être arriver à @target.
 */
std::ifstream go_to(std::string filename, std::string target, unsigned int n);

/*
 * Cette fonction retourne la distance entre deux points @a et @b
 * Elle sert a creer une matrice d'adjacence
 */
double distance(point a, point b);

/*
 * Procedure qui importe des données d'une instance tsp sous forme de
 * coordonées de points dans une matrice @tsp
 */
void import_tsp_cord(matrix &tsp, std::string filename);

/*
 * Fonction qui renvoie une matrice dynamique d'adjacence créée à partir
 * d'une instance decrite par une matrice d'adjacence.
 * Le paramètre @file est le nom du fichier de l'instance.
 */
double** import_tsp_matrice(std::string filename);

/*
 * Cette fonction détermine le format du fichier de l'instance passé en param.
 * Une fois le format déterminé (matrice d'adjacence ou coordonées de points)
 * la fonction appelle la fonction d'import aproprié
 */
double** import_tsp(std::string filename);
