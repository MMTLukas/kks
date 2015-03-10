set terminal png enhanced

set xlabel "Number of elements (logscale)"
set ylabel "Nanoseconds per push operation" 

set yrange[0:]
set logscale x

plot \
"data/results_own.dat" using 2:3 with errorlines title "My Min-Heap Implementation", \
"data/results_stl.dat" using 2:3 with errorlines title "STL Implementation"
