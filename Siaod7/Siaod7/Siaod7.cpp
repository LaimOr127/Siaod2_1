#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;

uint64_t Min(
    const vector<vector<uint64_t>>& map,
    vector<vector<uint64_t>>& mins, size_t i, size_t j,
    vector<vector<int>>& steps
) {
    if (mins[i][j] != 0) {
        return mins[i][j];
    }

    uint64_t min_result = UINT64_MAX;

    if (i > 0 && j > 0) {
        min_result = min(min_result, Min(map, mins, i - 1, j - 1, steps));
    }

    if (j > 0) {
        min_result = min(min_result, Min(map, mins, i, j - 1, steps));
    }

    if (i > 0) {
        min_result = min(min_result, Min(map, mins, i - 1, j, steps));
    }

    if (min_result != UINT64_MAX) {
        steps[i][j]++;
    }

    return mins[i][j] = min_result + map[i][j];
}

uint64_t BruteForce(
    const vector<vector<uint64_t>>& map,
    size_t i, size_t j,
    vector<vector<int>>& steps
) {
    if (i == 0 && j == 0) {
        return map[0][0];
    }

    uint64_t min_result = UINT64_MAX;

    if (i > 0 && j > 0) {
        min_result = min(min_result, BruteForce(map, i - 1, j - 1, steps));
    }

    if (j > 0) {
        min_result = min(min_result, BruteForce(map, i, j - 1, steps));
    }

    if (i > 0) {
        min_result = min(min_result, BruteForce(map, i - 1, j, steps));
    }

    if (min_result != UINT64_MAX) {
        steps[i][j]++;
    }

    return min_result + map[i][j];
}

uint64_t Solution(const vector<vector<uint64_t>>& map, vector<vector<int>>& steps) {
    size_t n = map.size();
    size_t m = map[0].size();

    vector<vector<uint64_t>> mins(n, vector<uint64_t>(m, 0));
    vector<vector<int>> dpSteps(n, vector<int>(m, 0));

    mins[0][0] = map[0][0];

    uint64_t dpResult = Min(map, mins, n - 1, m - 1, dpSteps);

    return dpResult;
}

uint64_t BruteForceSolution(const vector<vector<uint64_t>>& map, vector<vector<int>>& steps) {
    size_t n = map.size();
    size_t m = map[0].size();

    vector<vector<int>> bruteForceSteps(n, vector<int>(m, 0));

    uint64_t bruteForceResult = BruteForce(map, n - 1, m - 1, bruteForceSteps);

    return bruteForceResult;
}

vector<vector<uint64_t>> GenerateRandomMap(size_t n, size_t m, uint64_t max_value) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint64_t> dist(1, max_value);

    vector<vector<uint64_t>> map(n, vector<uint64_t>(m));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            map[i][j] = dist(gen);
        }
    }

    return map;
}

int main() {
    size_t n, m;
    uint64_t max_value;

    cout << "Enter m, n, and the maximum value for random generation: ";
    cin >> m >> n >> max_value;

    vector<vector<uint64_t>> map = GenerateRandomMap(n, m, max_value);

    cout << "Generated Map:" << endl;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    auto start = high_resolution_clock::now();
    vector<vector<int>> dpSteps(n, vector<int>(m, 0));
    uint64_t dpResult = Solution(map, dpSteps);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Dynamic Programming Time: " << duration.count() << " microseconds" << endl;

    // Аналогично для метода в лоб
    start = high_resolution_clock::now();
    vector<vector<int>> bruteForceSteps(n, vector<int>(m, 0));
    uint64_t bruteForceResult = BruteForceSolution(map, bruteForceSteps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Brute Force Time: " << duration.count() << " microseconds" << endl;

    // ... Вывод результатов и т.д.

    // Также можно вывести объем памяти, занимаемый каждым методом
    cout << "Dynamic Programming Memory: " << sizeof(dpSteps) << " bytes" << endl;
    cout << "Brute Force Memory: " << sizeof(bruteForceSteps) << " bytes" << endl;

    return 0;
}
