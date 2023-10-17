#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

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

void writeHistogramToCSV(const std::string& filename, const std::vector<int>& histogram, int num_bins) {
    std::ofstream csv_file(filename);
    if (!csv_file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < num_bins; i++) {
        csv_file << histogram[i] << "\n";
    }

    csv_file.close();
    std::cout << "Гистограмма сохранена в файле '" << filename << "'." << std::endl;
}

void printChiSquareResult(double chi_square) {
    std::cout << "Тестирование методом 'Хи-квадрат':" << std::endl;
    std::cout << "Хи-квадрат: " << chi_square << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    LinearCongruentialGenerator lcg;

    const int num_samples = 10000;
    const int num_bins = 10;
    std::vector<int> histogram(num_bins, 0);

    for (int i = 0; i < num_samples; i++) {
        unsigned long long random_num = lcg.random();
        int bin = random_num % num_bins;
        histogram[bin]++;
    }

    writeHistogramToCSV("histogram1.csv", histogram, num_bins);

    const int expected_count = num_samples / num_bins;
    double chi_square = 0.0;

    for (int i = 0; i < num_bins; i++) {
        chi_square += std::pow(histogram[i] - expected_count, 2) / expected_count;
    }

    printChiSquareResult(chi_square);

    return 0;
}
