set term png
set output 'histogram.png'
set title '����������� ��������� �����'
set xlabel '�������'
set ylabel '�������'
set style data histograms
plot 'histogram_data.txt' using 2:xtic(1) title '�������' with boxes
