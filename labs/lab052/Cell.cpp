#include "Cell.h"
#include <iomanip>
#include <sstream>

Cell::Cell() : type_{CellType::STRING}, stringVal_{""}, intVal_{0}, doubleVal_{0.0} {}

// TODO: 아래 생성자와 멤버 함수를 구현하세요.

Cell::Cell(const std::string val) {
    // 문자열 값을 저장하는 생성자
    // type_ 을 STRING 으로 설정하세요.
    type_ = CellType::STRING;
    stringVal_ = val;
}

Cell::Cell(int val) {
    // 정수 값을 저장하는 생성자
    // type_ 을 INT 로 설정하세요.
    type_ = CellType::INT;
    intVal_ = val;
}

Cell::Cell(double val) {
    // 실수 값을 저장하는 생성자
    // type_ 을 DOUBLE 로 설정하세요.
    type_ = CellType::DOUBLE;
    doubleVal_ = val;
}

bool Cell::isNumeric() const {
    // INT 또는 DOUBLE 이면 true 를 반환합니다.
    if (type_ == CellType::INT || type_ == CellType::DOUBLE) {
        return true;
    }
    else {
        return false;
    }
}

bool Cell::isString() const {
    // STRING 이면 true 를 반환합니다.
    if (type_ == CellType::STRING) {
        return true;
    }
    else {
        return false;
    }
}

double Cell::getNumericValue() const {
    // INT 이면 intVal_ 을 double 로, DOUBLE 이면 doubleVal_ 을 반환합니다.
    // STRING 이면 0.0 을 반환합니다.
    if (type_ == CellType::INT) {
        return static_cast<double>(intVal_);
    }
    else if (type_ == CellType::DOUBLE) {
        return doubleVal_;
    }

    else {
        return 0.0;
    }
}

std::string Cell::toString() const {
    // STRING 이면 stringVal_ 을 그대로 반환합니다.
    // INT 이면 정수를 문자열로 변환합니다 (예: 87 → "87").
    // DOUBLE 이면 소수점 1자리로 변환합니다 (예: 75.7 → "75.7").
    // 힌트: std::ostringstream + std::fixed + std::setprecision(1)
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);

    if (type_ == CellType::STRING) {
        return stringVal_;
    }
    else if (type_ == CellType::INT) {
        oss << intVal_;
        return oss.str();
    }
    else {
        oss << std::fixed << std::setprecision(1) << doubleVal_;
        return oss.str();
    }
}
