#include <iostream>
#include <string>
using namespace std;


class Node {
public:
    string move;
    Node* prev; // POINTER: Указатель на предыдущий узел 
    Node* next; // POINTER: Указатель на следующий узел

    // Конструктор: при создании узла указатели сразу инициализируются nullptr
    Node(string m) : move(m), prev(nullptr), next(nullptr) {}
};

Node* head = nullptr;
Node* tail = nullptr;
int moveCount = 0;

void addMove(string move) {
    Node* ptr = new Node(move); 
    ptr->prev = tail;
    ptr->next = nullptr;
    if (tail != nullptr) {
        tail->next = ptr;
    } else {
        head = ptr;
    }
    tail = ptr;
    moveCount++;
}

void printList() {
    Node* current = head;
    int step = 1;

    // POINTER: Цикл продолжается, пока current не станет nullptr (конец списка)
    while (current != nullptr) {
        // POINTER: Оператор -> разыменовывает указатель current и обращается к полю move
        cout << "Step " << step++ << ": " << current->move << endl;
        // POINTER: Сдвигаем указатель current по цепочке: присваиваем ему адрес следующего узла
        current = current->next;
    }
    cout << "Total moves: " << moveCount << endl;
}

void freeList() {
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    moveCount = 0;
}

void towerofhanoi(int n, int a, int b, int c) {
    if (n == 0) {
        return;
    }
    towerofhanoi(n - 1, a, c, b);
    addMove("Move disk from " + to_string(a) + " to " + to_string(c));
    towerofhanoi(n - 1, b, a, c);
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    towerofhanoi(n, 1, 2, 3);

    cout << "=== Moves List ===" << endl;
    printList();

    freeList(); // Освобождаем всю динамическую память перед выходом

    return 0;
}