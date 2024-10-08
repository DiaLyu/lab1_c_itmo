#include <iostream>
#include "string"
#include <fstream>

#ifndef NOMINMAX
# define NOMINMAX
#endif

#include <Windows.h>
#include <vector>
#include <limits>
#include "math_function.h"

using namespace std;

// 1. Число
// 2. Операция
// 3. Скобка
int lastChoice = -1;        // номер предыдущей команды для отслеживания ввода данных
string lastOperator = "";

// функция для выбора меню
void choiceTypes(string& type1, string& type2) {
    vector<string> type_list{ "short", "unsigned short", "int", "unsigned int", "long", "unsigned long", "long long", "unsigned long long", "float", "double", "long double" };
    cout << "Введите типы данных (числовые) для вашего примера: \n";

    do {
        if (type1 == "") {
            cout << "Тип данных для входных чисел > "; getline(cin, type1);
            auto it = find(type_list.begin(), type_list.end(), type1); // Эта функция возвращает итератор на первое найденное значение или words.end(), если значение не найдено
            if (it == type_list.end()) {
                std::cout << "Слово \"" << type1 << "\" не найдено в векторе." << std::endl;
                type1 = "";
                continue;
            }
        }
        if (type2 == "") {
            cout << "Тип данных для результата > "; getline(cin, type2);
            auto it = find(type_list.begin(), type_list.end(), type2); // Эта функция возвращает итератор на первое найденное значение или words.end(), если значение не найдено
            if (it == type_list.end()) {
                std::cout << "Слово \"" << type2 << "\" не найдено в векторе." << std::endl;
                type2 = "";
                continue;
            }
        }
    } while (type1 == "" || type2 == "");
}

// проверка на корректный ввод чисел
template <typename T>
void numericalInputValidation(T& choice, string instruction = "> ") {
    cout << instruction;
    while (!(cin >> choice)) {
        cout << "\nНекорректный ввод. Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ввод пользователем числа с проверкой на тип данных
void inputNumber(string& math_expression, string type1) {
    if (type1 == "short") {
        short number;
        numericalInputValidation<short>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "unsigned short") {
        unsigned short number;
        numericalInputValidation<unsigned short>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "int") {
        int number;
        numericalInputValidation<int>(number, "Введите число > ");
        math_expression += to_string(number);
    } 
    else if (type1 == "unsigned int") {
        unsigned int number;
        numericalInputValidation<unsigned int>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "long") {
        long number;
        numericalInputValidation<long>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "unsigned long") {
        unsigned long number;
        numericalInputValidation<unsigned long>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "long long") {
        long long number;
        numericalInputValidation<long long>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "unsigned long long") {
        unsigned long long number;
        numericalInputValidation<unsigned long long>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "float") {
        float number;
        numericalInputValidation<float>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "double") {
        double number;
        numericalInputValidation<double>(number, "Введите число > ");
        math_expression += to_string(number);
    }
    else if (type1 == "long double") {
        long double number;
        numericalInputValidation<long double>(number, "Введите число > ");
        math_expression += to_string(number);
    }
}

// выбор оператора в выражение
void choiceOperation(string& math_expression, string type1) {
    /* чтение опараторов из файла */
    string line;
    vector<string> math_symbols{};
    ifstream fin("operations.txt");
    if (fin.is_open())
    {
        while (getline(fin, line))
        {
            cout << line << endl;
            math_symbols.push_back(line.substr(0, line.find("\t")));
        }
    }
    fin.close();

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера

    string operat;
    cout << "Выберите оператор из перечисленных > "; getline(cin, operat);
    auto it = find(math_symbols.begin(), math_symbols.end(), operat); // Эта функция возвращает итератор на первое найденное значение или words.end(), если значение не найдено
    if (it == math_symbols.end()) {
        cout << "Оператор \"" << operat << "\" не найден в векторе." << endl;
        operat = "";
    }
    else {
        if (operat == "+" || operat == "-" || operat == "/" || operat == "*") {
            if ((lastChoice == 2 && (lastOperator == "+" || lastOperator == "-" || lastOperator == "/" || lastOperator == "*")) || lastChoice == 3) {
                cout << "Операции идут друг за другом. Отмена... \n" << endl;
            }
            else {
                math_expression += operat;
            }
        } 
        else {
            math_expression += operat;
            if (operat == "sqrt" || operat == "log") { // Функция pow(arg1, arg2) в C++ вычисляет значение arg1, возведённое в степень arg2
                math_expression += "(";
                inputNumber(math_expression, type1);
                math_expression += ")";
            }
            else if (operat == "pow") {
                math_expression += "(";
                inputNumber(math_expression, type1);
                math_expression += ", ";
                double degree;
                numericalInputValidation<double>(degree, "Введите степень > ");
                math_expression += to_string(degree) + ")";
            }
        }
        lastOperator = operat;
    }
}

void inputBrackets(string& math_expression) {
    string operat = "";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
    cout << "\nВведите нужную скобку () > "; getline(cin, operat);
    if (operat == "(" || operat == ")") {
        math_expression += operat;
    }
}

void codeGeneration(string& math_expression, string type1, string type2) {
    ofstream fout("math_function.h");
    fout << "#include <iostream>" << endl;
    fout << "#include <cmath>" << endl;
    fout << type2 << " add_f();" << endl;
    fout << type2 << " add_f() {" << endl;
    fout << "std::cout << \"" << math_expression << " = \" << " + math_expression + " << std::endl;" << endl;
    fout << "return 0;" << endl;
    fout << "}" << endl;
    fout.close();

    math_expression = "";
    cout << "Выражение занесено в функцию f() файла math_function\n" << endl;
}

// пользовательский интерфейс (консоль)
void menuFunction(string type1, string type2) {
    int choice = -1;            // номер команды
    
    string math_expression = "";

    do {
        cout << "\nСоставление математического выражения\n";
        cout << "1. Ввод числа\n";
        cout << "2. Выбор математической операции\n";
        cout << "3. Скобки\n";
        cout << "4. Закончить составление выражения\n";
        cout << "0. Выход из программы\n";
        numericalInputValidation<int>(choice, "Выберите номер команды > ");

        switch (choice) {
            case 1:
                inputNumber(math_expression, type1);
                break;
            case 2:
                choiceOperation(math_expression, type1);
                break;
            case 3:
                inputBrackets(math_expression);
                break;
            case 4:
                codeGeneration(math_expression, type1, type2);
                break;
            case 0:
                cout << "Завершение программы\n";
                break;
            default:
                cout << "Неправильная команда! Попробуйте снова\n";
                break;
        }
        cout << "Текущее математическое выражение: " << math_expression << endl;
        lastChoice = choice;
    } while (choice != 0);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string type1 = "", type2 = "";
    choiceTypes(type1, type2);
    cout << type1 << " " << type2 << endl;

    cout << "Выберите номер необходимой команды:\n";
    cout << "1. Составлять выражение \n";
    cout << "2. Посмотреть результат выражения, составленной при прошлой компиляции программы \n";

    int choice;
    numericalInputValidation<int>(choice, "Выберите номер команды > ");

    switch (choice) {
        case 1: 
            menuFunction(type1, type2);
            break;
        case 2:
            add_f();
            break;
        default:
            cout << "Неправильная команда! Завершение программы\n";
            break;
    }

    return 0;
}