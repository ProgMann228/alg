#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Функция для чтения точек из файла
vector<tuple<double, double>> DataSetWine(const string& filename) {
    vector<tuple<double, double>> points;
    ifstream file(filename);  // Открываем файл
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        return points;
    }

    while (getline(file, line)) {
        istringstream ss(line);
        string value;
        vector<double> row;

        // Разделяем строку по запятым и сохраняем значения
        while (getline(ss, value, ',')) {
            row.push_back(stod(value)); // Преобразуем строку в double
        }

        if (row.size() >= 3) { // Убедимся, что в строке есть минимум три столбца
            double feature1 = row[1]; // Второй признак (индекс 1)
            double feature2 = row[2]; // Третий признак (индекс 2)
            points.emplace_back(feature1, feature2); // Добавляем точку
        }
    }

    file.close();
    return points;
}