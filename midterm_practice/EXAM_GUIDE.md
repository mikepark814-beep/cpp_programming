# C++ 프로그래밍 실습 중간고사 예상 문제집

> 박세준 / 2026 봄학기
> 분석 기준: `labs/` 폴더 내 lab013~lab063 (lab035x, lab038x, lab045x, c01, q01~q04 제외)
> 출제 형식: 코딩 문제 (구현 파일 `.cpp` 직접 작성)
> 난이도: 쉬움(★) / 중간(★★) / 어려움(★★★) 혼합 10문제

---

## 📚 시험 범위 핵심 주제 요약

| 분류 | 관련 Lab | 핵심 개념 |
|---|---|---|
| 포인터 & 참조자 | lab013, lab018 | `*`, `&`, nullptr 체크, swap |
| 동적 메모리 / 스마트 포인터 | lab014~016 | `new/delete`, `unique_ptr`, `make_unique` |
| 현대 C++ 문법 | lab017 | `std::tuple`, 구조적 바인딩, 람다 |
| 배열 / 벡터 | lab021~023, lab025 | `std::array`, `std::vector`, 2D 배열 |
| 구조체 + 정렬 | lab024, lab036, lab042 | 람다 comparator, bubble sort |
| STL 알고리즘 | lab026, lab027 | `std::sort`, `std::erase`, `std::find_if` |
| 문자열 처리 | lab028, lab039 | `std::string`, `string_view`, `ispunct` |
| std::map | lab029, lab037, lab043, lab044 | `map<K,V>`, structured binding |
| 클래스 기본 (불변, const) | lab051, lab061 | 멤버 초기화 리스트, const 함수 |
| static 멤버 / 함수 | lab041, lab053 | static 변수 정의 위치, 상태 관리 |
| 메서드 체이닝 | lab054 | `*this` 반환, fluent interface |
| initializer_list | lab062 | `std::initializer_list`, value_type |
| 상속 / shared_ptr | lab063 | 클래스 계층, `shared_ptr<const T>` |

---

# 🎯 예상 출제 문제

---

## 문제 1 ★ (쉬움) — 참조자를 이용한 swap 확장

**출제 근거:** lab018 (reference_variable)

### 출제 의도
참조자 매개변수의 이해. 포인터 없이 값을 변경하는 가장 기본적인 방법.

### 주어진 파일: `main.cpp`
```cpp
#include <iostream>

void sort_three(int& a, int& b, int& c);

int main() {
    int x, y, z;
    std::cin >> x >> y >> z;
    sort_three(x, y, z);
    std::cout << x << " " << y << " " << z << std::endl;
    return 0;
}
```

### 학생이 작성할 파일: `sort_three.cpp`
세 정수를 **오름차순**이 되도록 참조자를 통해 재배치하시오. (`std::swap` 사용 허용)

### 입출력 예시
```
입력:  5 2 8
출력:  2 5 8

입력:  9 9 1
출력:  1 9 9
```

### 모범답안
```cpp
#include <algorithm>

void sort_three(int& a, int& b, int& c) {
    if (a > b) std::swap(a, b);
    if (b > c) std::swap(b, c);
    if (a > b) std::swap(a, b);
}
```

### 채점 포인트
- 참조자 문법(`int&`)을 올바르게 받는가
- 값이 실제로 호출부에 반영되는가 (복사본 수정 X)

---

## 문제 2 ★ (쉬움) — 포인터와 nullptr 안전성

**출제 근거:** lab013 (pointer/update)

### 출제 의도
포인터 역참조와 nullptr 가드. 실제 lab13의 update() 패턴을 약간 변형.

### 주어진 파일: `calc.h`
```cpp
#ifndef CALC_H
#define CALC_H

// a, b 중 하나라도 nullptr이면 아무 것도 하지 않고 리턴.
// 그렇지 않으면 *a = *a * 2 + *b, *b = *b * 2 - *a_original 로 설정한다.
// (주의: *a를 먼저 변경하면 *a_original 값을 잃어버리므로 임시 저장 필요)
void transform(int* a, int* b);

#endif
```

### 학생이 작성할 파일: `calc.cpp`

