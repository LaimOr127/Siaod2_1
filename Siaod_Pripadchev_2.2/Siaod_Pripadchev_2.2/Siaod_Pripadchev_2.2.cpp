#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

const int PRODUCT_CODE_SIZE = 5;
const int PRODUCT_NAME_SIZE = 51;
const int SALE_DATE_SIZE = 11;

// Структура записи о продаже товара
struct SaleRecord {
    char productCode[PRODUCT_CODE_SIZE];
    char productName[PRODUCT_NAME_SIZE];
    double price;
    char saleDate[SALE_DATE_SIZE];
};

// Функция для записи данных в двоичный файл
void writeBinaryFile(const string& filename, const SaleRecord& record) {
    ofstream outFile(filename, ios::binary | ios::app);

    if (!outFile) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&record), sizeof(SaleRecord));
    outFile.close();
}

// Функция для чтения данных из двоичного файла и вывода на экран
void readAndPrintBinaryFile(const string& filename) {
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения." << endl;
        return;
    }

    SaleRecord record;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(SaleRecord))) {
        cout << "Код товара: " << record.productCode << endl;
        cout << "Название: " << record.productName << endl;
        cout << "Цена: " << record.price << endl;
        cout << "Дата продажи: " << record.saleDate << endl;
        cout << "------------------------" << endl;
    }

    inFile.close();
}

// Функция для удаления записи по коду товара
void deleteRecordByProductCode(const string& filename, const char* productCode) {
    ifstream inFile(filename, ios::binary);
    ofstream tempFile("temp.bin", ios::binary);

    if (!inFile || !tempFile) {
        cerr << "Ошибка открытия файлов." << endl;
        return;
    }

    SaleRecord record;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(SaleRecord))) {
        if (strcmp(record.productCode, productCode) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&record), sizeof(SaleRecord));
        }
        else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(filename.c_str());
        rename("temp.bin", filename.c_str());
        cout << "Запись с кодом товара " << productCode << " удалена." << endl;
    }
    else {
        remove("temp.bin");
        cout << "Запись с кодом товара " << productCode << " не найдена." << endl;
    }
}

// Функция для выполнения дополнительной операции 1: подсчет суммы продаж за указанную дату
double calculateTotalSalesByDate(const string& filename, const char* targetDate) {
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения." << endl;
        return 0.0;
    }

    SaleRecord record;
    double totalSales = 0.0;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(SaleRecord))) {
        if (strcmp(record.saleDate, targetDate) == 0) {
            totalSales += record.price;
        }
    }

    inFile.close();
    return totalSales;
}

// Функция для выполнения дополнительной операции 2: создание файла с информацией о продажах
void createSalesInfoFile(const string& sourceFilename, const string& outputFilename) {
    ifstream inFile(sourceFilename, ios::binary);
    ofstream outFile(outputFilename, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Ошибка открытия файлов." << endl;
        return;
    }

    SaleRecord record;
    vector<SaleRecord> salesInfo;

    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(SaleRecord))) {
        salesInfo.push_back(record);
    }

    for (const SaleRecord& rec : salesInfo) {
        int salesCount = 0;

        for (const SaleRecord& r : salesInfo) {
            if (strcmp(r.productCode, rec.productCode) == 0) {
                salesCount++;
            }
        }

        strncpy(record.productCode, rec.productCode, PRODUCT_CODE_SIZE);
        strncpy(record.saleDate, rec.saleDate, SALE_DATE_SIZE);
        record.price = salesCount;
        strncpy(record.productName, to_string(salesCount).c_str(), PRODUCT_NAME_SIZE);
        outFile.write(reinterpret_cast<const char*>(&record), sizeof(SaleRecord));
    }

    inFile.close();
    outFile.close();
    cout << "Файл с информацией о продажах успешно создан." << endl;
}

// Функция для выполнения дополнительной операции 3: расчет выручки
double calculateRevenue(const string& filename) {
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения." << endl;
        return 0.0;
    }

    SaleRecord record;
    double revenue = 0.0;

    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(SaleRecord))) {
        revenue += record.price;
    }

    inFile.close();
    return revenue;
}

// Функция для получения записи по порядковому номеру
SaleRecord getRecordByIndex(const string& filename, int index) {
    ifstream inFile(filename, ios::binary);

    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения." << endl;
        return {};  // Возвращаем пустую запись в случае ошибки
    }

    SaleRecord record;
    int currentIndex = 0;

    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(SaleRecord))) {
        currentIndex++;
        if (currentIndex == index) {
            inFile.close();
            return record;  // Возвращаем найденную запись
        }
    }

    inFile.close();
    return {};  // Возвращаем пустую запись, если запись с указанным индексом не найдена
}

int main() {
    setlocale(LC_ALL, "Russian");

    string filename = "sales.bin";
    int choice;

    while (true) {
        cout << "Выберите операцию:" << endl;
        cout << "1. Записать данные в двоичный файл" << endl;
        cout << "2. Вывести все записи из двоичного файла" << endl;
        cout << "3. Получить запись по порядковому номеру" << endl;
        cout << "4. Удалить запись по коду товара" << endl;
        cout << "5. Посчитать сумму продаж за указанную дату" << endl;
        cout << "6. Сформировать файл с информацией о продажах" << endl;
        cout << "7. Произвести расчет выручки" << endl;
        cout << "8. Выйти" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            SaleRecord record;
            cout << "Введите код товара (максимум 4 символа): ";
            cin >> record.productCode;
            cout << "Введите название товара (максимум 50 символов): ";
            cin.ignore();
            cin.getline(record.productName, PRODUCT_NAME_SIZE);
            cout << "Введите цену: ";
            cin >> record.price;
            cout << "Введите дату продажи (формат: ГГГГ-ММ-ДД): ";
            cin >> record.saleDate;
            writeBinaryFile(filename, record);
            cout << "Данные успешно записаны в файл." << endl;
            break;
        }
        case 2: {
            readAndPrintBinaryFile(filename);
            break;
        }
        case 3: {
            int index;
            cout << "Введите порядковый номер записи: ";
            cin >> index;
            SaleRecord record = getRecordByIndex(filename, index);
            if (strlen(record.productCode) > 0) {
                cout << "Запись по порядковому номеру " << index << ":" << endl;
                cout << "Код товара: " << record.productCode << endl;
                cout << "Название: " << record.productName << endl;
                cout << "Цена: " << record.price << endl;
                cout << "Дата продажи: " << record.saleDate << endl;
            }
            else {
                cout << "Запись с указанным порядковым номером не найдена." << endl;
            }
            break;
        }
        case 4: {
            char productCodeToDelete[PRODUCT_CODE_SIZE];
            cout << "Введите код товара для удаления: ";
            cin >> productCodeToDelete;
            deleteRecordByProductCode(filename, productCodeToDelete);
            break;
        }
        case 5: {
            char targetDate[SALE_DATE_SIZE];
            cout << "Введите дату для подсчета суммы продаж (формат: ГГГГ-ММ-ДД): ";
            cin >> targetDate;
            double totalSales = calculateTotalSalesByDate(filename, targetDate);
            cout << "Сумма продаж за указанную дату: " << totalSales << endl;
            break;
        }
        case 6: {
            string outputFilename = "sales_info.bin";
            createSalesInfoFile(filename, outputFilename);
            break;
        }
        case 7: {
            double revenue = calculateRevenue(filename);
            cout << "Выручка от продаж: " << revenue << endl;
            break;
        }
        case 8: {
            return 0;
        }
        default: {
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
        }
    }

    return 0;
}
