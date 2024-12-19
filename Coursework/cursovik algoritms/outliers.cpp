#include <vector>
#include <tuple>
#include <random>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Генерация случайного числа в диапазоне
double randomDouble(double min, double max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

// Функция для добавления выбросов
void addOutliers(vector<tuple<double, double>>& points, int numOutliers) {
    // Находим границы данных
    double minX = numeric_limits<double>::max(), maxX = numeric_limits<double>::min();
    double minY = numeric_limits<double>::max(), maxY = numeric_limits<double>::min();

    for (const auto& point : points) {
        minX = min(minX, get<0>(point));
        maxX = max(maxX, get<0>(point));
        minY = min(minY, get<1>(point));
        maxY = max(maxY, get<1>(point));
    }

    // Генерация выбросов: точки далеко за границами
    for (int i = 0; i < numOutliers; ++i) {
        double outlierX = randomDouble(minX - (maxX - minX), maxX + (maxX - minX));
        double outlierY = randomDouble(minY - (maxY - minY), maxY + (maxY - minY));
        points.emplace_back(outlierX, outlierY);
    }
}