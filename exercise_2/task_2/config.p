set terminal png enhanced

set xlabel "Working Set Size (Bytes)"
set ylabel "Cycles/Operation" 

set logscale x
set logscale y

plot \
"data/results.dat" using 1:2 with errorlines title "Access Times for Random Writes"
