#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

struct Record {
    string phoneNumber;
    string address;
};

class HashTable {
private:
    int TABLE_SIZE;
    Record* table;
    bool* isOccupied;
    int* lineNumbers;
    int size;

public:
    HashTable(int initialSize = 10) : size(0) {
        TABLE_SIZE = initialSize;
        table = new Record[TABLE_SIZE];
        isOccupied = new bool[TABLE_SIZE];
        lineNumbers = new int[TABLE_SIZE];

        for (int i = 0; i < TABLE_SIZE; i++) {
            isOccupied[i] = false;
            lineNumbers[i] = 0;
        }
    }

    ~HashTable() {
        delete[] table;
        delete[] isOccupied;
        delete[] lineNumbers;
    }

    int hash(const string& key) const {
        std::hash<std::string> stringHash;
        return stringHash(key) % TABLE_SIZE;
    }


    int doubleHash(const string& key, int attempt) const {
        return (2 + attempt) % TABLE_SIZE;
    }

    void insertLine(int index, int line) {
        lineNumbers[index] = line;
    }

    int getLine(int index) const {
        return lineNumbers[index];
    }

    void resizeAndRehash() {
        int newTableSize = TABLE_SIZE * 2;
        Record* newTable = new Record[newTableSize];
        bool* newIsOccupied = new bool[newTableSize];
        int* newLineNumbers = new int[newTableSize];

        for (int i = 0; i < newTableSize; i++) {
            newIsOccupied[i] = false;
            newLineNumbers[i] = 0;
        }

        for (int i = 0; i < TABLE_SIZE; i++) {
            if (isOccupied[i]) {
                Record record = table[i];
                string key = record.phoneNumber;
                int index = hash(key);
                int j = 0;

                while (newIsOccupied[index]) {
                    index = (index + j * doubleHash(key, j)) % newTableSize;
                    j++;
                }

                newTable[index] = record;
                newIsOccupied[index] = true;
                newLineNumbers[index] = getLine(i);
            }
        }

        delete[] table;
        delete[] isOccupied;
        delete[] lineNumbers;

        table = newTable;
        isOccupied = newIsOccupied;
        lineNumbers = newLineNumbers;

        TABLE_SIZE = newTableSize;
    }

    void insertRecord(const Record& record, int line) {
        string key = record.phoneNumber;
        int index = hash(key);
        int i = 0;

        while (isOccupied[index]) {
            index = (index + i * doubleHash(key, i)) % TABLE_SIZE;
            i++;
        }

        table[index] = record;
        isOccupied[index] = true;
        lineNumbers[index] = line;
        size++;

        if (size >= TABLE_SIZE * 0.7) {
            resizeAndRehash();
        }
    }

    void deleteRecord(const string& key) {
        int index = searchRecord(key);

        if (index != -1) {
            isOccupied[index] = false;
            size--;
        }
    }

    int searchRecord(const string& key) const {
        int index = hash(key);
        int i = 1;

        auto start = std::chrono::high_resolution_clock::now();

        while (isOccupied[index]) {
            if (table[index].phoneNumber == key) {
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                cout << "Запись найдена в ячейке " << index << endl;
                cout << "Номер телефона(Ключ): " << table[index].phoneNumber << endl;
                cout << "Адрес: " << table[index].address << endl;
                cout << "Номер строки в файле: " << lineNumbers[index] << endl;
                cout << "Время поиска: " << duration.count() << " мкс" << endl;
                return index;
            }
            index = (index + i * doubleHash(key, i)) % TABLE_SIZE;
            i++;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << "Запись не найдена" << endl;
        cout << "Время поиска: " << duration.count() << " мкс" << endl;

        return -1;
    }

    int getTableSize() const {
        return size;
    }

    int getHashTableSize() const {
        return TABLE_SIZE;
    }

    bool isOccupiedAt(int index) const {
        return isOccupied[index];
    }

    const Record* getTable() const {
        return table;
    }
};

void printAllData(const HashTable& hashTable) {
    for (int i = 0; i < hashTable.getHashTableSize(); i++) {
        if (hashTable.isOccupiedAt(i)) {
            cout << "Ячейка " << i << " - ";
            cout << "Номер телефона(ключ): " << hashTable.getTable()[i].phoneNumber << ", ";
            cout << "Номер строки в файле: " << hashTable.getLine(i) << endl;
        }
    }
}

void measureSearchTime(const HashTable& hashTable, const vector<string>& keys) {
    auto start = std::chrono::high_resolution_clock::now();

    for (const string& key : keys) {
        int index = hashTable.searchRecord(key);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Время поиска по номеру: " << duration.count() << " мкс" << endl;
}

void loadDataFromFile(HashTable& hashTable, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }

    Record record;
    int line = 1;

    while (file >> record.phoneNumber >> record.address) {
        hashTable.insertRecord(record, line);
        line++;
    }

    file.close();
}

void saveDataToBinaryFile(const HashTable& hashTable, const string& filename) {
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }

    for (int i = 0; i < hashTable.getHashTableSize(); i++) {
        if (hashTable.isOccupiedAt(i)) {
            file.write(reinterpret_cast<const char*>(&hashTable.getTable()[i]), sizeof(Record));
        }
    }

    file.close();
}

int main() {
    setlocale(0, "rus");
    HashTable hashTable;

    loadDataFromFile(hashTable, "data.txt");
    saveDataToBinaryFile(hashTable, "data.bin");

    while (true) {
        cout << "Меню:" << endl;
        cout << "1. Добавить запись" << endl;
        cout << "2. Найти запись" << endl;
        cout << "3. Удалить запись" << endl;
        cout << "4. Просмотреть все записи" << endl;
        cout << "5. Выйти" << endl;
        cout << "Выберите действие (1-5): ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string phoneNumber, address;

            cout << "Введите номер телефона: ";
            cin >> phoneNumber;
            cout << "Введите адрес: ";
            cin.ignore();
            getline(cin, address);

            Record record = { phoneNumber, address };
            hashTable.insertRecord(record, hashTable.getTableSize() + 1);
            cout << "Запись добавлена." << endl;
            break;
        }
        case 2: {
            string key;
            cout << "Введите номер телефона для поиска: ";
            cin >> key;
            hashTable.searchRecord(key);
            break;
        }
        case 3: {
            string key;
            cout << "Введите номер телефона для удаления: ";
            cin >> key;
            hashTable.deleteRecord(key);
            cout << "Запись удалена." << endl;
            break;
        }
        case 4: {
            cout << "Все записи:" << endl;
            printAllData(hashTable);
            break;
        }
        case 5:
            saveDataToBinaryFile(hashTable, "data.bin");
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Пожалуйста, введите число от 1 до 5." << endl;
            break;
        }
    }

    return 0;
}