### 입출력 예시
```cpp
int a = 3, b = 5;
transform(&a, &b);  // a = 11, b = 7
// 계산: a_new = 3*2 + 5 = 11
//       b_new = 5*2 - 3 = 7  (원래의 a=3 사용)

int* p = nullptr;
int q = 10;
transform(p, &q);   // 아무 변화 없음, q = 10 유지
```

### 모범답안
```cpp
#include "calc.h"

void transform(int* a, int* b) {
    if (a == nullptr || b == nullptr) return;

    int orig_a = *a;
    int orig_b = *b;
    *a = orig_a * 2 + orig_b;
    *b = orig_b * 2 - orig_a;
}
```

### 채점 포인트
- nullptr 체크 누락 여부
- **원본 값 임시 저장** 누락 시 버그 (흔한 함정)

---

## 문제 3 ★ (쉬움) — std::array와 기본 알고리즘

**출제 근거:** lab023, lab024 (std::array 활용)

### 출제 의도
`std::array` + `std::min_element`/`std::max_element` + 기본 통계

### 주어진 파일: `stats.h`
```cpp
#ifndef STATS_H
#define STATS_H
#include <array>

constexpr size_t N = 5;

// 평균(double), 최댓값-최솟값의 차를 각각 반환
double average(const std::array<int, N>& arr);
int range(const std::array<int, N>& arr);

#endif
```

### 학생이 작성할 파일: `stats.cpp`

### 입출력 예시
```cpp
std::array<int, 5> a = {10, 20, 30, 40, 50};
average(a);  // 30.0
range(a);    // 40  (50 - 10)
```

### 모범답안
```cpp
#include "stats.h"
#include <algorithm>
#include <numeric>

double average(const std::array<int, N>& arr) {
    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    return static_cast<double>(sum) / N;
}

int range(const std::array<int, N>& arr) {
    auto mn = std::min_element(arr.begin(), arr.end());
    auto mx = std::max_element(arr.begin(), arr.end());
    return *mx - *mn;
}
```

### 채점 포인트
- `min_element/max_element`는 **이터레이터를 반환** → 역참조 필요
- int 나눗셈 함정: `sum / N`만 쓰면 정수 나눗셈

---

## 문제 4 ★★ (중간) — 람다 comparator로 구조체 벡터 정렬

**출제 근거:** lab036, lab042

### 출제 의도
lambda를 `std::sort`의 비교 함수로 전달, 다중 정렬 기준

### 주어진 파일: `main.cpp` (일부)
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Runner {
    std::string name;
    int minutes;   // 완주 시간
    int age;
};

void rank_runners(std::vector<Runner>& v);

int main() {
    int n; std::cin >> n;
    std::vector<Runner> v(n);
    for (auto& r : v) std::cin >> r.name >> r.minutes >> r.age;
    rank_runners(v);
    for (const auto& r : v) std::cout << r.name << '\n';
}
```

### 학생이 작성할 파일: `ranker.cpp`
다음 기준으로 정렬:
1. 완주 시간(`minutes`) **오름차순**
2. 시간이 같으면 나이(`age`) **내림차순** (연장자 우대)
3. 둘 다 같으면 이름(`name`) **오름차순**

### 입출력 예시
```
입력:
4
Alice 120 30
Bob 110 25
Carol 120 35
David 110 25

출력:
Bob
David
Carol
Alice
```

### 모범답안
```cpp
#include <vector>
#include <string>
#include <algorithm>

struct Runner {
    std::string name;
    int minutes;
    int age;
};

void rank_runners(std::vector<Runner>& v) {
    std::sort(v.begin(), v.end(),
        [](const Runner& a, const Runner& b) {
            if (a.minutes != b.minutes) return a.minutes < b.minutes;
            if (a.age != b.age)         return a.age > b.age;
            return a.name < b.name;
        }
    );
}
```

### 채점 포인트
- 람다의 매개변수를 **`const T&`**로 받았는가 (복사 비용 감소)
- 다단계 비교 조건 순서 정확성

---

## 문제 5 ★★ (중간) — static 변수로 상태 관리하는 함수들

**출제 근거:** lab041 (playlist), lab053 (Logger)

### 출제 의도
파일 내부 `static` 변수로 전역 상태 관리. 함수 파라미터로 상태를 넘기지 않음.

### 주어진 파일: `cart.h`
```cpp
#ifndef CART_H
#define CART_H
#include <string>

