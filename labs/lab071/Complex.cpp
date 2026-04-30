#include "Complex.h"
#include <cmath>
#include <iomanip> // std::fixed, std::setprecision 등을 위해 포함

// TODO: Complex.h 에 선언된 함수/연산자를 모두 구현하세요.
// - 생성자 (멤버 초기화 리스트)
// - operator+ , operator-  (새 Complex 반환, const)
// - operator<              (magnitude → real → imag 순으로 tie-break)
// - operator<<             (friend, 비멤버)
//
// 모든 산술·비교 연산자는 *this 와 other 를 수정하지 않습니다 (const).

Complex::Complex(double real, double imag) : real(real) , imag(imag) {}
    // 힌트: : real(real), imag(imag)

// TODO: operator+ 구현 — 두 복소수의 실수부·허수부를 각각 더한 새 객체 반환
Complex Complex::operator+ (const Complex& other) const {
    return Complex(real + other.real , imag + other.imag);
}
// TODO: operator- 구현 — 두 복소수의 실수부·허수부를 각각 뺀 새 객체 반환
Complex Complex::operator- (const Complex& other) const {
    return Complex(real - other.real , imag - other.imag);
}
// TODO: operator< 구현
bool Complex::operator< (const Complex& other) const {
    double m1 = std::sqrt(real * real + imag * imag);
    double m2 = std::sqrt(other.real * other.real + other.imag * other.imag);

    if (std::abs(m1 - m2) > 1e-9) {
        return m1 < m2;
    }
    
    if (std::abs(real - other.real) > 1e-9) {
        return real < other.real;
    }

    return imag < other.imag;
}
//   1) 크기(magnitude = sqrt(real^2 + imag^2)) 로 먼저 비교
//   2) 크기가 같으면 real 값으로 비교
//   3) real 도 같으면 imag 값으로 비교
//   → 이 3단계 tie-break 이 있어야 std::map 이 서로 다른 복소수를 구분합니다.
//
// TODO: operator<< 구현 (friend, 비멤버)
std::ostream& operator<<(std::ostream& os , const Complex& c) {
    if (c.real == 0 && c.imag == 0) {
        os << "0";
    }
    
    else if (c.real == 0) {
        os << c.imag << "i";
    }

    else if (c.imag == 0) {
        os << c.real;
    }

    else {
        os << c.real;
        if (c.imag > 0) {
            os << "+";
        }
        os << c.imag << "i";
    }
    return os;
}

//   - real==0 && imag==0  →  "0"
//   - imag==0             →  "<real>"
//   - real==0             →  "<imag>i"
//   - else, imag>0        →  "<real>+<imag>i"
//   - else                →  "<real><imag>i"    // imag 자체에 '-' 가 붙어 있음
