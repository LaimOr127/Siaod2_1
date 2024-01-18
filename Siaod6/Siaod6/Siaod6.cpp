#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>

class Graph {
private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;

public:
    Graph(int vertices) : adjacencyList(vertices) {}

    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].emplace_back(destination, weight);
        adjacencyList[destination].emplace_back(source, weight);
    }

    void addVertex() {
        adjacencyList.emplace_back();
    }

    void displayGraph() const {
        for (int i = 0; i < adjacencyList.size(); ++i) {
            std::cout << "Вершина " << i + 1 << " соседи: ";
            for (const auto& neighbor : adjacencyList[i]) {
                std::cout << neighbor.first + 1 << "(" << neighbor.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    void displayGraphASCII() const {
        for (int i = 0; i < adjacencyList.size(); ++i) {
            std::cout << "Вершина " << i + 1 << ": ";
            for (const auto& neighbor : adjacencyList[i]) {
                std::cout << i + 1 << " --" << neighbor.second << "-- " << neighbor.first + 1 << "   ";
            }
            std::cout << std::endl;
        }
    }

    void dijkstra(int start, int end, int K) {
        // Implementation of Dijkstra's algorithm remains unchanged
    }

    std::vector<std::pair<int, int>> getVertexRating() {
        std::vector<std::pair<int, int>> rating;

        for (int i = 0; i < adjacencyList.size(); ++i) {
            rating.emplace_back(i, adjacencyList[i].size());
        }

        std::sort(rating.begin(), rating.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        return rating;
    }

    bool isConnected() const {
        std::vector<bool> visited(adjacencyList.size(), false);
        dfs(0, visited);
        return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
    }

private:
    void dfs(int v, std::vector<bool>& visited) const {
        visited[v] = true;
        for (const auto& neighbor : adjacencyList[v]) {
            int u = neighbor.first;
            if (!visited[u]) {
                dfs(u, visited);
            }
        }
    }
};

int main() {
    setlocale(0, "rus");
    int choice;
    int vertices;

    std::cout << "Введите количество вершин в графе: ";
    std::cin >> vertices;

    Graph graph(vertices);

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить ребро\n";
        std::cout << "2. Вывести граф\n";
        std::cout << "3. Выполнить поиск кратчайшего пути\n";
        std::cout << "4. Добавить новую вершину\n";
        std::cout << "5. Проверить связность графа\n";
        std::cout << "0. Выйти\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите ребро в формате 'откуда куда вес':\n";
            int source, destination, weight;
            std::cin >> source >> destination >> weight;
            graph.addEdge(source - 1, destination - 1, weight);
            break;

        case 2:
            std::cout << "Граф:\n";
            graph.displayGraph();
            std::cout << "\nГраф в виде рисунка:\n";
            graph.displayGraphASCII();
            break;

        case 3:
            int start, end, K;
            std::cout << "Введите начальную вершину, конечную вершину и ограничение на вес ребер (K): ";
            std::cin >> start >> end >> K;
            graph.dijkstra(start - 1, end - 1, K);
            break;

        case 4:
            graph.addVertex();
            std::cout << "Добавлена новая вершина.\n";
            break;

        case 5:
            if (graph.isConnected()) {
                std::cout << "Граф связный.\n";
            }
            else {
                std::cout << "Граф несвязный.\n";
            }
            break;

        case 0:
            std::cout << "Выход из программы.\n";
            break;

        default:
            std::cout << "Неверный выбор. Пожалуйста, введите корректное значение.\n";
        }
    } while (choice != 0);

    return 0;
}
