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


void updateCentr(const vector<vector<tuple<double, double>>>& clusters,
    vector<tuple<double, double>>& centroids) {
    double sumX = 0.0, sumY = 0.0;
    for (int i = 0; i < clusters.size(); ++i) {
        if (clusters[i].empty()) {
            // ���� ������� ������, ��������� �������� ��� ���������
            cout << "Cluster " << i + 1 << " is empty. Keeping the old centroid.\n";
            continue;
        }
        sumX = 0.0, sumY = 0.0;
        for (const auto& point : clusters[i]) {
            sumX += get<0>(point);
            sumY += get<1>(point);
        }
        int n = clusters[i].size();
        // ����� �������� - ������� ���� ����� � ��������
        centroids[i] = make_tuple(sumX / n, sumY / n);
    }
}

void K_Means(vector<tuple<double, double>>& points,
    vector<tuple<double, double>>& centroids,
    vector<vector<tuple<double, double>>>& clusters) {

    double epsilon = 1e-6; // ����� ��� ����������� ��������

    // ������� �������� ����� �������������� �����
    for (auto& cluster : clusters) {
        cluster.clear();
    }

    for (const auto& point : points) {
        //�������� �������� ��� ������ min
        double minDistance = numeric_limits<double>::infinity();
        int closestCluster = 0;

        // ��� ������ ����� ������� ��������� ��������
        for (int i = 0; i < centroids.size(); ++i) {
            double dist = distance(point, centroids[i]);

            if (dist < minDistance) {
                minDistance = dist;
                closestCluster = i;
            }
        }
        // ����������� ����� ��������
        clusters[closestCluster].push_back(point);
    }

    for (int i = 0; i < clusters.size(); ++i) {
        cout << "\nCluster " << i + 1 << ":\n";
        for (const auto& point : clusters[i]) {
            cout << "(" << get<0>(point) << ", " << get<1>(point) << ")\n";
        }
    }

    //����� ���������
    vector<tuple<double, double>> newCentroids = centroids;
    updateCentr(clusters, newCentroids);

    cout << "\ncentroids:\n";
    for (const auto& cent : newCentroids) {
        cout << "(" << get<0>(cent) << ", " << get<1>(cent) << ")\n";
    }

    // �������� �� ����������
    bool flag = true; // �������, ��� ���������� ����������
    for (int i = 0; i < centroids.size(); ++i) {
        if (distance(centroids[i], newCentroids[i]) > epsilon) {
            flag = false; // ���� ���� �� ���� �������� ������ ���������
            break;
        }
    }

    if (flag == false)
        K_Means(points, newCentroids, clusters);
}