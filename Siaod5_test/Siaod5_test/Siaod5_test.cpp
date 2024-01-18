
#include <iostream>
#include <fstream>
#include <string>

class FileManager {
public:
    FileManager(const std::string& fileName) : fileName(fileName) {}

    void createBinaryFile() {
        std::ifstream inputTextFile(fileName);
        if (!inputTextFile.is_open()) {
            std::cerr << "Ошибка открытия текстового файла." << std::endl;
            return;
        }

        std::ofstream outputBinaryFile("binary_data.dat", std::ios::binary);
        if (!outputBinaryFile.is_open()) {
            std::cerr << "Ошибка создания двоичного файла." << std::endl;
            inputTextFile.close();
            return;
        }

        std::string line;
        while (std::getline(inputTextFile, line)) {
            outputBinaryFile.write(line.c_str(), line.size());
        }

        inputTextFile.close();
        outputBinaryFile.close();
        std::cout << "Двоичный файл успешно создан." << std::endl;
    }

private:
    std::string fileName;
};

class BinarySearchTree {
private:
    struct Node {
        int key;
        std::string data;
        Node* left;
        Node* right;
        Node(int k, const std::string& d) : key(k), data(d), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, int key, const std::string& data) {
        if (node == nullptr) {
            node = new Node(key, data);
        }
        else {
            if (key < node->key) {
                insert(node->left, key, data);
            }
            else if (key > node->key) {
                insert(node->right, key, data);
            }
        }
    }

    bool search(Node* node, int key) const {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        else if (key < node->key) {
            return search(node->left, key);
        }
        else {
            return search(node->right, key);
        }
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }
        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->data = temp->data;
                node->right = remove(node->right, temp->key);
            }
        }
        return node;
    }

    void display(Node* node) const {
        if (node != nullptr) {
            display(node->left);
            std::cout << "Key: " << node->key << ", Data: " << node->data << std::endl;
            display(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key, const std::string& data) {
        insert(root, key, data);
    }

    bool search(int key) const {
        return search(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    void display() const {
        display(root);
    }
};

int main() {
    setlocale(0, "");
    FileManager fileManager("test.txt");
    fileManager.createBinaryFile();

    BinarySearchTree bst;
    bst.insert(10, "Data for key 10");
    bst.insert(5, "Data for key 5");
    bst.insert(15, "Data for key 15");
    bst.insert(3, "Data for key 3");

    std::cout << "Binary Search Tree:" << std::endl;
    bst.display();

    int keyToSearch = 5;
    if (bst.search(keyToSearch)) {
        std::cout << "Key " << keyToSearch << " found in the tree." << std::endl;
    }
    else {
        std::cout << "Key " << keyToSearch << " not found in the tree." << std::endl;
    }

    int keyToDelete = 15;
    bst.remove(keyToDelete);

    std::cout << "Binary Search Tree after deleting key " << keyToDelete << ":" << std::endl;
    bst.display();

    return 0;
}
