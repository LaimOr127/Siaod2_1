#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>
#include <limits>
#include <random>
#include <chrono>

struct Record {
    std::string phone;
    std::string address;

    Record() : phone(""), address("") {}
};

class HashTable {
private:
    int tableSize;
    Record* table;
    int* status;

    int hash1(const std::string& key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % tableSize;
    }

    int hash2(const std::string& key) {
        int prime = 31;
        int hash = 0;
        for (char c : key) {
            hash = (hash * prime) + c;
        }
        return (hash % (tableSize - 1)) + 1;
    }

    void rehash() {
        int newTableSize = tableSize * 2;
        Record* newTable = new Record[newTableSize]();
        int* newStatus = new int[newTableSize]();

        for (int i = 0; i < tableSize; ++i) {
            if (status[i] == 1) {
                Record& record = table[i];
                int index = hash1(record.phone) % newTableSize;
                int step = hash2(record.phone);
                int j = 0;

                while (newStatus[index] == 1) {
                    index = (index + step * j) % newTableSize;
                    j++;
                }

                newTable[index] = record;
                newStatus[index] = 1;
            }
        }

        delete[] table;
        delete[] status;
        table = newTable;
        status = newStatus;
        tableSize = newTableSize;
    }

public:
    HashTable(int size) : tableSize(size) {
        table = new Record[tableSize]();
        status = new int[tableSize]();
    }

    ~HashTable() {
        delete[] table;
        delete[] status;
    }

    int hash(const std::string& key, int i) {
        return (hash1(key) + i * hash2(key)) % tableSize;
    }

    void insert(const Record& record) {
        if (size() >= (7 * tableSize) / 10) {
            rehash();
        }

        int index = hash1(record.phone);
        int step = hash2(record.phone);
        int i = 0;

        while (status[index] == 1) {
            index = (index + step * i) % tableSize;
            i++;
        }

        table[index] = record;
        status[index] = 1;
    }

    void remove(const std::string& phone) {
        int index = hash1(phone);
        int step = hash2(phone);
        int i = 0;

        while (status[index] != 0) {
            if (status[index] == 1 && table[index].phone == phone) {
                status[index] = 2;
                return;
            }
            index = (index + step * i) % tableSize;
            i++;
        }
    }

    Record* search(const std::string& phone, bool findInMiddle = false) {
        int start = 0;
        int end = tableSize - 1;

        if (findInMiddle) {
            start = tableSize / 3;
            end = (2 * tableSize) / 3;
        }

        for (int index = start; index <= end; ++index) {
            if (status[index] == 1 && table[index].phone == phone) {
                return &table[index];
            }
        }

        return nullptr;
    }

    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (status[i] == 1) {
                std::cout << "Phone: " << table[i].phone << ", Address: " << table[i].address << std::endl;
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

    void writeToDisk(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);

        if (file.is_open()) {
            for (int i = 0; i < tableSize; i++) {
                if (status[i] == 1) {
                    file.write(table[i].phone.c_str(), 10);
                    int addressLength = table[i].address.length();
                    file.write(reinterpret_cast<char*>(&addressLength), sizeof(int));
                    file.write(table[i].address.c_str(), addressLength);
                }
            }
            file.close();
        }
        else {
            std::cerr << "Ошибка открытия файла для записи." << std::endl;
        }
    }

    void readFromDisk(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);

        if (file.is_open()) {
            while (file) {
                Record record;
                file.read(&record.phone[0], 10);
                if (file.eof()) {
                    break;
                }
                int addressLength = 0;
                file.read(reinterpret_cast<char*>(&addressLength), sizeof(int));
                record.address.resize(addressLength);
                file.read(&record.address[0], addressLength);
                insert(record);
            }
            file.close();
        }
        else {
            std::cerr << "Ошибка открытия файла для чтения." << std::endl;
        }
    }
};

void generateRandomData(HashTable& hashTable, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> phoneDist(1000000000, 9999999999);
    std::vector<std::string> cities = { "CityA", "CityB", "CityC", "CityD", "CityE" };

    for (int i = 0; i < count; ++i) {
        Record record;
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

    std::string filename = "hash_table.dat";
    hashTable.readFromDisk(filename);

    while (true) {
        int choice;
        std::cout << "1. Вставить запись" << std::endl;
        std::cout << "2. Удалить запись" << std::endl;
        std::cout << "3. Поиск записи" << std::endl;
        std::cout << "4. Поиск записи в середине таблицы" << std::endl;
        std::cout << "5. Вывести хеш-таблицу" << std::endl;
        std::cout << "6. Генерировать случайные записи" << std::endl;
        std::cout << "7. Сохранить таблицу в файл" << std::endl;
        std::cout << "8. Загрузить таблицу из файл" << std::endl;
        std::cout << "9. Выход" << std::endl;

        while (!(std::cin >> choice) || choice < 1 || choice > 9) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Ошибка ввода. Введите число от 1 до 9." << std::endl;
        }

        if (choice == 1) {
            Record record;
            std::cout << "Введите номер телефона (10 символов): ";
            std::cin >> record.phone;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите адрес: ";
            std::getline(std::cin, record.address);
            hashTable.insert(record);
        }
        else if (choice == 2) {
            std::string phone;
            std::cout << "Введите номер телефона для удаления: ";
            std::cin >> phone;
            hashTable.remove(phone);
        }
        else if (choice == 3) {
            std::string phone;
            std::cout << "Введите номер телефона для поиска: ";
            std::cin >> phone;

            auto start = std::chrono::high_resolution_clock::now();
            Record* found = hashTable.search(phone);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            if (found) {
                std::cout << "Найдена запись: Phone: " << found->phone << ", Address: " << found->address << std::endl;
            }
            else {
                std::cout << "Запись не найдена." << std::endl;
            }

            std::cout << "Время поиска: " << elapsed.count() << " секунд" << std::endl;
        }
        else if (choice == 4) {
            std::string phone;
            std::cout << "Введите номер телефона для поиска в середине таблицы: ";
            std::cin >> phone;

            auto start = std::chrono::high_resolution_clock::now();
            Record* found = hashTable.search(phone, true);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            if (found) {
                std::cout << "Найдена запись: Phone: " << found->phone << ", Address: " << found->address << std::endl;
            }
            else {
                std::cout << "Запись не найдена." << std::endl;
            }

            std::cout << "Время поиска в середине таблицы: " << elapsed.count() << " секунд" << std::endl;
        }
        else if (choice == 5) {
            hashTable.printTable();
        }
        else if (choice == 6) {
            int dataCount;
            std::cout << "Введите количество записей для генерации: ";
            std::cin >> dataCount;
            generateRandomData(hashTable, dataCount);
        }
        else if (choice == 7) {
            std::string filename;
            std::cout << "Введите имя файла для сохранения: ";
            std::cin >> filename;
            hashTable.writeToDisk(filename);
            std::cout << "Таблица сохранена в файл " << filename << std::endl;
        }
        else if (choice == 8) {
            std::string filename;
            std::cout << "Введите имя файла для загрузки: ";
            std::cin >> filename;
            hashTable.readFromDisk(filename);
            std::cout << "Таблица загружена из файла " << filename << std::endl;
        }
        else if (choice == 9) {
            break;
        }
    }

    return 0;
}
