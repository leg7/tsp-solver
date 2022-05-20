# tsp-solver 🗺

Cet outil permet de résoudre des instances du problème du
voyageur de commerce suivant la spécification tsplib95.

>En informatique, le problème du voyageur de commerce, ou problème du commis
voyageur, est un problème d'optimisation qui consiste à déterminer, étant donné
une liste de villes et les distances entre toutes les paires de villes, le plus
court circuit qui passe par chaque ville une et une seule fois.

[Extrait de wikipedia](https://wikiless.org/wiki/Probl%C3%A8me_du_voyageur_de_commerce?lang=fr)

## Fonctionnalités

* Resoudre des instances tsplib95 de type :
	* EDGE_WEIGHT_TYPE : ATT
	* EDGE_WEIGHT_TYPE: EXPLICIT
	  EDGE_WEIGHT_FORMAT: UPPER_ROW
* Plusieurs algorithmes/heuristiques de resolution differents
	* Algorithme glouton (greedy)
	* Algorithme de recuit simulé (simmulated_annealing)
	* Algorithme génétique (WIP)
	* Algorithme des fourmis (Non implementé)
	* Optimisation de tour LK (Lin–Kernighan) (2-opt)
* Interface TUI/CLI
	* Mode interactif (option `-i`)
	* Mode quiet (option `-q`)
* animation de la solution avec gnuplot
* Export de la solution dans fichier txt

## Dépendances

L'application à été développé avec ces outils. Des anciennes versions
pourraient probablement marcher.

* gnuplot-5.4.3 compilé avec support pour gd (pour l'animation)
* xdg-utils bien configuré évidemment (pour ouvrir le gif automatiquement)
* gcc-11.2.1_20220115
* glibc-2.34-r13
* make-4.3
* un système GNU/Linux

## Guide d'installation

Depuis un terminal avec connexion à internet entrez ces commandes.

```
git clone https://git.leonardgomez.xyz/leg7/tsp-solver
cd tsp-solver
make
```

Les tests seront compilés et exécutés, puis tsp-solver sera compilé.
**Rien n'est installé sur le système donc il faut appeler l'exécutable depuis
le dossier tsp-solver.**

*Exemple*

```
./tsp-solver [OPTION] tspinstance.tsp
```

## FAQ

* **Où sont stockés les résultats et gif créés par le programme ?**

Ils sont au même endroit que le fichier d'instance passé en paramètre.

* **Pourquoi l'algorithme génétique et celui des fourmis ne marchent pas?**

Ces algorithmes sont en cours de développement.

* **Ça prend longtemps de faire le gif avec gnuplot, est-ce que le programme est buggé?**

Non. Faire un gif avec gnuplot peut prendre un temps considérable.

* **Certaines instances TSPLIB95 ne marchent pas !?!??? 🦍**

Tous les types d'instances ne sont pas encore supportés.
