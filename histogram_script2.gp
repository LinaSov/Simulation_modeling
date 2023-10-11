set term png
set output 'histogram2.png'
set title 'Гистограмма случайных чисел'
set xlabel 'Корзины'
set ylabel 'Частота'
set style data histograms
plot 'histogram_data2.csv' using 2:xtic(1) title 'Частота' with boxes
