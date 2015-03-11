set terminal png enhanced

set xlabel "Working Set Size (Bytes)"
set ylabel "Cycles/Operation" 

set logscale x 2
set logscale y

set format x '2^{%L}'

plot \
"data/results0.dat" using (2**$1):2 with errorlines title "Access Time NPAD = 0", \
"data/results7.dat" using (2**$1):2 with errorlines title "Access Time NPAD = 7", \
"data/results15.dat" using (2**$1):2 with errorlines title "Access Time NPAD = 15", \
"data/results31.dat" using (2**$1):2 with errorlines title "Access Time NPAD = 31"