#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> data;
    data.reserve(n);

    int size;
    for(int i = 0; i < n; i++) {
        std::cin >> size;
        std::vector<int> row(size);
        for(int j = 0; j < size; j++) {
            std::cin >> row[j];
        }
        data.push_back(row);
    }

    for(int k = 0; k < m; k++) {
        int i , j;
        std::cin >> i >> j;
        std::cout << data[i][j] << std::endl;
    }

    // TODO: n개의 가변 길이 정수 배열을 입력받아 data에 저장하세요.

    // TODO: m개의 질문 (i, j)을 입력받아 data[i][j]를 한 줄에 하나씩 출력하세요.

    return 0;
}
