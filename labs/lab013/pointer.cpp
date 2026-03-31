#include "pointer.h"

void update(int* a, int* b) {
    if (a == nullptr || b == nullptr) {
        return;
    }

    int x = *a;   
    int y = *b;   

    *a = x + y;   
    *b = x - y;   
}