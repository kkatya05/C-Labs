#include <iostream>
#include <string> 
#include <cmath>
using namespace std;
//g++ main.cpp -o build/main.exe -fexec-charset=GBK -g or ctrl shift B
//.\build\main.exe

int calc() {
        string operation;
        double num1, num2;

        cout << "Enter first number:";
        cin >> num1;
        cout << "Enter operation:";
        cin >> operation;
        cout << "Enter second number:";
        cin >> num2;

        if (operation == "plus"){
            cout << num1 + num2;
        } 
        else if(operation == "minus"){
            cout << num1 - num2;
        } 
        else if(operation == "power"){
            double result = 1.0;  
            int exp = static_cast<int>(num2);
            for (int i = 0; i < exp; ++i) {
                result *= num1;
            }

            cout << result;
        }
        else {
            cout << "Not a recognize operation";
        }

    return 0;
    }

int main() {  
calc();
return 0;
}