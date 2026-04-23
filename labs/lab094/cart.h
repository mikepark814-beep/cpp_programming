#ifndef CART_H
#define CART_H

#include <string>

// 장바구니 관리 — 내부 상태는 cart.cpp 의 static 변수로 보관합니다.
// 함수 파라미터로 상태를 전달하지 않습니다.

void add_item(const std::string& name, int price);
bool has_item(const std::string& name);
void remove_item(const std::string& name);  // 없으면 아무것도 하지 않음
int total_price();                          // 현재 장바구니 총액

#endif // CART_H
