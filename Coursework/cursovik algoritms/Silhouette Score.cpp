#include <vector>
#include <tuple>
#include <cmath>
#include <limits>
#include <iostream>
#include "Header.h"

using namespace std;


// Функция для подсчета среднего расстояния до точек в том же кластере
double SameClustDist(const  tuple<double, double>& point, 
                      const vector< tuple<double, double>>& cluster) {

    double totalDistance = 0.0;
    for (const auto& p : cluster) {
        totalDistance += distance(point, p);
    }
    // Если кластер из одной точки, возвращаем 0
    return cluster.size() > 1 ? totalDistance / (cluster.size() - 1) : 0.0;
}

// Функция для подсчета среднего расстояния до ближайшего другого кластера
double NearestClustDist(const tuple<double, double>& point, const vector<vector< tuple<double, 
                        double>>>& clusters, int currentClusterIndex) {

    double minDistance = numeric_limits<double>::max();

    for (size_t i = 0; i < clusters.size(); ++i) {
        if (i == currentClusterIndex) continue; // Пропускаем текущий кластер

        double totalDistance = 0.0;
        for (const auto& p : clusters[i]) {
            totalDistance += distance(point, p);
        }
        double avgDistance = clusters[i].size() > 0 ? totalDistance / clusters[i].size() : numeric_limits<double>::max();

        minDistance = min(minDistance, avgDistance);
    }

    return minDistance;
}

// Основная функция для вычисления Silhouette Score для k-средних
double SilhouetteScore(const vector< tuple<double, double>>& points, 
                        const vector<vector< tuple<double, double>>>& clusters) {

    double totalScore = 0.0;
    int totalPoints = 0;

    for (size_t clusterIdx = 0; clusterIdx < clusters.size(); ++clusterIdx) {
        for (const auto& point : clusters[clusterIdx]) {
            double a = SameClustDist(point, clusters[clusterIdx]);
            double b = NearestClustDist(point, clusters, clusterIdx);

            double silhouette = (b - a) / max(a, b);
            totalScore += silhouette;
            ++totalPoints;
        }
    }

    return totalPoints > 0 ? totalScore / totalPoints : 0.0;
}

// Преобразование кластеров для иерархического метода в формат, удобный для подсчета Silhouette Score
vector<vector< tuple<double, double>>> convertHClust(const vector< tuple<double, double>>& points, 
                                                    const vector<vector<int>>& clusters) {

    vector<vector< tuple<double, double>>> result;
    for (const auto& cluster : clusters) {
        vector< tuple<double, double>> clusterPoints;
        for (int index : cluster) {
            clusterPoints.push_back(points[index]);
        }
        result.push_back(clusterPoints);
    }
    return result;
}

// Основная функция для вычисления Silhouette Score для иерархического метода
double SilhouetteScoreH(const vector< tuple<double, double>>& points, const vector<vector<int>>& HClusters) {
    vector<vector< tuple<double, double>>> clusters = convertHClust(points, HClusters);
    return SilhouetteScore(points, clusters);
}
