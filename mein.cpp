#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <locale>
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");

    const unsigned long long seed = 12345; // ��������� �������� (�����) ��� ����������
    std::mt19937 mt(seed);

    const int numSamples = 10000; // ���������� ��������������� ��������� �����
    const int numBins = 20; // ���������� ������

    std::vector<int> histogram(numBins, 0);

    std::uniform_int_distribution<int> dist(0, numBins - 1);

    // ��������� ��������� ����� � ���������� �����������
    for (int i = 0; i < numSamples; i++) {
        int randomValue = dist(mt);
        histogram[randomValue]++;
    }

    // ������ ������ ����������� � ���� CSV
    std::ofstream dataFile("histogram_data_cpp.csv"); 
    if (!dataFile) {
        std::cerr << "������: �� ������� ������� ���� ��� ������!" << std::endl;
        return 1;
    }

    for (int i = 0; i < numBins; i++) {
        dataFile << i << "," << histogram[i] << std::endl;
    }
    std::cout << "������ �������� � ���� " << std::endl;
    dataFile.close();

    // ���������� ����� ��-�������
    double expected = static_cast<double>(numSamples) / numBins;
    double chiSquared = 0.0;

    for (int i = 0; i < numBins; i++) {
        chiSquared += pow(histogram[i] - expected, 2) / expected;
    }

    // ����� �����������
    std::cout << "�������� ��-�������: " << chiSquared << std::endl;

    return 0;
}
