#include <iostream>
#include <fstream>
#include <algorithm>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

const int SIZE = 500000;

int main() {
    std::fstream file("array.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла :(" << std::endl;
        return 1;
    }

    int array[SIZE];
    int index = 0;

    while (index < SIZE && file >> array[index]) {
        index++;
    }
    file.close();

    quickSort(array, 0, index - 1);

    std::ofstream out("arraySorted.txt");
    for (int i = 0; i < index; i++) {
        out << array[i] << '\n';
    }
    out.close();

    return 0;
}
