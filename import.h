#pragma once

#include <string>

struct point
{
	int x;
	int y;
};

/* Fonction qui retourne une matrie d'adjacence @m vide de taille @n */
double** build_matrix(double **m, unsigned int n);

/*
 * Procedure qui affiche une matrice d'adjacence @m
 * pour une instance de taille @n
 */
void print_matrix(double **m, unsigned int n);

/*
 * Fonction qui retourne la taille d'une instance pour pouvoir créer une
 * matrcie de taille adapté.
 * Le paramètre s'agit du nom du fichier de l'instance
 */
unsigned int get_tsp_size(std::string file);

/*
 * Cette fonction retourne la distance entre deux points @a et @b
 * Elle sert a creer une matrice d'adjacence si l'instance passé en paramètre
 * n'en possède deja pas une
 */
double distance(point a, point b);

/*
 * Cette fonction retourne un ifstreamn à la position des paramètres.
 * @file est le nom du fichier.
 * @target est la position de départ.
 * @n est le nombre de lignes à sauter après être arriver à @target.
 */
std::ifstream go_to(std::string file, std::string target, unsigned int n);

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
