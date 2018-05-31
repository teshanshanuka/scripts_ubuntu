if (!exists("nowmaxx")) nowmaxx = 0; \
else nowmaxx = nowmaxx + 1 

print(nowmaxx)
set xrange [0:20]
set yrange [0:400]
plot "plot.dat" using 1:2 with lines
pause 0.5
if (nowmaxx < 20) reread