// 장바구니 관리 — 상태는 cart.cpp 내부 static 변수로
void add_item(const std::string& name, int price);
bool has_item(const std::string& name);
void remove_item(const std::string& name);  // 없으면 무시
int total_price();                           // 현재 총액 반환

#endif
```

### 학생이 작성할 파일: `cart.cpp`
내부적으로 `std::vector<std::pair<std::string,int>>`로 관리 (또는 `std::map`도 가능하나 같은 이름 중복 허용 시 vector 추천)

### 입출력 예시 (동작 예시)
```cpp
add_item("apple", 1000);
add_item("milk", 2500);
has_item("milk");     // true
total_price();        // 3500
remove_item("apple");
total_price();        // 2500
```

### 모범답안
```cpp
#include "cart.h"
#include <vector>
#include <algorithm>

static std::vector<std::pair<std::string, int>> cart;

void add_item(const std::string& name, int price) {
    cart.push_back({name, price});
}

bool has_item(const std::string& name) {
    for (const auto& [n, p] : cart) {
        if (n == name) return true;
    }
    return false;
}

void remove_item(const std::string& name) {
    auto it = std::find_if(cart.begin(), cart.end(),
        [&](const auto& p) { return p.first == name; });
    if (it != cart.end()) cart.erase(it);
}

int total_price() {
    int sum = 0;
    for (const auto& [n, p] : cart) sum += p;
    return sum;
}
```

### 채점 포인트
- `static`을 파일 스코프에 선언했는가 (헤더에 넣으면 안 됨)
- `find_if` + 람다, structured binding 활용 여부

---

## 문제 6 ★★ (중간) — std::map과 단어 빈도

**출제 근거:** lab037 (단어 빈도), lab044 (map 순회)

### 출제 의도
`std::map`의 자동 정렬 특성 + structured binding

### 주어진 파일: `main.cpp`
```cpp
#include <iostream>
#include <string>
#include <map>

std::map<std::string, int> count_words(const std::vector<std::string>& words);
void print_top(const std::map<std::string, int>& freq, int k);

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::string> ws(n);
    for (auto& w : ws) std::cin >> w;
    auto freq = count_words(ws);
    print_top(freq, k);
}
```

### 학생이 작성할 파일: `wordfreq.cpp`
- `count_words`: 각 단어의 등장 횟수를 map으로 반환
- `print_top`: **등장 횟수 내림차순, 동률 시 알파벳 오름차순**으로 상위 k개를 `"단어 횟수\n"` 형식 출력

### 입출력 예시
```
입력:
7 3
apple banana apple cherry banana apple banana

출력:
apple 3
banana 3
cherry 1
```
(apple과 banana 모두 3회 → 알파벳순으로 apple 먼저)

### 모범답안
```cpp
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::map<std::string, int> count_words(const std::vector<std::string>& words) {
    std::map<std::string, int> m;
    for (const auto& w : words) m[w]++;
    return m;
}

