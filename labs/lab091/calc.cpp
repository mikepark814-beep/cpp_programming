#include "calc.h"

void transform(int* a, int* b) {
    if (a == nullptr || b == nullptr) {
        return;
    }
    
    int orig_a = *a;
    int orig_b = *b;
    *a = orig_a * 2 + orig_b;
    *b = orig_b * 2 - orig_a;

}