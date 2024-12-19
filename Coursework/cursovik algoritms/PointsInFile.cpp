#include <vector>
#include <tuple> 
#include <iostream>
#include <random>
#include <algorithm>
#include <set>
#include <cmath>
#include <limits>
#include <iomanip>
#include <chrono>
#include "Header.h"
#include <fstream>
using namespace std;

// Функция для записи кластеров в файл
void saveClustersToFile(const vector<vector<tuple<double, double>>>& clusters, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Записываем каждый кластер
    for (size_t i = 0; i < clusters.size(); ++i) {
        outFile << "Cluster " << i + 1 << ":\n";
        for (const auto& point : clusters[i]) {
            outFile << get<0>(point) << "," << get<1>(point) << "\n";
        }
    }

    outFile.close();
    cout << "Clusters saved to: " << filename << endl;
}

// Функция для записи кластеров иерархической кластеризации в файл
void saveClustersToFileH(const vector<vector<int>>& clusters, const vector<tuple<double, double>>& points, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Записываем каждый кластер
    for (size_t i = 0; i < clusters.size(); ++i) {
        outFile << "Cluster " << i + 1 << ":\n";
        for (int idx : clusters[i]) {
            outFile << get<0>(points[idx]) << "," << get<1>(points[idx]) << "\n";
        }
    }

    outFile.close();
    cout << "Hierarchical clusters saved to: " << filename << endl;
}