# Pour utiliser ce script appler le dans le terminal en precisant
# la variable filename avec le nom du fichier sans extension.
# Par exemple pour ./tsp/bayg29.tsp
# gnuplot -e "filename = './tsp/bayg29'" plot.gp

set term gif animate delay 10 size 1200,800
set output filename . ".gif"

datafile = filename . ".dat"

stats datafile name "A"
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
	plot datafile index i ls 1 w lp, '' with labels tc rgb "black"
	if (i==int(A_blocks-1)) {
		do for [j=0:30] {
			plot datafile index i ls 1 w lp, '' with labels tc rgb "black"
		}
	}

}
