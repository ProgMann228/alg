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
using namespace std;

// Функция для вычисления евклидова расстояния между двумя точками
double distance(const tuple<double, double>& p1, const tuple<double, double>& p2) {
    return sqrt(pow(get<0>(p1) - get<0>(p2), 2) + pow(get<1>(p1) - get<1>(p2), 2));
}

int main()
{
    setlocale(LC_ALL, "C"); // Устанавливаем локаль C (английская)

    int flag = 0, k = 3;
	vector<tuple<double, double>> points;
    vector<tuple<double, double>> centroids;
    //для хранения кластеров (каждый кластер будет хранить свои точки)
    vector<vector<tuple<double, double>>> clusters(k);
    
   
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1.0, 100.0);

    for (int i = 0; i < 100; i++) {
        points.push_back(make_tuple(dist(gen), dist(gen)));
    }

   // string filename = "iris.data";  // Путь к файлу
   // points = DataSet(filename);

    //string filename2 = "wine.data";  // Путь к файлу
    //points = DataSetWine(filename2);

     //Добавляем 10 выбросов
     //addOutliers(points, 50);

    cout << "points:\n";
    cout << fixed << setprecision(2);  // Отображаем 2 знака после запятой
    for (const auto& point : points) {
        cout << "(" << get<0>(point) << ", " << get<1>(point) << ")\n";
    }

    uniform_int_distribution<> dist2(0, points.size() - 1);
    set<int> chosenIndices; // Для предотвращения повторов

    while (chosenIndices.size() < k) {
        int index = dist2(gen);
        if (chosenIndices.insert(index).second) { // Добавляется, если index уникален
            centroids.push_back(points[index]);
        }
    }
    cout << "\ncentroids:\n";
    for (const auto& cent : centroids) {
        cout << "(" << get<0>(cent) << ", " << get<1>(cent) << ")\n";
    }

    auto start1 = chrono::high_resolution_clock::now();
    K_Means(points, centroids, clusters);
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed1 = end1 - start1;

    // Сохранение кластеров K-means в файл
    saveClustersToFile(clusters, "C:/Users/Elizaveta/OneDrive/Документы/для перекида/алгоритмы/cursovik algoritms/k-means.txt");
    

    /*cout << "Single-linkage clustering:\n";
    Hierarchical(points, k, SINGLE);

    cout << "\nComplete-linkage clustering:\n";
    Hierarchical(points, k, COMPLETE);*/

    vector<vector<int>> clustersH(points.size()); // Создаём n пустых векторов

    auto start2 = chrono::high_resolution_clock::now();
    cout << "\nAverage-linkage clustering:\n";
    Hierarchical(clustersH, points, k, AVERAGE);
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed2 = end2 - start2;

    // Сохранение кластеров иерархической кластеризации в файл
    saveClustersToFileH(clustersH, points, "C:/Users/Elizaveta/OneDrive/Документы/для перекида/алгоритмы/cursovik algoritms/Hierarchical.txt");

    

    // Расчет Silhouette Score для k-средних
    double KMSilhouette = SilhouetteScore(points, clusters);
    cout << "K-means Silhouette Score: " << KMSilhouette << endl;

    // Расчет Silhouette Score для иерархической кластеризации
    double HSilhouette = SilhouetteScoreH(points, clustersH);
    cout << "Hierarchical Silhouette Score: " << HSilhouette << endl;

    cout << "K-Means time: " << elapsed1.count() << "sec" << endl;
    cout << "Hierarchical time: " << elapsed2.count() << "sec" << endl;

}


