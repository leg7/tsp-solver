#pragma once

#include "matrix.h"
#include "calcul-itineraire.h"

#include <string>

/*
 * Fonction qui retourne la taille d'une instance pour pouvoir créer une
 * matrcie de taille adapté.
 * Le paramètre s'agit du nom du fichier de l'instance
 */
size_t get_tsp_size(std::string filename);

/*
 * Cette fonction retourne un ifstreamn à la position des paramètres.
 * @file est le nom du fichier.
 * @target est la position de départ.
 * @n est le nombre de lignes à sauter après être arriver à @target.
 */
std::ifstream go_to_target(std::string filename, std::string target, size_t n);

/* Fonction qui renvoie si @target est dans le fichier @filename */
bool find_target(std::string filename, std::string target);

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
 * Procedure qui rempli une matrice d'adjacence @tsp
 * avec les données d'une instance @filename
 */
void import_tsp_matrix(matrix &tsp, std::string filename);

/*
 * Procedure qui determine le format des données de l'instance tsp et appelle
 * la procedure de creation de matrice approprié.
 * Cette procedure depend de toutes les autres fonctions et procedure du
 * fichier apart print_matrix
 */
void import_tsp(matrix &tsp, std::string filename);

/* Procedure qui remplit les coordonnées d'un point */
void import_destination_coord(destination &d, std::string target, std::string filename);

/* Procedure qui trouve les coordonnées des points d'un itinéraire @it */
void import_itinerary_coord(itinerary &it, std::string instance);