void print_top(const std::map<std::string, int>& freq, int k) {
    std::vector<std::pair<std::string, int>> v(freq.begin(), freq.end());
    std::sort(v.begin(), v.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    int limit = std::min(k, (int)v.size());
    for (int i = 0; i < limit; ++i) {
        std::cout << v[i].first << " " << v[i].second << "\n";
    }
}
```

### 채점 포인트
- `m[key]++`로 자동 초기화 활용 (map은 없는 키 접근 시 0으로 기본 생성)
- map은 키로 자동 정렬이므로, **값으로 정렬하려면 vector로 옮겨야 함**
- `std::min(k, size())` 안전 처리

---

## 문제 7 ★★ (중간) — 문자열 처리와 정규화

**출제 근거:** lab028, lab039, lab054

### 출제 의도
문자열 조작, `ispunct`, `tolower` 활용

### 주어진 파일: `normalize.h`
```cpp
#ifndef NORMALIZE_H
#define NORMALIZE_H
#include <string>

// 주어진 문자열에 대해:
//  1) 앞뒤 공백 제거
//  2) 모든 구두점 제거
//  3) 모든 영문자를 소문자로 변환
// 위 세 단계를 거친 결과를 반환
std::string normalize(const std::string& input);

#endif
```

### 학생이 작성할 파일: `normalize.cpp`

### 입출력 예시
```cpp
normalize("  Hello, World!!  ");  // "hello world"
normalize("...A.B.C...");         // "abc"
normalize("   ");                 // ""
```

### 모범답안
```cpp
#include "normalize.h"
#include <cctype>
#include <algorithm>

std::string normalize(const std::string& input) {
    std::string s = input;

    // 1) trim
    auto start = s.find_first_not_of(' ');
    auto end = s.find_last_not_of(' ');
    if (start == std::string::npos) return "";
    s = s.substr(start, end - start + 1);

    // 2) 구두점 제거
    std::erase_if(s, [](unsigned char c){ return std::ispunct(c); });

    // 3) 소문자 변환
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });

    return s;
}
```

### 채점 포인트
- **빈 문자열 / 전부 공백 케이스** 처리 (find_first_not_of이 npos 반환)
- `ispunct`/`tolower`에 `unsigned char` 캐스팅 (정석)
- `std::erase_if` (C++20) 또는 erase-remove 관용구

---

## 문제 8 ★★★ (어려움) — 불변 클래스 설계 (Celsius/Fahrenheit 패턴 변형)

**출제 근거:** lab051 (Temperature), lab061 (Complex)

### 출제 의도
멤버 초기화 리스트, const 멤버 함수, 단위 변환, 불변 객체 설계

### 주어진 파일: `Money.h`
```cpp
#ifndef MONEY_H
#define MONEY_H
#include <string>

enum class Currency {
    KRW,  // 원
    USD   // 달러 (1 USD = 1400 KRW 고정)
};

class Money {
public:
    // amount의 단위는 주어진 currency 기준
    Money(double amount, Currency currency = Currency::KRW);

    // 두 Money 값을 더한 새 Money 반환. 결과의 통화는 *this 의 통화.
    Money add(const Money& other) const;

    // "12345.67 KRW\n" 또는 "8.75 USD\n" 형식 (소수점 2자리)
    std::string print() const;

private:
    double amount;
    Currency currency;

    double toKRW() const;
    double toUSD() const;
};

#endif
```

### 학생이 작성할 파일: `Money.cpp`
- 환율: 1 USD = 1400 KRW (고정)
- 모든 멤버 함수는 `const`여야 함 (불변 객체)

### 입출력 예시
```cpp
Money a(10000, Currency::KRW);
Money b(5, Currency::USD);        // 7000 KRW 상당
a.add(b).print();                 // "17000.00 KRW\n"
b.add(a).print();                 // "12.14 USD\n" (10000/1400 + 5 ≈ 12.142857)
```

### 모범답안
```cpp
#include "Money.h"
#include <sstream>
#include <iomanip>

constexpr double USD_TO_KRW = 1400.0;

Money::Money(double amount, Currency currency)
    : amount(amount), currency(currency) {}

double Money::toKRW() const {
    if (currency == Currency::KRW) return amount;
    return amount * USD_TO_KRW;
}

double Money::toUSD() const {
    if (currency == Currency::USD) return amount;
    return amount / USD_TO_KRW;
}

Money Money::add(const Money& other) const {
    if (currency == Currency::KRW) {
        return Money(amount + other.toKRW(), Currency::KRW);
    } else {
        return Money(amount + other.toUSD(), Currency::USD);
    }
}

