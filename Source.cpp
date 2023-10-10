#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <locale>
#include <clocale>

class LinearCongruentialGenerator {
public:
    LinearCongruentialGenerator(unsigned long long seed = 1)
        : m_seed(seed) {
    }

    unsigned long long random() {
        m_seed = (a * m_seed + c) % m;
        return m_seed;
    }

    void setSeed(unsigned long long seed) {
        m_seed = seed;
    }

private:
    const unsigned long long a = 1664525;
    const unsigned long long c = 1013904223;
    const unsigned long long m = 4294967296;
    unsigned long long m_seed;
};

int main() {
    setlocale(LC_ALL, "Russian");

    const unsigned long long seed = 12345; // ��������� �������� (�����) ��� ����������
    LinearCongruentialGenerator lcg(seed);

    const int numSamples = 10000; // ���������� ��������������� ��������� �����
    const int numBins = 20; // ���������� ������

    std::vector<int> histogram(numBins, 0);

    // ��������� ��������� ����� � ���������� �����������
    for (int i = 0; i < numSamples; i++) {
        unsigned long long randomValue = lcg.random();
        int bin = randomValue % numBins;
        histogram[bin]++;
    }

    // ������ ������ ����������� � ���� CSV
    std::ofstream dataFile("histogram_data.csv"); // ���� ��� ������ ����������� � ������� CSV
    if (!dataFile) {
        std::cerr << "������: �� ������� ������� ���� ��� ������!" << std::endl;
        return 1;
    }

    for (int i = 0; i < numBins; i++) {
        dataFile << i << "," << histogram[i] << std::endl;
    }
    std::cout << "������ �������� � ���� "<< std::endl;
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
