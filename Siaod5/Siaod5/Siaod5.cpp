#include <iostream>
#include <fstream>
#include <cstdlib> // for std::rand and std::srand
#include <ctime>   // for std::time

class TreeNode {
public:
    int key;
    long filePosition;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k, long pos) : key(k), filePosition(pos), left(nullptr), right(nullptr) {}
};

class FileManager {
private:
    std::fstream file;

public:
    FileManager(const std::string& filename) {
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            file.open(filename, std::ios::out | std::ios::binary);
            file.close();
            file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        }
    }

    ~FileManager() {
        file.close();
    }

    long appendRecord(int key) {
        file.seekp(0, std::ios::end);
        long position = file.tellp();

        file.write(reinterpret_cast<const char*>(&key), sizeof(int));

        return position;
    }

    void readRecord(long position, int& key) {
        file.seekg(position);
        file.read(reinterpret_cast<char*>(&key), sizeof(int));
    }
};

class BinarySearchTree {
private:
    TreeNode* root;
    FileManager fileManager;

public:
    BinarySearchTree(const std::string& filename) : root(nullptr), fileManager(filename) {}

    void insert(int key) {
        long position = fileManager.appendRecord(key);
        root = insertRecursive(root, key, position);
    }

    bool search(int key) {
        return searchRecursive(root, key);
    }

    void remove(int key) {
        root = removeRecursive(root, key);
    }

    void display() {
        displayRecursive(root, 0);
        std::cout << std::endl;
    }

    void generateRandomTree(int size) {
        std::srand(std::time(0)); // seed for std::rand based on current time

        for (int i = 0; i < size; ++i) {
            int randomKey = std::rand() % 100; // Adjust range as needed
            insert(randomKey);
        }
    }

private:
    TreeNode* insertRecursive(TreeNode* node, int key, long position) {
        if (node == nullptr) {
            return new TreeNode(key, position);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key, position);
        }
        else if (key > node->key) {
            node->right = insertRecursive(node->right, key, position);
        }

        return node;
    }

    bool searchRecursive(TreeNode* node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key == node->key) {
            return true;
        }
        else if (key < node->key) {
            return searchRecursive(node->left, key);
        }
        else {
            return searchRecursive(node->right, key);
        }
    }

    TreeNode* removeRecursive(TreeNode* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = removeRecursive(node->left, key);
        }
        else if (key > node->key) {
            node->right = removeRecursive(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = findMin(node->right);
            node->key = temp->key;
            node->right = removeRecursive(node->right, temp->key);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void displayRecursive(TreeNode* node, int level) {
        if (node != nullptr) {
            displayRecursive(node->right, level + 1);

            for (int i = 0; i < level; i++) {
                std::cout << "    ";
            }

            std::cout << node->key << std::endl;

            displayRecursive(node->left, level + 1);
        }
    }
};

int main() {
    BinarySearchTree bst("data.dat");

    while (true) {
        std::cout << "1. Insert\n";
        std::cout << "2. Search\n";
        std::cout << "3. Remove\n";
        std::cout << "4. Display\n";
        std::cout << "5. Generate Random Tree\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Enter key to insert: ";
            int key;
            std::cin >> key;
            bst.insert(key);
            std::cout << "Inserted " << key << " into the tree.\n";
            break;
        }
        case 2: {
            std::cout << "Enter key to search: ";
            int key;
            std::cin >> key;
            if (bst.search(key)) {
                std::cout << key << " found in the tree.\n";
                std::cout << key << " - Hi\n";
            }
            else {
                std::cout << key << " not found in the tree.\n";
            }
            break;
        }
        case 3: {
            std::cout << "Enter key to remove: ";
            int key;
            std::cin >> key;
            bst.remove(key);
            std::cout << "Removed " << key << " from the tree.\n";
            break;
        }
        case 4:
            std::cout << "Binary Search Tree:\n";
            bst.display();
            break;
        case 5: {
            std::cout << "Enter the size of the random tree: ";
            int size;
            std::cin >> size;
            bst.generateRandomTree(size);
            std::cout << "Generated a random tree.\n";
            break;
        }
        case 6:
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}