set terminal png enhanced

set xlabel "Number of elements (logscale)"
set ylabel "Nanoseconds per push operation (logscale)" 

set logscale x
set logscale y

plot \
"data/results.dat" using 2:4 with errorlines title "Own minheap implementation", \
"data/results.dat" using 2:6 with errorlines title "STL implementation"
