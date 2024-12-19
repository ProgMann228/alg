#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple> 
using namespace std;

// ������� ��� ������ ����� �� �����
vector<tuple<double, double>> DataSet(const string& filename) {
    vector<tuple<double, double>> points;
    ifstream file(filename);  // ��������� ����
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        return points;
    }

    while (getline(file, line)) {  // ������ ���� ���������
        if (line.empty()) continue;  // ���������� ������ ������

        stringstream ss(line);
        string value;
        double sepalLength, sepalWidth;

        // ������ ������ ���� �������� (sepal length � sepal width)
        getline(ss, value, ',');
        //cout << value<<'\n';;
        sepalLength = stod(value);  // ����������� ������ � double
        getline(ss, value, ',');
        sepalWidth = stod(value);

        // ��������� ����� � ������
        points.emplace_back(sepalLength, sepalWidth);
       // cout << sepalLength << ' ' << sepalWidth;
    }

    file.close();
    return points;
}