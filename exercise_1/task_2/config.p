set terminal png enhanced

set xlabel "Number of elements (logscale)"
set ylabel "Nanoseconds per push operation" 

set yrange[0:]

plot \
"data/results.dat" using 2:3 with errorlines title "My Min-Heap Implementation"
