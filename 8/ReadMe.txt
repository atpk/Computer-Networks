CREATE FILES FOR VARIATION OF "CWS" WITH Ki

./cw -i 1 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o ki_1.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o ki_2.txt
./cw -i 3 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o ki_3.txt
./cw -i 4 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o ki_4.txt

---------xxx-----------------

CREATE FILES FOR VARIATION OF "CWS" WITH Km

./cw -i 2 -m 1.2 -n 1.0 -f 0.2 -s 0.4 -T 40 -o km_1.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o km_2.txt
./cw -i 2 -m 1.8 -n 1.0 -f 0.2 -s 0.4 -T 40 -o km_3.txt
./cw -i 2 -m 2.0 -n 1.0 -f 0.2 -s 0.4 -T 40 -o km_4.txt

---------xxx---------------------

CREATE FILES FOR VARIATION OF "CWS" WITH Kn

./cw -i 2 -m 1.4 -n 0.5 -f 0.2 -s 0.4 -T 40 -o kn_1.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o kn_2.txt
./cw -i 2 -m 1.4 -n 1.5 -f 0.2 -s 0.4 -T 40 -o kn_3.txt
./cw -i 2 -m 1.4 -n 2.0 -f 0.2 -s 0.4 -T 40 -o kn_4.txt

--------xxx--------------------

CREATE FILES FOR VARIATION OF "CWS" WITH Kf

./cw -i 2 -m 1.4 -n 1.0 -f 0.1 -s 0.4 -T 40 -o kf_1.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o kf_2.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.4 -s 0.4 -T 40 -o kf_3.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.5 -s 0.4 -T 40 -o kf_4.txt

----------xxx----------------

CREATE FILES FOR VARIATION OF "CWS" WITH Ps

./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.2 -T 40 -o km_1.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.4 -T 40 -o km_2.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.6 -T 40 -o km_3.txt
./cw -i 2 -m 1.4 -n 1.0 -f 0.2 -s 0.8 -T 40 -o km_4.txt

------------xxx---------------

##PLOT FOR Ki-VARIATION FILES

set terminal postscript color noenhanced
set output "ki_.ps"

set key top

set xlabel "Number of Tranmissions"
set ylabel "Congestion Window Size"
plot [1:41][1:10] \
    for [i = 1:4] "ki_".i.".txt" \
    pointsize 1.3 linecolor i+4 \
    title "ki_".i.".txt" \
    with linespoint

------------xxx-----------------

##PLOT FOR Km-VARIATION FILES

set terminal postscript color noenhanced
set output "km_.ps"

set key top

set xlabel "Number of Tranmissions"
set ylabel "Congestion Window Size"
plot [1:41][1:10] \
    for [i = 1:4] "km_".i.".txt" \
    pointsize 1.3 linecolor i+4 \
    title "km_".i.".txt" \
    with linespoint

-------------xxx---------------

##PLOT FOR Kn-VARIATION FILES

set terminal postscript color noenhanced
set output "kn_.ps"

set key top

set xlabel "Number of Tranmissions"
set ylabel "Congestion Window Size"
plot [1:41][1:10] \
    for [i = 1:4] "kn_".i.".txt" \
    pointsize 1.3 linecolor i+4 \
    title "kn_".i.".txt" \
    with linespoint

-----------xxx----------------

##PLOT FOR Kf-VARIATION FILES

set terminal postscript color noenhanced
set output "kf_.ps"

set key top

set xlabel "Number of Tranmissions"
set ylabel "Congestion Window Size"
plot [1:41][1:10] \
    for [i = 1:4] "kf_".i.".txt" \
    pointsize 1.3 linecolor i+4 \
    title "kf_".i.".txt" \
    with linespoint

-------------xxx------------

##PLOT FOR Ps-VARIATION FILES

set terminal postscript color noenhanced
set output "ps_.ps"

set key top

set xlabel "Number of Tranmissions"
set ylabel "Congestion Window Size"
plot [1:41][1:10] \
    for [i = 1:4] "ps_".i.".txt" \
    pointsize 1.3 linecolor i+4 \
    title "ps_".i.".txt" \
    with linespoint
