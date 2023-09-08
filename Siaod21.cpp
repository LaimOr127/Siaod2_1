#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <cctype> // Для isdigit функции

const int MAX_DIGIT = 7; // Максимальная цифра в семизначных числах
const int NUM_DIGITS = 10; // Количество возможных цифр (0-9)

// Функция для установки битов в битовом массиве на основе числа
void setBits(std::vector<bool>& bitArray, int num) {
    while (num > 0) {
        int digit = num % 10; // Получаем последнюю цифру числа
        bitArray[digit] = true; // Устанавливаем соответствующий бит в true
        num /= 10; // Убираем последнюю цифру числа
    }
}

// Функция для сортировки семизначных чисел на основе битового массива
void sortNumbers(std::vector<int>& numbers, const std::vector<bool>& bitArray) {
    std::vector<int> sortedNumbers;
    for (int num : numbers) {
        bool canInsert = true;
        int copy = num;
        while (copy > 0) {
            int digit = copy % 10; // Получаем последнюю цифру числа
            if (!bitArray[digit]) {
                canInsert = false; // Если бит не установлен, число нельзя вставить
                break;
            }
            copy /= 10; // Убираем последнюю цифру числа
        }
        if (canInsert) {
            sortedNumbers.push_back(num);
        }
    }
    numbers = sortedNumbers;
}

int main() {
    std::vector<bool> bitArray(NUM_DIGITS, false); // Битовый массив для цифр 0-9
    std::vector<int> numbers; // Список семизначных чисел

    while (true) {
        // Ввод семизначных чисел с клавиатуры
        int num;
        std::cout << "Введите семизначные числа (для завершения введите 0):\n";
        while (true) {
            std::string input;
            std::cin >> input;

            if (input == "0") {
                break;
            }

            bool validInput = true;

            for (char digit : input) {
                if (!std::isdigit(digit)) {
                    std::cout << "Введите корректное семизначное число.\n";
                    validInput = false;
                    break;
                }
            }

            if (validInput) {
                num = std::stoi(input);

                if (num >= 1000000 && num <= 9999999) {
                    setBits(bitArray, num); // Устанавливаем биты для введенного числа
                    numbers.push_back(num); // Добавляем число в список
                }
                else {
                    std::cout << "Введите корректное семизначное число.\n";
                }
            }
            else {
                std::cout << "Введите корректное семизначное число.\n";
            }
        }

        // Сортировка семизначных чисел
        sortNumbers(numbers, bitArray);

        // Вывод отсортированных чисел
        std::cout << "Отсортированные семизначные числа:\n";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        // Очистка битового массива и списка чисел для новой итерации
        bitArray.assign(NUM_DIGITS, false);
        numbers.clear();

        // Проверка, хочет ли пользователь продолжить
        char choice;
        std::cout << "Хотите ввести еще числа? (y/n): ";
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }

        // Очистка буфера ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
