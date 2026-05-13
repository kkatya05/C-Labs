#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

// Компиляция: g++ main.cpp -o build/main.exe or ctrl shift b
// Запуск: .\build\main.exe 5 plus 3
//         .\build\main.exe 10 minus 4
//         .\build\main.exe 2 power 5

int main(int argc, char* argv[]) {
    // Проверка количества аргументов
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <num1> <operation> <num2>" << endl;
        cout << "Operations: plus, minus, power" << endl;
        cout << "Example: " << argv[0] << " 5 plus 3" << endl;
        return 1;
    }
    
    // Парсинг аргументов командной строки
    double num1 = atof(argv[1]); // atof : string -> double
    string operation = argv[2];
    double num2 = atof(argv[3]);
    
    // Выполнение операции
    if (operation == "plus") {
        cout << num1 + num2 << endl;
    } 
    else if (operation == "minus") {
        cout << num1 - num2 << endl;
    } 
    else if (operation == "power") {
        double result = 1.0;
        int exp = static_cast<int>(num2);
        for (int i = 0; i < exp; ++i) {
            result *= num1;
        }
        cout << result << endl;
    }
    else {
        cout << "Not a recognized operation" << endl;
        cout << "Available operations: plus, minus, power" << endl;
        return 1;
    }
    
    return 0;
}