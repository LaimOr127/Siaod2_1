#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Function to create a text file with decimal numbers
// Function to create a text file with random decimal numbers
void createFile(string fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 1; i <= 10; i++) {
            int num = rand() % 10; // Генерируем случайное десятичное число от 0 до 9
            file << num << " ";
            if (i % 5 == 0) {
                file << endl;
            }
        }
        file.close();
        cout << "File created successfully." << endl;
    }
    else {
        cout << "Error: Unable to create file." << endl;
    }
}


// Function to output the contents of a text file
void readFile(string fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to add a new record to the end of a text file
void appendFile(string fileName, int number) {
    ofstream file(fileName, ios::app);
    if (file.is_open()) {
        file << number << endl;
        file.close();
        cout << "Record added successfully." << endl;
    }
    else {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to read a number from a text file by its ordinal number and return its value
// Function to read a number from a text file by its ordinal number and return its value
int readNumber(string fileName, int index) {
    ifstream file(fileName);
    if (file.is_open()) {
        int number;
        int currentIndex = 1;
        while (file >> number) {
            if (currentIndex == index) {
                file.close();
                return number;
            }
            currentIndex++;
        }

        file.close();
        cout << "Error: Index out of range." << endl;
        return -1;
    }
    else {
        cout << "Error: Unable to open file." << endl;
        return -1;
    }
}


// Function to determine the number of numbers in a text file
int countNumbers(string fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        int count = 0;
        int number;
        while (file >> number) {
            count++;
        }
        file.close();
        return count;
    }
    else {
        cout << "Error: Unable to open file." << endl;
        return -1;
    }
}

void createFileIfNotExists(string fileName) {
    ifstream file(fileName);
    if (!file.good()) {
        // File does not exist, create it
        ofstream newFile(fileName);
        if (newFile.is_open()) {
            newFile.close();
            cout << "File created successfully." << endl;
        }
        else {
            cout << "Error: Unable to create file." << endl;
        }
    }
    else {
        cout << "File already exists." << endl;
    }
}
// Function to create a new file with random numbers
void createNewFile(string fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        int count = countNumbers(fileName);
        int min = count;
        int max = count * 10;
        srand(time(NULL));
        ofstream newFile("new_" + fileName);
        if (newFile.is_open()) {
            for (int i = 1; i <= count; i++) {
                int number = rand() % (max - min + 1) + min;
                newFile << number << " ";
                if (i % 5 == 0) {
                    newFile << endl;
                }
            }
            newFile.close();
            cout << "New file created successfully." << endl;
        }
        else {
            cout << "Error: Unable to create new file." << endl;
        }
    }
    else {
        cout << "Error: Unable to open file." << endl;
    }
}

int main() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    // Check if file exists and can be opened
    ifstream file(fileName);
    if (!file.good()) {
        cout << "Error: File does not exist or cannot be opened." << endl;
        createFileIfNotExists(fileName);
    }
    file.close();

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Create file" << endl;
        cout << "2. Read file" << endl;
        cout << "3. Append file" << endl;
        cout << "4. Read number" << endl;
        cout << "5. Count numbers" << endl;
        cout << "6. Create new file with random numbers" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            createFile(fileName);
            break;
        case 2:
            readFile(fileName);
            break;
        case 3:
            int number;
            cout << "Enter number to append: ";
            cin >> number;
            appendFile(fileName, number);
            break;
        case 4:
            int index;
            cout << "Enter index of number to read: ";
            cin >> index;
            cout << "Number at index " << index << " is " << readNumber(fileName, index) << endl;
            break;
        case 5:
            cout << "Number of numbers in file is " << countNumbers(fileName) << endl;
            break;
        case 6:
            createNewFile(fileName);
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}