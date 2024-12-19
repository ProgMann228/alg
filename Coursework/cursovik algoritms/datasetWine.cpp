#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

// ������� ��� ������ ����� �� �����
vector<tuple<double, double>> DataSetWine(const string& filename) {
    vector<tuple<double, double>> points;
    ifstream file(filename);  // ��������� ����
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        return points;
    }

    while (getline(file, line)) {
        istringstream ss(line);
        string value;
        vector<double> row;

        // ��������� ������ �� ������� � ��������� ��������
        while (getline(ss, value, ',')) {
            row.push_back(stod(value)); // ����������� ������ � double
        }

        if (row.size() >= 3) { // ��������, ��� � ������ ���� ������� ��� �������
            double feature1 = row[1]; // ������ ������� (������ 1)
            double feature2 = row[2]; // ������ ������� (������ 2)
            points.emplace_back(feature1, feature2); // ��������� �����
        }
    }

    file.close();
    return points;
}