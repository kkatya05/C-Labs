#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
using namespace std;
using namespace std::chrono;
//g++ main.cpp -o build/main.exe -fexec-charset=GBK -g
//.\build\main.exe


double calculate1(double x) {
    double a1;
    a1 = pow(x, 2) - pow(x, 2) + x*4 - x*5 + x + x;
    return a1;
}

double calculate2(double x) {
    double a2;
    a2 = x + x;
    return a2;
}

void taskFormula1(double x, int iterations, double& result) {
    for (int i = 0; i < iterations; i++) {
        result = calculate1(x);
    }
}

void taskFormula2(double x, int iterations, double& result) {
    for (int i = 0; i < iterations; i++) {
        result = calculate2(x);
    }
}

int main() {
    int p;
    double x = 1.5;
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

        // === ПАРАЛЛЕЛЬНОЕ выполнение формул 1 и 2 ===
        auto startParallel = high_resolution_clock::now();

        thread t1(taskFormula1, x, p, ref(result1));
        thread t2(taskFormula2, x, p, ref(result2));

        t1.join();
        t2.join();

        auto endParallel = high_resolution_clock::now();
        auto durationParallel = duration_cast<microseconds>(endParallel - startParallel);

        // === ПОСЛЕДОВАТЕЛЬНОЕ выполнение формулы 3 ===
        auto start3 = high_resolution_clock::now();

        for (int i = 0; i < p; i++) {
            a3 = result1 + result2 - result1;
        }

        auto end3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(end3 - start3);

        // Вывод результатов
        cout << "\n--- Results for " << p << " iterations ---" << endl;
        cout << "Time for formulas 1 & 2 (parallel): " << durationParallel.count() / 1000000.0 << " seconds" << endl;
        cout << "Time for formula 3 (sequential): " << duration3.count() / 1000000.0 << " seconds" << endl;
        cout << "Total time: " << (durationParallel.count() + duration3.count()) / 1000000.0 << " seconds" << endl;
        cout << "Result a3 = " << a3 << endl << endl;
    }

    return 0;
}