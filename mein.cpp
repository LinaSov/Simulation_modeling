#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <locale>
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");

    const unsigned long long seed = 12345; // Начальное значение (зерно) для генератора
    std::mt19937 mt(seed);

    const int numSamples = 10000; // Количество сгенерированных случайных чисел
    const int numBins = 20; // Количество корзин

    std::vector<int> histogram(numBins, 0);

    std::uniform_int_distribution<int> dist(0, numBins - 1);

    // Генерация случайных чисел и заполнение гистограммы
    for (int i = 0; i < numSamples; i++) {
        int randomValue = dist(mt);
        histogram[randomValue]++;
    }

    // Запись данных гистограммы в файл CSV
    std::ofstream dataFile("histogram_data_cpp.csv"); 
    if (!dataFile) {
        std::cerr << "Ошибка: Не удалось открыть файл для данных!" << std::endl;
        return 1;
    }

    for (int i = 0; i < numBins; i++) {
        dataFile << i << "," << histogram[i] << std::endl;
    }
    std::cout << "Данные записаны в файл " << std::endl;
    dataFile.close();

    // Проведение теста хи-квадрат
    double expected = static_cast<double>(numSamples) / numBins;
    double chiSquared = 0.0;

    for (int i = 0; i < numBins; i++) {
        chiSquared += pow(histogram[i] - expected, 2) / expected;
    }

    // Вывод результатов
    std::cout << "Значение хи-квадрат: " << chiSquared << std::endl;

    return 0;
}