std::string Money::print() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount << " "
        << (currency == Currency::KRW ? "KRW" : "USD") << "\n";
    return oss.str();
}
```

### 채점 포인트
- **멤버 초기화 리스트** 사용 (`: amount(amount), currency(currency)`)
- 모든 변환/조회 함수에 `const` 붙였는가
- add에서 *this/other를 수정하지 않고 **새 객체를 반환**하는가
- `std::fixed << std::setprecision(2)` 정확성

---

## 문제 9 ★★★ (어려움) — 메서드 체이닝 가능한 클래스

**출제 근거:** lab054 (StringSplitter)

### 출제 의도
`*this` 반환 (fluent interface), const 터미널 연산, 내부 상태 변경

### 주어진 파일: `NumberList.h`
```cpp
#ifndef NUMBERLIST_H
#define NUMBERLIST_H
#include <vector>

class NumberList {
private:
    std::vector<int> data_;

public:
    NumberList(const std::vector<int>& init);

    // 체이닝 가능 연산
    NumberList& addAll(int x);         // 모든 원소에 x를 더함
    NumberList& multiplyAll(int x);    // 모든 원소에 x를 곱함
    NumberList& removeIf(bool (*pred)(int));  // pred가 true인 원소 제거

    // 터미널 연산 (const)
    int sum() const;
    std::vector<int> toVector() const;
};

#endif
```

### 학생이 작성할 파일: `NumberList.cpp`

### 입출력 예시
```cpp
NumberList nl({1, 2, 3, 4, 5});
int result = nl.addAll(10)       // {11,12,13,14,15}
               .removeIf([](int x){ return x % 2 == 0; })  // {11,13,15}
               .multiplyAll(2)   // {22,26,30}
               .sum();            // 78
```

### 모범답안
```cpp
#include "NumberList.h"
#include <algorithm>

NumberList::NumberList(const std::vector<int>& init) : data_(init) {}

NumberList& NumberList::addAll(int x) {
    for (auto& v : data_) v += x;
    return *this;
}

NumberList& NumberList::multiplyAll(int x) {
    for (auto& v : data_) v *= x;
    return *this;
}

NumberList& NumberList::removeIf(bool (*pred)(int)) {
    std::erase_if(data_, pred);
    return *this;
}

int NumberList::sum() const {
    int s = 0;
    for (int v : data_) s += v;
    return s;
}

std::vector<int> NumberList::toVector() const {
    return data_;
}
```

### 채점 포인트
- 체이닝 메서드는 **`NumberList&` 반환 + `return *this;`**
- 터미널 연산(`sum`, `toVector`)은 **`const`** 선언
- 참조 리턴이므로 임시 객체 아님 (복사 방지)

---

## 문제 10 ★★★ (어려움) — 상속 + shared_ptr로 구성된 소규모 시스템

**출제 근거:** lab063 (University/Department/Faculty)

### 출제 의도
객체 관계 설계, `shared_ptr` 사용, `const` 반환, Rule of Zero

### 주어진 파일: `Library.hpp`
```cpp
#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include <string>
#include <memory>
#include <vector>

class Author {
public:
    Author(const std::string& name, int birthYear);
    const std::string& getName() const;
    int getBirthYear() const;
private:
    std::string name;
    int birthYear;
};

class Book {
public:
    // author는 nullptr 가능 (익명 저자)
    Book(const std::string& title,
         std::shared_ptr<Author> author = nullptr);
    const std::string& getTitle() const;
    std::shared_ptr<const Author> getAuthor() const;  // const 반환!
private:
    std::string title;
    std::shared_ptr<Author> author;
};

class Library {
public:
    explicit Library(const std::string& name);
    void addBook(const Book& book);
    void printCatalog() const;
private:
    std::string name;
    std::vector<Book> books;
};

#endif
```

### 학생이 작성할 파일: `Library.cpp`

`printCatalog()` 출력 형식:
```
Library: <name>
Total Books: <count>

Title: <title>
Author: <author_name>        ← author가 nullptr이면 "Unknown"
Born: <year>                 ← author가 nullptr이면 "Born: N/A"
(책마다 위 3줄 반복, 책 사이 공백줄은 없음. 첫 책 앞에만 공백줄 1개)
```

### 입출력 예시
```cpp
auto tolkien = std::make_shared<Author>("J.R.R. Tolkien", 1892);
Library lib("Main Library");
lib.addBook(Book("The Hobbit", tolkien));
lib.addBook(Book("Beowulf"));  // 익명
lib.printCatalog();
```
출력:
```
Library: Main Library
Total Books: 2

