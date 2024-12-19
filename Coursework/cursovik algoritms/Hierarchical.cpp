#include <vector>
#include <tuple> 
#include <iostream>
#include <random>
#include <algorithm>
#include <set>
#include <cmath>
#include <limits>
#include "Header.h"
using namespace std;



// Функция для вывода кластеров
void printClusters(const vector<vector<int>>& clusters, const vector<tuple<double, double>>& points) {
    for (size_t i = 0; i < clusters.size(); ++i) {
        cout << "Cluster " << i + 1 << ": ";
        for (int idx : clusters[i]) {
            cout << "(" << get<0>(points[idx]) << ", " << get<1>(points[idx]) << ") ";
        }
        cout << '\n';
    }
}

// Функция для вычисления расстояния между двумя кластерами с разными методами агломерации
double ClusterDistance(const vector<int>& clusterA, const vector<int>& clusterB,
    const vector<tuple<double, double>>& points, LinkageMethod method) {
    double result = 0.0;

    if (method == SINGLE) { // Single-linkage (минимальное расстояние)
        result = numeric_limits<double>::max();
        for (int p1 : clusterA) {
            for (int p2 : clusterB) {
                result = min(result, distance(points[p1], points[p2]));
            }
        }
    }
    else if (method == COMPLETE) { // Complete-linkage (максимальное расстояние)
        result = numeric_limits<double>::lowest();
        for (int p1 : clusterA) {
            for (int p2 : clusterB) {
                result = max(result, distance(points[p1], points[p2]));
            }
        }
    }
    else if (method == AVERAGE) { // Average-linkage (среднее расстояние)
        double sum = 0.0;
        int count = 0;
        for (int p1 : clusterA) {
            for (int p2 : clusterB) {
                sum += distance(points[p1], points[p2]);
                count++;
            }
        }
        result = sum / count;
    }
    return result;
}

// Основная функция иерархической кластеризации
void Hierarchical(vector<vector<int>>& clusters,const vector<tuple<double, double>>& points, int k, LinkageMethod method) {
    int n = points.size();
    for (size_t i = 0; i < points.size(); ++i) {
        clusters[i].push_back(i);
    }

    while (clusters.size() > k) {
        double minDistance = numeric_limits<double>::max();
        int mergeA = -1, mergeB = -1;

        // Найти ближайшие кластеры с использованием выбранной метрики
        for (size_t i = 0; i < clusters.size(); ++i) {
            for (size_t j = i + 1; j < clusters.size(); ++j) {
                double dist = ClusterDistance(clusters[i], clusters[j], points, method);

                if (dist < minDistance) {
                    minDistance = dist;
                    mergeA = i;
                    mergeB = j;
                }
            }
        }

        // Объединить ближайшие кластеры
        if (mergeA != -1 && mergeB != -1) {
            clusters[mergeA].insert(clusters[mergeA].end(), clusters[mergeB].begin(), clusters[mergeB].end());
            clusters.erase(clusters.begin() + mergeB);
        }
    }

    // Вывести результаты
    printClusters(clusters, points);
    cout << "Clustering completed.\n";
}
