set title "Algorithme glouton + 2-opt"
set title tc rgb "purple"

# Background
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "black" behind

# Border
set border lw 2 lc rgb "white"

# Tics
set xtics tc rgb "white"
set ytics tc rgb "white"

# Labels
set xlabel "X" tc rgb "purple"
set ylabel "Y" tc rgb "purple" rotate by 90

# Key
set key tc rgb "purple"

plot "bayg29.tsp.out" lc rgb "white" lt 7 ps 2 w lp
