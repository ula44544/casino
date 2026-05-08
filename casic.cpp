// Подключаем библиотеку для вывода текста в консоль
#include <iostream>

// Подключаем vector — удобный массив
#include <vector>

// Подключаем string — работа со строками
#include <string>

// Для rand() и srand()
#include <cstdlib>

// Для time()
#include <ctime>

// Для задержки времени
#include <thread>
#include <chrono>

// Если программа запускается на Windows
#ifdef _WIN32

// Библиотека Windows
#include <windows.h>

// Для русского языка
#include <locale.h>

#endif

// Используем стандартные функции без std::
using namespace std;

// Цвета текста в консоли через ANSI коды
const string RESET = "\033[0m";   // Сброс цвета
const string RED = "\033[31m";  // Красный
const string GREEN = "\033[32m";  // Зеленый
const string YELLOW = "\033[33m";  // Желтый
const string BLUE = "\033[34m";  // Синий
const string MAGENTA = "\033[35m";  // Фиолетовый
const string CYAN = "\033[36m";  // Голубой

// Создаем структуру символа слота
struct Symbol {

    // Символ
    string icon;

    // Цвет символа
    string color;
};

// Функция очистки консоли
void clearConsole() {

#ifdef _WIN32

    // Очистка Windows консоли
    system("cls");

#else

    // Очистка Linux/Mac консоли
    system("clear");

#endif
}

// Главная функция программы
int main() {

#ifdef _WIN32

    // Включаем UTF-8 для русского текста
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Русская локаль
    setlocale(LC_ALL, "Russian");

    // Получаем консоль Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Переменная для режима консоли
    DWORD dwMode = 0;

    // Получаем текущий режим
    GetConsoleMode(hOut, &dwMode);

    // Включаем поддержку ANSI цветов
    SetConsoleMode(
        hOut,
        dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING
    );

#endif

    // Инициализация случайных чисел
    srand((unsigned)time(0));

    // Создаем список символов слота
    vector<Symbol> symbols = {

        {"7", RED},

        {"$", GREEN},

        {"@", YELLOW},

        {"#", BLUE},

        {"*", MAGENTA},

        {"&", CYAN}
    };

    // Начальный баланс игрока
    int balance = 1000;

    // Бесконечный игровой цикл
    while (true) {

        // Очищаем консоль
        clearConsole();

        // Проверяем — закончились ли деньги
        if (balance <= 0) {

            // Красный цвет
            cout << RED;

            // Надпись GAME OVER
            cout << "=============================\n";
            cout << "          GAME OVER\n";
            cout << "=============================\n\n";

            // Сообщение игроку
            cout << "У вас закончились поинты!\n";

            // Возвращаем обычный цвет
            cout << RESET;

            // Выходим из цикла
            break;
        }

        // Заголовок игры
        cout << "=============================\n";
        cout << "         SLOT MACHINE\n";
        cout << "=============================\n\n";

        // Показываем баланс
        cout << "Баланс: ";

        // Зеленый цвет
        cout << GREEN;

        // Сам баланс
        cout << balance;

        // Возврат обычного цвета
        cout << RESET;

        cout << " поинтов\n\n";

        // Переменная ставки
        int bet;

        // Просим ввести ставку
        cout << "Введите ставку: ";

        // Читаем число
        cin >> bet;

        // Проверка ошибок ввода
        if (cin.fail()) {

            // Сбрасываем ошибку
            cin.clear();

            // Очищаем мусор из ввода
            cin.ignore(999999, '\n');

            cout << RED;
            cout << "Введите число!\n";
            cout << RESET;

            // Ждем 2 секунды
            this_thread::sleep_for(
                chrono::seconds(2)
            );

            // Начинаем цикл заново
            continue;
        }

        // Проверка ставки
        if (bet <= 0) {

            cout << RED;
            cout << "Ставка должна быть больше 0!\n";
            cout << RESET;

            this_thread::sleep_for(
                chrono::seconds(2)
            );

            continue;
        }

        // Проверка хватает ли денег
        if (bet > balance) {

            cout << RED;
            cout << "Недостаточно поинтов!\n";
            cout << RESET;

            this_thread::sleep_for(
                chrono::seconds(2)
            );

            continue;
        }

        // Вычитаем ставку из баланса
        balance -= bet;

        // Создаем массив из 3 слотов
        vector<int> slots(3);

        // Анимация прокрутки
        for (int spin = 0; spin < 20; spin++) {

            // Очищаем консоль
            clearConsole();

            // Заголовок
            cout << "=============================\n";
            cout << "         SLOT MACHINE\n";
            cout << "=============================\n\n";

            // Показываем баланс
            cout << "Баланс: "
                << GREEN
                << balance
                << RESET
                << " поинтов\n\n";

            // Рисуем 3 случайных символа
            for (int i = 0; i < 3; i++) {

                // Случайный индекс
                int r = rand() % symbols.size();

                // Вывод слота
                cout << "[ "
                    << symbols[r].color
                    << symbols[r].icon
                    << RESET
                    << " ] ";
            }

            cout << "\n\nКрутится...\n";

            // Пауза 100 миллисекунд
            this_thread::sleep_for(
                chrono::milliseconds(100)
            );
        }

        // Генерируем финальные символы
        for (int i = 0; i < 3; i++) {

            // Случайный символ
            slots[i] = rand() % symbols.size();
        }

        // Очищаем экран
        clearConsole();

        // Заголовок
        cout << "=============================\n";
        cout << "         SLOT MACHINE\n";
        cout << "=============================\n\n";

        // Показываем ставку
        cout << "Ставка: "
            << YELLOW
            << bet
            << RESET
            << "\n\n";

        // Выводим итоговые слоты
        for (int i = 0; i < 3; i++) {

            cout << "[ "
                << symbols[slots[i]].color
                << symbols[slots[i]].icon
                << RESET
                << " ] ";
        }

        cout << "\n\n";

        // Если все 3 одинаковые
        if (
            slots[0] == slots[1] &&
            slots[1] == slots[2]
            ) {

            // Выигрыш x5
            int win = bet * 5;

            // Добавляем деньги
            balance += win;

            cout << GREEN;
            cout << "ДЖЕКПОТ x5\n";

            cout << "Вы выиграли "
                << win
                << " поинтов!\n";

            cout << RESET;
        }

        // Если 2 одинаковые
        else if (

            slots[0] == slots[1] ||
            slots[1] == slots[2] ||
            slots[0] == slots[2]
            ) {

            // Выигрыш x2
            int win = bet * 2;

            // Добавляем баланс
            balance += win;

            cout << YELLOW;
            cout << "ПОБЕДА x2\n";

            cout << "Вы выиграли "
                << win
                << " поинтов!\n";

            cout << RESET;
        }

        // Если ничего не совпало
        else {

            cout << RED;
            cout << "ПРОИГРЫШ\n";

            cout << "Вы потеряли "
                << bet
                << " поинтов\n";

            cout << RESET;
        }

        // Показываем баланс
        cout << "\nТекущий баланс: "
            << GREEN
            << balance
            << RESET
            << " поинтов\n";

        // Ждем ENTER
        cout << "\nНажмите ENTER для продолжения...";

        // Очищаем enter
        cin.ignore();

        // Ждем enter
        cin.get();
    }

    // Конец программы
    return 0;
}