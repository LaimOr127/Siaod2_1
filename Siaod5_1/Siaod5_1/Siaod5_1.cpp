#include <iostream>
#include <string>

struct TreeNode {
    std::string owner;
    std::string phoneNumber;
    std::string fileRecord;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& owner, const std::string& phoneNumber, const std::string& fileRecord)
        : owner(owner), phoneNumber(phoneNumber), fileRecord(fileRecord), left(nullptr), right(nullptr) {}
};

class SkewedBinarySearchTree {
private:
    TreeNode* root;

public:
    SkewedBinarySearchTree() : root(nullptr) {}

    TreeNode* insert(TreeNode* root, const std::string& owner, const std::string& phoneNumber, const std::string& fileRecord) {
        if (root == nullptr) {
            return new TreeNode(owner, phoneNumber, fileRecord);
        }

        if (owner < root->owner) {
            root->left = insert(root->left, owner, phoneNumber, fileRecord);
        }
        else {
            root->right = insert(root->right, owner, phoneNumber, fileRecord);
        }

        return root;
    }

    void insert(const std::string& owner, const std::string& phoneNumber, const std::string& fileRecord) {
        root = insert(root, owner, phoneNumber, fileRecord);
    }

    TreeNode* search(TreeNode* root, const std::string& owner) {
        if (root == nullptr || root->owner == owner) {
            return root;
        }

        if (owner < root->owner) {
            return search(root->left, owner);
        }
        else {
            return search(root->right, owner);
        }
    }

    TreeNode* deleteNode(TreeNode* root, const std::string& owner) {
        if (root == nullptr) {
            return root;
        }

        if (owner < root->owner) {
            root->left = deleteNode(root->left, owner);
        }
        else if (owner > root->owner) {
            root->right = deleteNode(root->right, owner);
        }
        else {
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            TreeNode* temp = findMin(root->right);
            root->owner = temp->owner;
            root->phoneNumber = temp->phoneNumber;
            root->fileRecord = temp->fileRecord;
            root->right = deleteNode(root->right, temp->owner);
        }

        return root;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void printTree(TreeNode* root, int level) {
        if (root != nullptr) {
            printTree(root->right, level + 1);
            for (int i = 0; i < level; ++i) {
                std::cout << "   ";
            }
            std::cout << root->owner << " (" << root->phoneNumber << ") " << root->fileRecord << std::endl;
            printTree(root->left, level + 1);
        }
    }

    void inOrderTraversal(TreeNode* root, int level) {
        if (root != nullptr) {
            inOrderTraversal(root->right, level + 1);
            for (int i = 0; i < level; ++i) {
                std::cout << "   ";
            }
            std::cout << root->owner << " (" << root->phoneNumber << ") " << root->fileRecord << std::endl;
            inOrderTraversal(root->left, level + 1);
        }
    }

    void printTreeReverse() {
        printTreeReverse(root, 0);
    }

    void printTreeReverse(TreeNode* root, int level) {
        if (root != nullptr) {
            printTreeReverse(root->right, level + 1);
            for (int i = 0; i < level; ++i) {
                std::cout << "   ";
            }
            std::cout << root->owner << " (" << root->phoneNumber << ") " << root->fileRecord << std::endl;
            printTreeReverse(root->left, level + 1);
        }
    }

    void printMenu() {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Insert" << std::endl;
        std::cout << "2. Search" << std::endl;
        std::cout << "3. Delete" << std::endl;
        std::cout << "4. Print Tree" << std::endl;
        std::cout << "5. Print Tree in Reverse" << std::endl;
        std::cout << "6. Print In-Order Traversal" << std::endl;
        std::cout << "7. Exit" << std::endl;
    }

    void handleUserInput() {
        int choice;
        std::string owner, phoneNumber, fileRecord;
        TreeNode* result = nullptr;

        while (true) {
            printMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                std::cout << "Enter owner, phone number, and file record to insert: ";
                std::cin >> owner >> phoneNumber >> fileRecord;
                insert(owner, phoneNumber, fileRecord);
                break;

            case 2:
                std::cout << "Enter owner to search: ";
                std::cin >> owner;
                result = search(root, owner);
                if (result != nullptr) {
                    std::cout << "Found: " << result->owner << " (" << result->phoneNumber << ") " << result->fileRecord << std::endl;
                }
                else {
                    std::cout << "Not Found" << std::endl;
                }
                break;

            case 3:
                std::cout << "Enter owner to delete: ";
                std::cin >> owner;
                root = deleteNode(root, owner);
                break;

            case 4:
                std::cout << "Print Tree:" << std::endl;
                printTree(root, 0);
                break;

            case 5:
                std::cout << "Print Tree in Reverse:" << std::endl;
                printTreeReverse(root, 0);
                break;

            case 6:
                std::cout << "Print In-Order Traversal:" << std::endl;
                inOrderTraversal(root, 0);
                break;

            case 7:
                return;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }

    void test() {
        insert("Alice", "123-456-7890", "record1");
        insert("Bob", "987-654-3210", "record2");
        insert("Charlie", "555-123-4567", "record3");
        insert("Alex", "333-333-333", "record4");
        insert("Boby", "444-444-444", "record5");
        insert("Den", "555-555-555", "record6");

        std::cout << "Print Skewed Tree Reverse:" << std::endl;
        printTreeReverse();

        handleUserInput();
    }
};

int main() {
    SkewedBinarySearchTree sbst;
    sbst.test();

    return 0;
}
