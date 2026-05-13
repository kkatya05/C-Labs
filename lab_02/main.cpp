#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;
//g++ main.cpp -o build/main.exe -fexec-charset=GBK -g
//.\build\main.exe

double calculate(double x) {
    return pow(x, 2) - pow(x, 2) + pow(x, 4) - pow(x, 5) + x;
}

int main() {
    int p;
    double x = 1.5;  // значение x для вычислений
    
    while (true) {
        cout << "Enter number of iterations: ";
        cin >> p;
        if (cin.fail()) {
            cout << "Error: not a number! Program terminated." << endl;
            break;
        }

        auto start = high_resolution_clock::now();
 
        for (int i = 0; i < p; i++) {
            double result = calculate(x);
        }
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        
        cout << "Time  " << p << " iterations: " << duration.count() << " microseconds" << endl;
        cout << "----------------------------------------" << endl;
    }
    
    return 0;
}