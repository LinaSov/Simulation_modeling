set term png
set output 'histogram2.png'
set title '����������� ��������� �����'
set xlabel '�������'
set ylabel '�������'
set style data histograms
plot 'histogram_data2.csv' using 2:xtic(1) title '�������' with boxes
