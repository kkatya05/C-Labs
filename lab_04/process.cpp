#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
using namespace std;
using namespace std::chrono;

//g++ main.cpp -o build/main.exe -fexec-charset=GBK -g
//.\build\main.exe

double calculate1(double x) {
    return pow(x, 2) - pow(x, 2) + x*4 - x*5 + x + x;
}

double calculate2(double x) {
    return x + x;
}

// Функция для записи результата в файл
void writeResultToFile(const string& filename, double result) {
    ofstream file(filename);
    file << result;
    file.close();
}

// Чтение результата из файла
double readResultFromFile(const string& filename) {
    ifstream file(filename);
    double result;
    file >> result;
    file.close();
    return result;
}

int main(int argc, char* argv[]) {
    // Если запущен как дочерний процесс
    if (argc > 3) {
        string mode = argv[1];
        double x = atof(argv[2]);
        int p = atof(argv[3]);
        string outputFile = argv[4];
        
        double result = 0;
        
        if (mode == "f1") {
            auto start = high_resolution_clock::now();
            for (int i = 0; i < p; i++) {
                result = calculate1(x);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            writeResultToFile(outputFile, result);
            cout << "Formula 1 completed in " << duration.count() / 1000000.0 << " seconds" << endl;
        }
        else if (mode == "f2") {
            auto start = high_resolution_clock::now();
            for (int i = 0; i < p; i++) {
                result = calculate2(x);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            writeResultToFile(outputFile, result);
            cout << "Formula 2 completed in " << duration.count() / 1000000.0 << " seconds" << endl;
        }
        
        return 0;
    }
    
    // Родительский процесс
    int p;
    double x = 1.5;
    double a3;
    double result1, result2;

    while (true) {
        cout << "Enter number of iterations: ";
        cin >> p;
        if (cin.fail()) {
            cout << "Error: not a number! Program terminated." << endl;
            break;
        }

        // Файлы для обмена данными между процессами
        string file1 = "result1.txt";
        string file2 = "result2.txt";
        
        // Удаляем старые файлы если существуют
        remove(file1.c_str());
        remove(file2.c_str());

        cout << "\n=== Starting parallel processes for " << p << " iterations ===" << endl;
        
        auto start_total = high_resolution_clock::now();
        
        // === ЗАПУСК ПРОЦЕССА ДЛЯ ФОРМУЛЫ 1 ===
        STARTUPINFO si1 = {sizeof(STARTUPINFO)};
        PROCESS_INFORMATION pi1;
        
        stringstream ss1;
        ss1 << "build\\main.exe f1 " << x << " " << p << " " << file1;
        string cmd1 = ss1.str();
        
        auto start1 = high_resolution_clock::now();
        CreateProcess(
            NULL,
            (LPSTR)cmd1.c_str(),
            NULL, NULL, FALSE,
            0, NULL, NULL,
            &si1, &pi1
        );
        
        // === ЗАПУСК ПРОЦЕССА ДЛЯ ФОРМУЛЫ 2 ===
        STARTUPINFO si2 = {sizeof(STARTUPINFO)};
        PROCESS_INFORMATION pi2;
        
        stringstream ss2;
        ss2 << "build\\main.exe f2 " << x << " " << p << " " << file2;
        string cmd2 = ss2.str();
        
        auto start2 = high_resolution_clock::now();
        CreateProcess(
            NULL,
            (LPSTR)cmd2.c_str(),
            NULL, NULL, FALSE,
            0, NULL, NULL,
            &si2, &pi2
        );
        
        // Ждем завершения обоих процессов
        WaitForSingleObject(pi1.hProcess, INFINITE);
        WaitForSingleObject(pi2.hProcess, INFINITE);
        
        auto end_parallel = high_resolution_clock::now();
        auto duration_parallel = duration_cast<microseconds>(end_parallel - start1);
        
        // Читаем результаты из файлов
        result1 = readResultFromFile(file1);
        result2 = readResultFromFile(file2);
        
        // === ФОРМУЛА 3 (последовательно в родительском процессе) ===
        auto start3 = high_resolution_clock::now();
        
        for (int i = 0; i < p; i++) {
            a3 = result1 + result2 - result1;
        }
        
        auto end3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(end3 - start3);
        
        // Закрываем дескрипторы процессов
        CloseHandle(pi1.hProcess);
        CloseHandle(pi1.hThread);
        CloseHandle(pi2.hProcess);
        CloseHandle(pi2.hThread);
        
        // Удаляем временные файлы
        remove(file1.c_str());
        remove(file2.c_str());
        
        // Вывод результатов
        cout << "\n=== Results for " << p << " iterations ===" << endl;
        cout << "Time for Formula 1 (process): " << duration_parallel.count() / 1000000.0 << " seconds" << endl;
        cout << "Time for Formula 2 (process): " << duration_parallel.count() / 1000000.0 << " seconds" << endl;
        cout << "Time for Formula 3 (sequential): " << duration3.count() / 1000000.0 << " seconds" << endl;
        cout << "Total parallel time: " << duration_parallel.count() / 1000000.0 << " seconds" << endl;
        cout << "Total time: " << (duration_parallel.count() + duration3.count()) / 1000000.0 << " seconds" << endl;
        cout << "Result1 = " << result1 << endl;
        cout << "Result2 = " << result2 << endl;
        cout << "Result a3 = " << a3 << endl;
        cout << "================================\n" << endl;
    }
    
    return 0;
}