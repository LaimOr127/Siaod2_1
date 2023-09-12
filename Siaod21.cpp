// 20 вариант

//#include <iostream>
//#include <bitset>
//
//int main() {
//    setlocale(LC_ALL, "Russian"); // Установка русской локали
//    while (true) {
//        std::cout << "Выберите упражнение (1-5) или 0 для выхода:" << std::endl;
//        std::cout << "1. Установить 1-ый, 5-ый и 7-ой бит в 1, используя маску (вариант 1)." << std::endl;
//        std::cout << "2. Обнулить 2, 3, 4, 5 биты, используя маску (вариант 2)." << std::endl;
//        std::cout << "3. Умножить значение на 16." << std::endl;
//        std::cout << "4. Разделить значение на 8." << std::endl;
//        std::cout << "5. Установить n-ый бит в 1, используя маску (вариант 1)." << std::endl;
//        int exercise;
//        std::cin >> exercise;
//
//        if (exercise == 0) {
//            break; // Выход из цикла при вводе 0
//        }
//
//        if (exercise < 1 || exercise > 5) {
//            std::cout << "Некорректный выбор упражнения. Пожалуйста, выберите снова." << std::endl;
//            continue; // Переход к следующей итерации цикла
//        }
//
//        switch (exercise) {
//        case 1: {
//            // Упражнение 1: Установить 1-ый, 5-ый и 7-ой бит в 1, используя маску (вариант 1)
//            unsigned int value1 = 0x00; // Исходное значение
//
//            // Маска для установки битов в 1: 0b01001001
//            unsigned int mask1 = 0x49;
//
//            value1 |= mask1;
//
//            std::cout << "Результат упражнения 1: " << std::bitset<8>(value1) << std::endl;
//            break;
//        }
//        case 2: {
//            // Упражнение 2: Обнулить 2, 3, 4, 5 биты, используя маску (вариант 2)
//            unsigned int value2;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> std::hex >> value2)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите шестнадцатеричное значение." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            // Маска для обнуления битов: 0b11110000
//            unsigned int mask2 = 0xF0;
//
//            value2 &= ~mask2;
//
//            std::cout << "Результат упражнения 2: " << std::bitset<8>(value2) << std::endl;
//            break;
//        }
//        case 3: {
//            // Упражнение 3: Умножить значение на 16
//            int value3;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> value3)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            value3 <<= 4; // Сдвиг влево на 4 бита эквивалентен умножению на 16
//
//            std::cout << "Результат упражнения 3: " << value3 << std::endl;
//            break;
//        }
//        case 4: {
//            // Упражнение 4: Разделить значение на 8
//            int value4;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> value4)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            value4 >>= 3; // Сдвиг вправо на 3 бита эквивалентен делению на 8
//
//            std::cout << "Результат упражнения 4: " << value4 << std::endl;
//            break;
//        }
//        case 5: {
//            // Упражнение 5: Установить n-ый бит в 1, используя маску (вариант 1)
//            int value5;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> value5)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            int n;
//            std::cout << "Введите номер бита для установки в 1: ";
//            if (!(std::cin >> n) || n < 0 || n > 31) {
//                std::cout << "Ошибка при вводе номера бита. Пожалуйста, введите корректное значение." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            // Маска для установки n-го бита в 1
//            int mask5 = 1 << n;
//
//            value5 |= mask5;
//
//            std::cout << "Результат упражнения 5: " << value5 << std::endl;
//            break;
//        }
//        }
//    }
//
//    return 0;




