#include <iostream>
#include <vector>

// Сортировка баллов от 0 до 100 подсчетом
void countingSort(std::vector<int>& arr)
{
    int count[101] = {0};

    for (int i = 0; i < (int)arr.size(); i++)
    {
        count[arr[i]]++;
    }

    int index = 0;
    for (int value = 0; value <= 100; value++)
    {
        for (int j = 0; j < count[value]; j++)
        {
            arr[index] = value;
            index++;
        }
    }
}

int main()
{
    int n;
    std::cout << "Enter number of scores (1-100000): ";
    if (!(std::cin >> n) || n < 1 || n > 100000)
    {
        std::cout << "Invalid size" << std::endl;
        return 1;
    }

    std::vector<int> arr(n);
    std::cout << "Enter scores (0-100): ";
    for (int i = 0; i < n; i++)
    {
        if (!(std::cin >> arr[i]) || arr[i] < 0 || arr[i] > 100)
        {
            std::cout << "Invalid score" << std::endl;
            return 1;
        }
    }

    countingSort(arr);

    std::cout << "Sorted scores: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

// g++ task1.cpp -o task1.exe
// .\task1.exe
