#include <iostream>
#include <locale.h> // Для setlocale

// Структура узла бинарного дерева
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Функция для создания идеально сбалансированного бинарного дерева
TreeNode* createBalancedBST(int arr[], int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    TreeNode* root = new TreeNode(arr[mid]);

    root->left = createBalancedBST(arr, start, mid - 1);
    root->right = createBalancedBST(arr, mid + 1, end);

    return root;
}

// Функция для определения высоты дерева
int getHeight(TreeNode* root) {
    if (root == nullptr) {
        return -1; // Высота пустого дерева -1
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return 1 + std::max(leftHeight, rightHeight);
}

// Функция для определения количества ребер в дереве
int getEdgeCount(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    return getEdgeCount(root->left) + getEdgeCount(root->right) + 1;
}

// Функция для вычисления суммы всех чисел в дереве
int getSum(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    return root->data + getSum(root->left) + getSum(root->right);
}

// Функция для отображения дерева как структуры
void printTreeStructure(TreeNode* root, int level) {
    if (root == nullptr) {
        return;
    }

    printTreeStructure(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }

    std::cout << root->data << std::endl;

    printTreeStructure(root->left, level + 1);
}

int main() {
    // Устанавливаем русскую локаль
    setlocale(LC_ALL, "Russian");

    int n; // Количество узлов в дереве
    std::cout << "Введите количество узлов в дереве: ";
    std::cin >> n;

    int* arr = new int[n];
    for (int i = 1; i <= n; i++) {
        arr[i - 1] = i;
    }

    TreeNode* root = createBalancedBST(arr, 0, n - 1);

    // Вывод структуры дерева
    std::cout << "Структура дерева:" << std::endl;
    printTreeStructure(root, 0);

    int edgeCount = getEdgeCount(root); // Подсчет количества ребер
    int sum = getSum(root);
    double average = static_cast<double>(sum) / n;

    // Руссифицированный вывод
    std::cout << "Высота дерева: " << getHeight(root) << " (высота дерева)" << std::endl;
    std::cout << "Количество ребер в дереве: " << edgeCount - 1 << " (количество ребер)" << std::endl;
    std::cout << "Среднее арифметическое всех чисел в дереве: " << average << " (среднее арифметическое)" << std::endl;

    delete[] arr;
    return 0;
}
