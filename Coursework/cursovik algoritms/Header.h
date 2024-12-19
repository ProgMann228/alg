#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <tuple>

using namespace std;

// Перечисление для выбора метода агломерации
enum LinkageMethod {
    SINGLE,
    COMPLETE,
    AVERAGE
};

// Объявление функций
void updateCentr(const vector<vector<tuple<double, double>>>& clusters,
                 vector<tuple<double, double>>& centroids);

void K_Means(vector<tuple<double, double>>& points,
             vector<tuple<double, double>>& centroids,
             vector<vector<tuple<double, double>>>& clusters);

double distance(const tuple<double, double>& p1, const tuple<double, double>& p2);

void Hierarchical(vector<vector<int>>& clusters, 
                    const vector<tuple<double, double>>& points, int k, 
                    LinkageMethod method);

vector<tuple<double, double>> DataSet(const string& filename);

double SilhouetteScore(const vector< tuple<double, double>>& points,
                     const vector<vector< tuple<double, double>>>& clusters);

double SilhouetteScoreH(const vector< tuple<double, double>>& points, 
                        const vector<vector<int>>& HClusters);

void saveClustersToFile(const vector<vector<tuple<double, double>>>& 
                        clusters, const string& filename);

void saveClustersToFileH(const vector<vector<int>>& clusters,
                        const vector<tuple<double, double>>& points,
                        const string& filename);

void addOutliers(vector<tuple<double, double>>& points, int numOutliers);

vector<tuple<double, double>> DataSetWine(const string& filename);


#endif 