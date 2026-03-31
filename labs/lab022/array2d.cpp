#include <iostream>

int main() {
    int rows , cols;
    std::cin >> rows >> cols;
    int arr[rows][cols];

    int rowSum[rows];
    int colSum[cols];
    for (int i = 0; i < rows; i++) { rowSum[i] = 0; }
    for (int j = 0; j < cols; j++) { colSum[j] = 0; }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            std::cin >> arr[i][j];
            rowSum[i] += arr[i][j];
            colSum[j] += arr[i][j];
        }
    }

    for(int i = 0; i < rows; i++) {
        std::cout << rowSum[i] << " ";
    }

    std::cout << std::endl;

    for(int j = 0; j < cols; j++) {
        std::cout << colSum[j] << " ";
    }
    std::cout << std::endl;

    return 0;
}
