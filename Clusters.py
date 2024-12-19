import matplotlib.pyplot as plt


# Функция для считывания кластеров из файла
def read_clusters_from_file(filename):
    clusters = []
    with open(filename, 'r') as file:
        cluster = []
        for line in file:
            line = line.strip()
            if line.startswith("Cluster"):
                if cluster:  # Если это новый кластер, сохраняем предыдущий
                    clusters.append(cluster)
                cluster = []
            elif line:
                # Парсим координаты точки (x, y)
                x, y = map(float, line.split(','))
                cluster.append((x, y))
        if cluster:  # Не забываем добавить последний кластер
            clusters.append(cluster)
    return clusters


# Чтение кластеров из файлов
kmeans_clusters = read_clusters_from_file('C:/Users/Elizaveta/OneDrive/Документы/для перекида/алгоритмы/cursovik algoritms/k-means.txt')
hierarchical_clusters = read_clusters_from_file('C:/Users/Elizaveta/OneDrive/Документы/для перекида/алгоритмы/cursovik algoritms/Hierarchical.txt')


# Функция для рисования кластеров с нормальным масштабом
def plot_clusters(clusters, title):
    plt.figure(figsize=(9, 6))  # Размер графика

    # Собираем все точки для вычисления границ
    all_x = [point[0] for cluster in clusters for point in cluster]
    all_y = [point[1] for cluster in clusters for point in cluster]

    for i, cluster in enumerate(clusters):
        x_values, y_values = zip(*cluster)
        plt.scatter(x_values, y_values, s=20, label=f"Cluster {i + 1}")  # Размер маркеров

    # Устанавливаем границы с небольшим запасом
    plt.xlim(min(all_x) - 0.5, max(all_x) + 0.5)
    plt.ylim(min(all_y) - 0.5, max(all_y) + 0.5)

    plt.title(title)
    plt.xlabel("X координата")
    plt.ylabel("Y координата")
    plt.axis('equal')  # Сохраняем пропорции осей
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.5)  # Добавляем сетку
    plt.tight_layout()
    plt.show()

# Построение графиков
plot_clusters(kmeans_clusters, "K-means Clustering")
plot_clusters(hierarchical_clusters, "Hierarchical Clustering")
