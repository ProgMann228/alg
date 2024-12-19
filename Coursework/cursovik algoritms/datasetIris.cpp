#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple> 
using namespace std;

// Функция для чтения точек из файла
vector<tuple<double, double>> DataSet(const string& filename) {
    vector<tuple<double, double>> points;
    ifstream file(filename);  // Открываем файл
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        return points;
    }

    while (getline(file, line)) {  // Читаем файл построчно
        if (line.empty()) continue;  // Пропускаем пустые строки

        stringstream ss(line);
        string value;
        double sepalLength, sepalWidth;

        // Чтение первых двух значений (sepal length и sepal width)
        getline(ss, value, ',');
        //cout << value<<'\n';;
        sepalLength = stod(value);  // Конвертация строки в double
        getline(ss, value, ',');
        sepalWidth = stod(value);

        // Добавляем точку в вектор
        points.emplace_back(sepalLength, sepalWidth);
       // cout << sepalLength << ' ' << sepalWidth;
    }

    file.close();
    return points;
}