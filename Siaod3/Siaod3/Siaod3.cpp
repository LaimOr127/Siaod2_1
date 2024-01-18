#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>
#include <limits>
#include <random>
#include <chrono>

struct Record {
    int key; // Ключ записи
    std::string phone;
    std::string address;

    Record() : key(0), phone(""), address("") {}
};

class HashTable {
private:
    int tableSize;
    Record* table;
    int* status; // Статусы для элементов в таблице (0 - пусто, 1 - активно, 2 - удалено)
    int* keys; // Массив ключей

    int hash1(int key) {
        return key % tableSize; // Хеш-функция 1
    }

    int hash2(int key) {
        return 1 + (key % (tableSize - 1)); // Хеш-функция 2
    }

    void rehash() {
        int newTableSize = tableSize * 2;
        Record* newTable = new Record[newTableSize]();
        int* newStatus = new int[newTableSize]();
        int* newKeys = new int[newTableSize]();

        for (int i = 0; i < tableSize; ++i) {
            if (status[i] == 1) {
                Record& record = table[i];
                int key = keys[i];
                int index = hash1(key) % newTableSize;
                int step = hash2(key);
                int j = 0;

                while (newStatus[index] == 1) {
                    index = (index + step * j) % newTableSize;
                    j++;
                }

                newTable[index] = record;
                newStatus[index] = 1;
                newKeys[index] = key;
            }
        }

        delete[] table;
        delete[] status;
        delete[] keys;
        table = newTable;
        status = newStatus;
        keys = newKeys;
        tableSize = newTableSize;
    }

public:
    HashTable(int size) : tableSize(size) {
        table = new Record[tableSize]();
        status = new int[tableSize]();
        keys = new int[tableSize]();
    }

    ~HashTable() {
        delete[] table;
        delete[] status;
        delete[] keys;
    }

    void insert(const Record& record) {
        if (size() >= (7 * tableSize) / 10) {
            rehash(); // Перехеширование при достижении порога заполнения
        }

        int key = record.key;
        int index = hash1(key);
        int step = hash2(key);
        int i = 0;

        while (status[index] == 1) {
            index = (index + step * i) % tableSize;
            i++;
        }

        table[index] = record;
        status[index] = 1;
        keys[index] = key;
    }

    void remove(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int i = 0;

        while (status[index] != 0) {
            if (status[index] == 1 && keys[index] == key) {
                status[index] = 2; // Удалено
                return;
            }
            index = (index + step * i) % tableSize;
            i++;
        }
    }

    Record* search(int key) {
        for (int index = 0; index < tableSize; ++index) {
            if (status[index] == 1 && keys[index] == key) {
                return &table[index];
            }
        }

        return nullptr;
    }

    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (status[i] == 1) {
                std::cout << "Key: " << keys[i] << ", Phone: " << table[i].phone << ", Address: " << table[i].address << std::endl;
            }
        }
    }

    int size() {
        int count = 0;
        for (int i = 0; i < tableSize; ++i) {
            if (status[i] == 1) {
                count++;
            }
        }
        return count;
    }
};

void generateRandomData(HashTable& hashTable, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> keyDist(1000, 9999);
    std::uniform_int_distribution<int> phoneDist(1000000000, 9999999999);
    std::vector<std::string> cities = { "CityA", "CityB", "CityC", "CityD", "CityE" };

    for (int i = 0; i < count; ++i) {
        Record record;
        record.key = keyDist(gen);
        record.phone = std::to_string(phoneDist(gen));
        record.address = cities[i % cities.size()];
        hashTable.insert(record);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int tableSize;
    std::cout << "Введите размер хеш-таблицы: ";
    std::cin >> tableSize;
    HashTable hashTable(tableSize);

    while (true) {
        int choice;
        std::cout << "1. Вставить запись" << std::endl;
        std::cout << "2. Удалить запись" << std::endl;
        std::cout << "3. Поиск записи" << std::endl;
        std::cout << "4. Вывести хеш-таблицу" << std::endl;
        std::cout << "5. Генерировать случайные записи" << std::endl;
        std::cout << "6. Выход" << std::endl;

        while (!(std::cin >> choice) || choice < 1 || choice > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Ошибка ввода. Введите число от 1 до 6." << std::endl;
        }

        if (choice == 1) {
            Record record;
            std::cout << "Введите ключ (целое число): ";
            std::cin >> record.key;
            std::cout << "Введите номер телефона (10 символов): ";
            std::cin.ignore();
            std::getline(std::cin, record.phone);
            std::cout << "Введите адрес: ";
            std::getline(std::cin, record.address);
            hashTable.insert(record);
        }
        else if (choice == 2) {
            int key;
            std::cout << "Введите ключ для удаления: ";
            std::cin >> key;
            hashTable.remove(key);
        }
        else if (choice == 3) {
            int key;
            std::cout << "Введите ключ для поиска: ";
            std::cin >> key;

            auto start = std::chrono::high_resolution_clock::now();
            Record* found = hashTable.search(key);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            if (found) {
                std::cout << "Найдена запись: Key: " << found->key << ", Phone: " << found->phone << ", Address: " << found->address << std::endl;
            }
            else {
                std::cout << "Запись не найдена." << std::endl;
            }

            std::cout << "Время поиска: " << elapsed.count() << " секунд" << std::endl;
        }
        else if (choice == 4) {
            hashTable.printTable();
        }
        else if (choice == 5) {
            int count;
            std::cout << "Введите количество случайных записей для генерации: ";
            std::cin >> count;
            generateRandomData(hashTable, count);
        }
        else if (choice == 6) {
            break;
        }
    }

    return 0;
}
