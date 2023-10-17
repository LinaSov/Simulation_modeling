#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <cmath>

void writeHistogramToCSV(const std::string& filename, const std::vector<int>& histogram) {
    std::ofstream csv_file(filename);
    if (!csv_file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < histogram.size(); i++) {
        csv_file  << histogram[i] << "\n";
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

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9); 

    const int num_samples = 10000;
    const int num_bins = 10;
    std::vector<int> histogram(num_bins, 0);

    for (int i = 0; i < num_samples; i++) {
        int random_num = dist(mt);  
        histogram[random_num]++;
    }

    writeHistogramToCSV("histogram_mt.csv", histogram);

    const int expected_count = num_samples / num_bins;
    double chi_square = 0.0;

    for (int i = 0; i < num_bins; i++) {
        chi_square += std::pow(histogram[i] - expected_count, 2) / expected_count;
    }

    printChiSquareResult(chi_square);

    return 0;
}
