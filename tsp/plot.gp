# Pour utiliser ce script appler le dans le terminal en precisant
# la variable filename avec le nom du fichier, par exemple:
# gnuplot -e "filename = \"bayg29.tsp.out\"" plot.gp

set term gif animate delay 10 size 1200,800
set output filename . ".gif"
# set output ".gif"

stats filename name "A"
set xrange [A_min_x - 0.05*A_max_x:A_max_x + 0.05*A_max_x]
set yrange [A_min_y - 0.05*A_max_y:A_max_y + 0.05*A_max_y]

set title filename
unset key
set border lw 2
set grid
set tics nomirror
set xlabel "X"
set ylabel "Y"

set linestyle 1 lc rgb "#CC2773" lw 4 pt 7 ps 4

do for [i=0:int(A_blocks-1)] {
	plot filename index i ls 1 w lp, '' with labels tc rgb "black"
}
