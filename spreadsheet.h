#ifndef spreadsheet_h
#define spreadsheet_h

#include <iostream>
#include <string>
#include <initializer_list>
#include "cell.h"

class SpreadSheet {
public:
    SpreadSheet(); //
    SpreadSheet(std::size_t s); //
    SpreadSheet(std::size_t s1, std::size_t s2); //
    SpreadSheet(const SpreadSheet& rhv); //
    SpreadSheet(SpreadSheet&& rhv); //
    ~SpreadSheet(); //
private:
    class Proxy {
    public:
        explicit Proxy(Cell* c, std::size_t s);
        Cell& operator[](std::size_t i);
        const Cell& operator[](std::size_t i) const;
    public:
        Proxy() = delete;
        Proxy(const Proxy&) = delete;
        Proxy(Proxy&&) = delete;
        
        const Proxy& operator=(const Proxy&) = delete;
        const Proxy& operator=(Proxy&&) = delete;
    private:
        Cell* p_sheet;
        std::size_t p_col;
    };
public:
    SpreadSheet& operator=(const SpreadSheet& rhv); //
    SpreadSheet& operator=(SpreadSheet&& rhv); //
    Proxy operator[](std::size_t i);//
    const Proxy operator[](std::size_t i) const;//
    void resizeRow(std::size_t s); //
    void resizeCol(std::size_t s); //
    void resize(std::size_t s1, std::size_t s2); //
    std::size_t get_row() const; //
    std::size_t get_col() const; //
    void clear(); //
    void rotate(int n);
    void mirrorh();
    void mirrorv();
    void mirrorD();
    void mirrord();
    void removeRow(int r);
    void removeCol(int c);
    void removeRows(std::initializer_list<int> r);
    void removeCols(std::initializer_list<int> c);
    SpreadSheet slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols);
    std::size_t maxLen() const;
private:
    void rotate_right();
    void rotate_left();
private:
    Cell** sheet;
    std::size_t row;
    std::size_t col;
};

bool operator==(SpreadSheet sh1, SpreadSheet sh2); //
bool operator!=(SpreadSheet sh1, SpreadSheet sh2); //
std::ostream& operator<<(std::ostream& out, SpreadSheet sh);

#endif