////18 вариант
//#include <iostream>
//#include <bitset>
//#include <locale.h>
//
//int main() {
//    setlocale(LC_ALL, "Russian"); // Установка русской локали
//
//    while (true) {
//        std::cout << "Выберите упражнение (1-5) или 0 для выхода:" << std::endl;
//        std::cout << "1. Установить 3-й, 5-й и 8-й бит в 1, используя маску (вариант 1)." << std::endl;
//        std::cout << "2. Обнулить 4, 5, 6, 7 биты, используя маску (вариант 2)." << std::endl;
//        std::cout << "3. Умножить значение на 16." << std::endl;
//        std::cout << "4. Разделить значение на 16." << std::endl;
//        std::cout << "5. Обнулить n-ый бит, используя маску (вариант 1)." << std::endl;
//
//        int exercise;
//        std::cin >> exercise;
//
//        if (exercise == 0) {
//            break; // Выход из цикла при вводе 0
//        }
//
//        if (exercise < 1 || exercise > 5) {
//            std::cout << "Некорректный выбор упражнения. Пожалуйста, выберите снова." << std::endl;
//            continue; // Переход к следующей итерации цикла
//        }
//
//        switch (exercise) {
//        case 1: {
//            // Упражнение 1: Установить 3-й, 5-й и 8-й бит в 1, используя маску (вариант 1)
//            unsigned int value1 = 0x00; // Исходное значение
//
//            // Маска для установки битов в 1: 0b00101001
//            unsigned int mask1 = 0x29;
//
//            value1 |= mask1;
//
//            std::cout << "Результат упражнения 1: " << std::bitset<8>(value1) << std::endl;
//            break;
//        }
//        case 2: {
//            // Упражнение 2: Обнулить 4, 5, 6, 7 биты, используя маску (вариант 2)
//            unsigned int value2;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> std::hex >> value2)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите шестнадцатеричное значение." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            // Маска для обнуления битов: 0b11110000
//            unsigned int mask2 = 0xF0;
//
//            value2 &= ~mask2;
//
//            std::cout << "Результат упражнения 2: " << std::bitset<8>(value2) << std::endl;
//            break;
//        }
//        case 3: {
//            // Упражнение 3: Умножить значение на 16
//            int value3;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> value3)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            value3 <<= 4; // Сдвиг влево на 4 бита эквивалентен умножению на 16
//
//            std::cout << "Результат упражнения 3: " << value3 << std::endl;
//            break;
//        }
//        case 4: {
//            // Упражнение 4: Разделить значение на 16
//            int value4;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> value4)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            value4 >>= 4; // Сдвиг вправо на 4 бита эквивалентен делению на 16
//
//            std::cout << "Результат упражнения 4: " << value4 << std::endl;
//            break;
//        }
//        case 5: {
//            // Упражнение 5: Обнулить n-ый бит, используя маску (вариант 1)
//            int value5;
//            std::cout << "Введите значение переменной: ";
//            if (!(std::cin >> value5)) {
//                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            int n;
//            std::cout << "Введите номер бита для обнуления: ";
//            if (!(std::cin >> n) || n < 0 || n > 31) {
//                std::cout << "Ошибка при вводе номера бита. Пожалуйста, введите корректное значение." << std::endl;
//                std::cin.clear(); // Сброс состояния потока
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
//                continue; // Переход к следующей итерации цикла
//            }
//
//            // Маска для обнуления n-го бита
//            int mask5 = ~(1 << n);
//
//            value5 &= mask5;
//
//            std::cout << "Результат упражнения 5: " << value5 << std::endl;
//            break;
//        }
//        }
//    }
//
//    return 0;
//}

//Второе задание с использованием визуальной библиотеки QT
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cctype>
#include <QtWidgets/QApplication>
#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QPushButton>

const int MAX_DIGIT = 7; // Максимальная цифра в семизначных числах
const int NUM_DIGITS = 10; // Количество возможных цифр (0-9)

// Функция для генерации случайных семизначных чисел
int generateRandomNumber() {
    return rand() % 9000000 + 1000000;
}

// Функция для ввода семизначных чисел с проверкой на корректность
int inputSevenDigitNumber() {
    int num;
    while (true) {
        std::cout << "Введите семизначное число: ";
        if (!(std::cin >> num) || num < 1000000 || num > 9999999) {
            std::cout << "Ошибка: Введите корректное семизначное число." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    return num;
}

// Функция для слияния двух отсортированных массивов
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Функция для сортировки массива методом слияния
void mergeSort(std::vector<int>& arr, int left, int right, QProgressDialog& progressDialog) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle, progressDialog);
        mergeSort(arr, middle + 1, right, progressDialog);

        merge(arr, left, middle, right);

        // Обновление полосы прогресса
        progressDialog.setValue(progressDialog.value() + 1);
        QCoreApplication::processEvents(); // Позволяет обновить графический интерфейс
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    std::vector<int> numbers; // Список семизначных чисел

    // Генерация случайных семизначных чисел
    std::cout << "Генерация случайных семизначных чисел..." << std::endl;
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < 10000000; i++) {
        numbers.push_back(generateRandomNumber());
    }

    // Создание диалогового окна с полосой прогресса
    QProgressDialog progressDialog("Сортировка...", "Отмена", 0, numbers.size());
    progressDialog.setWindowTitle("Процесс сортировки");
    progressDialog.setWindowModality(Qt::WindowModal);
    progressDialog.setMinimumDuration(0);
    progressDialog.setAutoClose(true);

    // Связываем событие отмены с закрытием приложения
    QObject::connect(&progressDialog, &QProgressDialog::canceled, &app, &QApplication::quit);

    // Сортировка чисел с использованием сортировки слиянием
    std::cout << "Сортировка чисел..." << std::endl;
    progressDialog.show();
    mergeSort(numbers, 0, numbers.size() - 1, progressDialog);

    // Вывод первых 10 отсортированных чисел
    std::cout << "Первые 10 отсортированных семизначных чисел:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    return app.exec();
}
