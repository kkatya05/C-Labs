#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;
//g++ main.cpp -o build/main.exe -fexec-charset=GBK -g
//.\build\main.exe

double calculate1(double x) {
    double a1;
    a1 = pow(x, 2) - pow(x, 2) + x*4 - x*5 + x + x;
    return a1;
}

double calculate2(double x){
    double a2;
    a2 = x + x;
    return a2;

}

int main() {
    int p;
    double x = 1.5;  // значение x для вычислений
    double a3; 
    double result1 = 0;  
    double result2 = 0;

    while (true) {
        cout << "Enter number of iterations: ";
        cin >> p;
        if (cin.fail()) {
            cout << "Error: not a number! Program terminated." << endl;
            break;
        }

        // подсчет по формуле 1
        auto start1 = high_resolution_clock::now();
 
        for (int i = 0; i < p; i++) {
            result1 = calculate1(x);
        }
        
        auto end1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(end1 - start1);
        
        // подсчет по формуле 2
        auto start2 = high_resolution_clock::now();
 
        for (int i = 0; i < p; i++) {
            result2 = calculate2(x);
        }
        
        auto end2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(end2 - start2);
        
        // подсчет по формуле 3
        auto start3 = high_resolution_clock::now();  
        for (int i = 0; i < p; i++) {
            a3 = result1 + result2 - result1; 
        }
        
        auto end3 = high_resolution_clock::now();  
        auto duration3 = duration_cast<microseconds>(end3 - start3);  

        // (микрогоды → секунды)
        cout << "Time for formula 1 for " << p << " iterations: " << duration1.count() / 1000000.0 << " seconds" << endl;
        cout << "Time for formula 2 for " << p << " iterations: " << duration2.count() / 1000000.0 << " seconds" << endl;
        cout << "Time for formula 3 for " << p << " iterations: " << duration3.count() / 1000000.0 << " seconds" << endl;  // ИСПРАВЛЕНО: добавили вывод для формулы 3
        cout << "Result a3 = " << a3 << endl;  
    }
    
    
    return 0;
}