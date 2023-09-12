#include <iostream>
#include <bitset>

int main() {
    setlocale(LC_ALL, "Russian"); // Установка русской локали
    while (true) {
        std::cout << "Выберите упражнение (1-5) или 0 для выхода:" << std::endl;
        std::cout << "1. Установить 1-ый, 5-ый и 7-ой бит в 1, используя маску (вариант 1)." << std::endl;
        std::cout << "2. Обнулить 2, 3, 4, 5 биты, используя маску (вариант 2)." << std::endl;
        std::cout << "3. Умножить значение на 16." << std::endl;
        std::cout << "4. Разделить значение на 8." << std::endl;
        std::cout << "5. Установить n-ый бит в 1, используя маску (вариант 1)." << std::endl;
        int exercise;
        std::cin >> exercise;

        if (exercise == 0) {
            break; // Выход из цикла при вводе 0
        }

        if (exercise < 1 || exercise > 5) {
            std::cout << "Некорректный выбор упражнения. Пожалуйста, выберите снова." << std::endl;
            continue; // Переход к следующей итерации цикла
        }

        switch (exercise) {
        case 1: {
            // Упражнение 1: Установить 1-ый, 5-ый и 7-ой бит в 1, используя маску (вариант 1)
            unsigned int value1 = 0x00; // Исходное значение

            // Маска для установки битов в 1: 0b01001001
            unsigned int mask1 = 0x49;

            value1 |= mask1;

            std::cout << "Результат упражнения 1: " << std::bitset<8>(value1) << std::endl;
            break;
        }
        case 2: {
            // Упражнение 2: Обнулить 2, 3, 4, 5 биты, используя маску (вариант 2)
            unsigned int value2;
            std::cout << "Введите значение переменной: ";
            if (!(std::cin >> std::hex >> value2)) {
                std::cout << "Ошибка при вводе. Пожалуйста, введите шестнадцатеричное значение." << std::endl;
                std::cin.clear(); // Сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                continue; // Переход к следующей итерации цикла
            }

            // Маска для обнуления битов: 0b11110000
            unsigned int mask2 = 0xF0;

            value2 &= ~mask2;

            std::cout << "Результат упражнения 2: " << std::bitset<8>(value2) << std::endl;
            break;
        }
        case 3: {
            // Упражнение 3: Умножить значение на 16
            int value3;
            std::cout << "Введите значение переменной: ";
            if (!(std::cin >> value3)) {
                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
                std::cin.clear(); // Сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                continue; // Переход к следующей итерации цикла
            }

            value3 <<= 4; // Сдвиг влево на 4 бита эквивалентен умножению на 16

            std::cout << "Результат упражнения 3: " << value3 << std::endl;
            break;
        }
        case 4: {
            // Упражнение 4: Разделить значение на 8
            int value4;
            std::cout << "Введите значение переменной: ";
            if (!(std::cin >> value4)) {
                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
                std::cin.clear(); // Сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                continue; // Переход к следующей итерации цикла
            }

            value4 >>= 3; // Сдвиг вправо на 3 бита эквивалентен делению на 8

            std::cout << "Результат упражнения 4: " << value4 << std::endl;
            break;
        }
        case 5: {
            // Упражнение 5: Установить n-ый бит в 1, используя маску (вариант 1)
            int value5;
            std::cout << "Введите значение переменной: ";
            if (!(std::cin >> value5)) {
                std::cout << "Ошибка при вводе. Пожалуйста, введите целое число." << std::endl;
                std::cin.clear(); // Сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                continue; // Переход к следующей итерации цикла
            }

            int n;
            std::cout << "Введите номер бита для установки в 1: ";
            if (!(std::cin >> n) || n < 0 || n > 31) {
                std::cout << "Ошибка при вводе номера бита. Пожалуйста, введите корректное значение." << std::endl;
                std::cin.clear(); // Сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                continue; // Переход к следующей итерации цикла
            }

            // Маска для установки n-го бита в 1
            int mask5 = 1 << n;

            value5 |= mask5;

            std::cout << "Результат упражнения 5: " << value5 << std::endl;
            break;
        }
        }
    }

    return 0;
}
