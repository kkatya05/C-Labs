#include <iostream>
#include <vector>

// Сортировка небольшого списка чисел вставками
void insertionSort(std::vector<int>& arr)
{
    for (int i = 1; i < (int)arr.size(); i++)
    {
        int value = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > value)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = value;
    }
}

int main()
{
    int n;
    std::cout << "Enter number of values (1-1000): ";
    if (!(std::cin >> n) || n < 1 || n > 1000)
    {
        std::cout << "Invalid size" << std::endl;
        return 1;
    }

    std::vector<int> arr(n);
    std::cout << "Enter integer values: ";
    for (int i = 0; i < n; i++)
    {
        if (!(std::cin >> arr[i]))
        {
            std::cout << "Invalid value" << std::endl;
            return 1;
        }
    }

    insertionSort(arr);

    std::cout << "Sorted values: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

// g++ task2.cpp -o task2.exe
// .\task2.exe
