#include <iostream>
#include <bitset>

using namespace std;

// Функция для установки заданных битов в 1
int SetBitsToOnes(int x, int mask) {
    return x | mask; // Поразрядное ИЛИ, чтобы установить биты в 1
}

// Функция для обнуления заданных битов
int ClearBitsToZeros(int x, int mask) {
    return x & ~mask; // Поразрядное И и инверсия маски
}

// Функция для умножения числа на 16
int MultiplyBy16(int x) {
    return x << 4; // Сдвиг на 4 бита влево эквивалентен умножению на 16
}

// Функция для целочисленного деления числа на 8
int DivideBy8(int x) {
    return x >> 3; // Сдвиг на 3 бита вправо эквивалентен делению на 8
}

// Функция для установки n-го бита в 1, используя маску
int SetNthBitToOne(int x, int n) {
    int mask = 1 << n; // Создаем маску с 1 в заданной позиции
    return x | mask; // Поразрядное ИЛИ с маской для установки n-го бита в 1
}

int main() {
    setlocale(LC_ALL, "Russian"); // Установка русской локали

    int operation, x, mask, result;
    bool flag = true;

    while (flag) {
        cout << "\n\n-------------------------\n";
        cout << "1. Установить биты в 1, используя маску" << endl;
        cout << "2. Обнулить биты с маской" << endl;
        cout << "3. Умножить на 16" << endl;
        cout << "4. Поделить на 8" << endl;
        cout << "5. Установить n-ый бит в 1, используя маску" << endl;
        cout << "6. Выйти из программы" << endl;
        cout << "\t\tВведите номер операции: ";
        cin >> operation;
        cout << "\n-------------------------\n";

        switch (operation) {
        case 1:
            cout << "Введите исходное число (x): ";
            cin >> x;
            mask = 0x124; // Маска для установки 3-го, 5-го и 8-го битов в 1
            cout << "Число x в 16-ой СС: " << hex << x << endl;
            cout << "Маска в 16-ой СС: " << hex << mask << endl;
            cout << "x (2-ая СС): " << bitset<32>(x);
            cout << "\nm (2-ая СС): " << bitset<32>(mask);
            result = SetBitsToOnes(x, mask);
            cout << "\nr (2-ая СС): " << bitset<32>(result);

            cout << "\n\nРезультат в 16-ой СС: " << hex << result << endl;
            break;
        case 2:
            cout << "Введите число, которое необходимо преобразовать: ";
            cin >> x;
            mask = 0xF0; // Маска для обнуления с 4-го по 7-й биты
            cout << "Число x в 16-ой СС: " << hex << x << endl;
            cout << "x (2-ая СС): " << bitset<32>(x);
            cout << "\nm (2-ая СС): " << bitset<32>(~mask);
            result = ClearBitsToZeros(x, mask);
            cout << "\nr (2-ая СС): " << bitset<32>(result);
            cout << "\n\nРезультат в 16-ой СС: " << hex << result << endl;
            break;
        case 3:
            cout << "Введите число, которое необходимо преобразовать: ";
            cin >> x;
            cout << "Число x в 16-ой СС: " << hex << x << endl;
            cout << "x (2-ая СС): " << bitset<32>(x);
            result = MultiplyBy16(x);
            cout << "\nr (2-ая СС): " << bitset<32>(result);
            cout << "\n\nРезультат в 16-ой СС: " << hex << result << endl;
            break;
        case 4:
            cout << "Введите число, которое необходимо преобразовать: ";
            cin >> x;
            cout << "Число x в 16-ой СС: " << hex << x << endl;
            cout << "x (2-ая СС): " << bitset<32>(x);
            result = DivideBy8(x);
            cout << "\nr (2-ая СС): " << bitset<32>(result);
            cout << "\n\nРезультат в 16-ой СС: " << hex << result << endl;
            break;
        case 5:
            int bitToSet;
            cout << "Введите номер бита, который необходимо установить в 1: ";
            cin >> bitToSet;
            cout << "\nВведите число, в котором нужно установить бит: ";
            cin >> x;
            mask = 1 << bitToSet; // Создаем маску с 1 в заданной позиции
            cout << "Число x в 16-ой СС: " << hex << x << endl;
            cout << "x (2-ая СС): " << bitset<32>(x);
            cout << "\nm (2-ая СС): " << bitset<32>(mask);
            result = SetNthBitToOne(x, bitToSet);
            cout << "\nr (2-ая СС): " << bitset<32>(result);
            cout << "\n\nРезультат в 16-ой СС: " << hex << result << endl;
            break;
        case 6:
            cout << "\nВыход из программы.";
            flag = false;
            break;
        default:
            cout << "\nОшибка: Введите корректный номер операции (от 1 до 6)." << endl;
            break;
        }
    }

    return 0;
}