Title: The Hobbit
Author: J.R.R. Tolkien
Born: 1892
Title: Beowulf
Author: Unknown
Born: N/A
```

### 모범답안
```cpp
#include "Library.hpp"
#include <iostream>

// Author
Author::Author(const std::string& name, int birthYear)
    : name(name), birthYear(birthYear) {}
const std::string& Author::getName() const { return name; }
int Author::getBirthYear() const { return birthYear; }

// Book
Book::Book(const std::string& title, std::shared_ptr<Author> author)
    : title(title), author(author) {}
const std::string& Book::getTitle() const { return title; }
std::shared_ptr<const Author> Book::getAuthor() const { return author; }

// Library
Library::Library(const std::string& name) : name(name) {}
void Library::addBook(const Book& book) { books.push_back(book); }

void Library::printCatalog() const {
    std::cout << "Library: " << name << "\n";
    std::cout << "Total Books: " << books.size() << "\n";
    std::cout << "\n";
    for (const auto& b : books) {
        std::cout << "Title: " << b.getTitle() << "\n";
        auto a = b.getAuthor();
        if (a) {
            std::cout << "Author: " << a->getName() << "\n";
            std::cout << "Born: " << a->getBirthYear() << "\n";
        } else {
            std::cout << "Author: Unknown" << "\n";
            std::cout << "Born: N/A" << "\n";
        }
    }
}
```

### 채점 포인트
- 생성자: 멤버 초기화 리스트 사용, 기본 매개변수는 헤더에만 선언 (cpp에서 다시 쓰면 오류)
- `getAuthor()`가 `std::shared_ptr<const Author>` 반환 (수정 방지)
- `if (a)` 로 nullptr 체크, `->` 연산자로 멤버 접근
- Rule of Zero: 소멸자/복사 생성자 직접 작성 **불필요** (std::string, vector, shared_ptr 모두 자동 관리)

---

# 🔥 시험 직전 체크리스트

## 문법 실수 자주 나는 포인트
- [ ] 헤더에 기본 인수(`= nullptr`)를 썼으면 **.cpp에서는 쓰지 않는다** (중복 정의 에러)
- [ ] 멤버 초기화 리스트 문법: `: name(name), age(age) {}`
- [ ] const 멤버 함수: 닫는 괄호 뒤 `const` (`void foo() const {}`)
- [ ] 메서드 체이닝: `*this` 반환 + 리턴 타입은 `ClassName&`
- [ ] static 멤버 변수는 **.cpp에서 별도 정의** 필요: `int Logger::logLevel = 1;`
- [ ] map에 없는 key를 `m[key]`로 접근하면 **기본값으로 삽입됨** (의도된 동작인지 확인)
- [ ] `std::min_element`, `std::find_if` 등은 **이터레이터 반환** → `*` 필요

## 출력 형식 함정
- [ ] `std::fixed << std::setprecision(n)` — 소수점 n자리 고정
- [ ] 마지막 줄 개행(`\n`) 있는지 없는지 문제마다 다름
- [ ] map의 `structured binding`: `for (const auto& [key, value] : m)`

## OOP 설계 패턴
- [ ] **불변 객체(Immutable)**: 모든 변경 연산은 새 객체를 반환 (`return ClassName(...)`)
- [ ] **Rule of Zero**: std::string/vector/shared_ptr만 쓰면 소멸자 불필요
- [ ] **const correctness**: 읽기 전용 getter는 전부 const

## 추천 마지막 연습
1. **lab051 (Temperature)** 을 헤더만 보고 **백지에서** 다시 구현
2. **lab054 (StringSplitter)** 의 메서드 체이닝 패턴 암기
3. **lab063 (University/Department/Faculty)** 의 3단 계층 구조 스케치

---

> 🍀 **각 문제를 풀어본 뒤 실제 lab 폴더에서 직접 빌드 & 실행하여 자신의 답안을 검증하세요.**
> 빌드: `mkdir build && cd build && cmake .. && cmake --build .`

*문서 생성: 2026-04-23 — C++ 프로그래밍 실습 중간고사 대비*
