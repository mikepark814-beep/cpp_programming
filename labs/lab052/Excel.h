#ifndef EXCEL_H
#define EXCEL_H

#include <vector>
#include <string>
#include "Cell.h"

using Table = std::vector<std::vector<Cell>>;

class Excel {
private:
    Table data_;

public:
    Excel(const Table& data);
    double average(int fromRow, int fromCol, int toRow, int toCol) const;
    std::string display() const;

private:
    std::vector<Cell> getCellsInRange(int fromRow, int fromCol, int toRow, int toCol) const;
    bool hasStringInRange(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isValidRange(int fromRow, int fromCol, int toRow, int toCol) const;
}; // private 생성 시에 뒤에 ; 안붙이면 컴파일 안됨 이거 중요함!

#endif
