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

    const unsigned long long seed = 12345; // Начальное значение (зерно) для генератора
    LinearCongruentialGenerator lcg(seed);

    const int numSamples = 10000; // Количество сгенерированных случайных чисел
    const int numBins = 20; // Количество корзин

    std::vector<int> histogram(numBins, 0);

    // Генерация случайных чисел и заполнение гистограммы
    for (int i = 0; i < numSamples; i++) {
        unsigned long long randomValue = lcg.random();
        int bin = randomValue % numBins;
        histogram[bin]++;
    }

    // Запись данных гистограммы в файл CSV
    std::ofstream dataFile("histogram_data.csv"); // Файл для данных гистограммы в формате CSV
    if (!dataFile) {
        std::cerr << "Ошибка: Не удалось открыть файл для данных!" << std::endl;
        return 1;
    }

    for (int i = 0; i < numBins; i++) {
        dataFile << i << "," << histogram[i] << std::endl;
    }
    std::cout << "Данные записаны в файл "<< std::endl;
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
