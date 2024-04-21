#include <iostream>
#include <string>
#include <iomanip>
#include <initializer_list>
#include <algorithm>
#include "cell.h"
#include "spreadsheet.h"

SpreadSheet::SpreadSheet()
: row(2)
, col(2)
{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i)
    {
        sheet[i] = new Cell[col];
    }
}

SpreadSheet::SpreadSheet(std::size_t s)
: row(s)
, col(s)
{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i)
    {
        sheet[i] = new Cell[col];
    }
}

SpreadSheet::SpreadSheet(std::size_t s1, std::size_t s2)
: row(s1)
, col(s2)
{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i)
    {
        sheet[i] = new Cell[col];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)
: row(rhv.row)
, col(rhv.col)
{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i)
    {
        sheet[i] = new Cell[col];
    }

    for(std::size_t i = 0; i < row; ++i)
    {
        for(std::size_t j = 0; j < col; ++j)
        {
            sheet[i][j] = rhv.sheet[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv)
: row(std::move(rhv.row))
, col(std::move(rhv.col))
{
    sheet = rhv.sheet;
    rhv.row = 0;
    rhv.col = 0;
    rhv.sheet = nullptr;
}

SpreadSheet::~SpreadSheet()
{
    clear();
}

SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv)
{
    if(this != &rhv)
    {
        clear();
        row = rhv.row;
        col = rhv.col;
        sheet = new Cell*[row];
        for(std::size_t i = 0; i < row; ++i)
        {
            sheet[i] = new Cell[col];
        }
        for(std::size_t i = 0; i < row; ++i)
        {
            for(std::size_t j = 0; j < col; ++j)
            {
                sheet[i][j] = rhv.sheet[i][j];
            }
        }
    }
    return *this;
}

SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv)
{
    if(this != &rhv)
    {
        clear();
        row = std::move(rhv.row);
        col = std::move(rhv.col);
        sheet = rhv.sheet;

        rhv.col = 0;
        rhv.row = 0;
        rhv.sheet = nullptr;

    }
    return *this;
}

SpreadSheet::Proxy SpreadSheet::operator[](std::size_t i)
{
    if(i < 0 || i >= row)
    {
        throw std::out_of_range("index is out of range");
    }
    return Proxy(sheet[i], col);
}

const SpreadSheet::Proxy SpreadSheet::operator[](std::size_t i) const
{
    if(i >= row)
    {
        throw std::out_of_range("index is out of range");
    }
    return Proxy(sheet[i], col);
}

void SpreadSheet::resizeRow(std::size_t s)
{
    if(s == row)
    {
        return;
    }
    Cell** ptr = new Cell*[s];
    for(std::size_t i = 0; i < s; ++i)
    {
        ptr[i] = new Cell[col];
    }

    std::size_t min = s < row ? s : row;

    for(std::size_t i = 0; i < min; ++i)
    {
        for(std::size_t j = 0; j < col; ++j)
        {
            ptr[i][j] = sheet[i][j];
        }
    }
    std::size_t ncol = col;
    clear();
    sheet = ptr;
    row = s;
    col = ncol;
    ptr = nullptr;
}

void SpreadSheet::resizeCol(std::size_t s)
{
    if(s == col)
    {
        return;
    }
    Cell** ptr = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i)
    {
        ptr[i] = new Cell[s];
    }

    std::size_t min = s < col ? s : col;

    for(std::size_t i = 0; i < row; ++i)
    {
        for(std::size_t j = 0; j < min; ++j)
        {
            ptr[i][j] = sheet[i][j];
        }
    }
    std::size_t nrow = row;
    clear();
    sheet = ptr;
    col = s;
    row = nrow;
    ptr = nullptr;
}

void SpreadSheet::resize(std::size_t s1, std::size_t s2)
{
    if(row == s1 && col == s2)
    {
        return;
    }
    if(row == s1)
    {
        resizeCol(s2);
        return;
    }
    if(col == s2)
    {
        resizeRow(s1);
        return;
    }
    Cell** ptr = new Cell*[s1];
    for(std::size_t i = 0; i < s1; ++i)
    {
        ptr[i] = new Cell[s2];
    }

    std::size_t minRow = s1 < row ? s1 : row;
    std::size_t minCol = s2 < col ? s2 : col;

    for(std::size_t i = 0; i < minRow; ++i)
    {
        for(std::size_t j = 0; j < minCol; ++j)
        {
            ptr[i][j] = sheet[i][j];
        }
    }

    clear();
    sheet = ptr;
    row = s1;
    col = s2;
    ptr = nullptr;
}

std::size_t SpreadSheet::get_row() const
{
    return row;
}

std::size_t SpreadSheet::get_col() const
{
    return col;
}

void SpreadSheet::clear()
{
    if(sheet)
    {
        for(std::size_t i = 0; i < row; ++i)
        {
            delete[]sheet[i];
        }
        delete[]sheet;
        sheet = nullptr;
    }
    row = 0;
    col = 0;
}

SpreadSheet::Proxy::Proxy(Cell* c, std::size_t s)
: p_col(s)
, p_sheet(c)
{}

Cell& SpreadSheet::Proxy::operator[](std::size_t i)
{
    if(i >= p_col)
    {
        throw std::out_of_range("index is out of range");
    }
    return p_sheet[i];
}

const Cell& SpreadSheet::Proxy::operator[](std::size_t i) const
{
    if(i >= p_col)
    {
        throw std::out_of_range("index is out of range");
    }
    return p_sheet[i];
}

void SpreadSheet::rotate(int n)
{
    n = n > 0 ? (n%4) : (n%4 + 4);
    switch(n)
    {
        case 0:
            return;
        case 2:
            rotate_right();
        case 1:
            rotate_right();
            return;
        case 3:
            rotate_left();
            return;
    }
}

void SpreadSheet::rotate_right()
{
    Cell** tmp = new Cell*[col];
    for(int i = 0; i < col; ++i)
    {
        tmp[i] = new Cell[row];
    }
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            tmp[j][row - i - 1] = sheet[i][j];
        }
    }
    for(int i = 0; i < row; ++i)
    {
        delete[] sheet[i];
    }
    delete[] sheet;
    sheet = tmp;
    std::swap(row, col);
}

void SpreadSheet::rotate_left()
{
    Cell** tmp = new Cell*[col];
    for(int i = 0; i < col; ++i)
    {
        tmp[i] = new Cell[row];
    }
    for(int i = 0; i < col; ++i)
    {
        for(int j = 0; j < row; ++j)
        {
            tmp[i][j] = sheet[j][col - i - 1];
        }
    }
    for(int i = 0; i < row; ++i)
    {
        delete[] sheet[i];
    }
    delete[] sheet;
    sheet = tmp;
    std::swap(row, col);

}

void SpreadSheet::mirrorh()
{
    for(int i = 0; i < row / 2; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            std::swap(sheet[i][j], sheet[row - i - 1][j]);
        }
    }
}


void SpreadSheet::mirrorv()
{
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col / 2; ++j)
        {
            std::swap(sheet[i][j], sheet[i][col - j - 1]);
        }
    }
}


void SpreadSheet::mirrorD()
{
    Cell** sh = new Cell*[col];
    for(int i = 0; i < col; ++i)
    {
        sh[i] = new Cell[row];
    }
    for(int i = 0; i < col; ++i)
    {
        for(int j = 0; j < row; ++j)
        {
            sh[i][j] = sheet[j][i];
        }
    }
    for(int i = 0; i < row; ++i)
    {
        delete[] sheet[i];
    }
    delete[] sheet;
    sheet = sh;
    std::swap(row, col);
}

void SpreadSheet::mirrord()
{
    rotate_left();
    mirrorv();
}

void SpreadSheet::removeRow(int r)
{
    if(r < 0 || r >= row)
    {
        throw std::out_of_range("there is no such row");
    }
    delete[] sheet[r];
    for(int i = r; i < row - 1; ++i)
    {
        sheet[i] = sheet[i + 1];
    }
    --row;
}

void SpreadSheet::removeCol(int c)
{
    if(c < 0 || c >= col)
    {
        throw std::out_of_range("there is no such col");
    }

    Cell** tmp = new Cell*[row];
    for(int i = 0; i < row; ++i)
    {
        tmp[i] = new Cell[col - 1];
    }

    for(int i = 0; i < row; ++i)
    {
        int k = 0;
        for(int j = 0; j < col; ++j)
        {
            if(j == c)
            {
                continue;
            }
            tmp[i][k] = sheet[i][j];
            ++k;
        }
    }

    std::size_t nrow = row;
    std::size_t ncol = col - 1;
    clear();
    row = nrow;
    col = ncol;
    sheet = tmp;
    tmp = nullptr;
}

SpreadSheet SpreadSheet::slice(std::initializer_list<std::size_t> rows, std::initializer_list<std::size_t> cols)
{
    SpreadSheet nSheet(rows.size(), cols.size());
    std::size_t rowi = 0;
    for(std::size_t i : rows)
    {
        std::size_t coli = 0;
        for(std::size_t j : cols)
        {
            nSheet.sheet[rowi][coli] = sheet[i][j];
            ++coli;
        }
        ++rowi;
    }
    return nSheet;
}

void SpreadSheet::removeRows(std::initializer_list<int> r)
{
    int count = 0;
    for(int i : r)
    {
        i -= count;
        removeRow(i);
        ++count;
    }
}

void SpreadSheet::removeCols(std::initializer_list<int> c)
{
    int count = 0;
    for(int i : c)
    {
        i -= count;
        removeCol(i);
        ++count;
    }
}

std::size_t SpreadSheet::maxLen() const
{
    std::size_t maxCellSize = 0;

    for (std::size_t i = 0; i < row; ++i) {
        for (std::size_t j = 0; j < col; ++j) {
            std::size_t cellSize = sheet[i][j].get_cell().size();
            maxCellSize = std::max(maxCellSize, cellSize);
        }
    }

    return maxCellSize;
}

bool operator==(SpreadSheet sh1, SpreadSheet sh2)
{
    if(sh1.get_row() != sh2.get_row() && sh1.get_col() != sh2.get_col())
    {
        return false;
    }
    for(std::size_t i = 0; i < sh1.get_row(); ++i)
    {
        for(std::size_t j = 0; j < sh1.get_col(); ++j)
        {
            if(sh1[i][j] != sh2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(SpreadSheet sh1, SpreadSheet sh2)
{
    return !(sh1 == sh2);
}

std::ostream& operator<<(std::ostream& out, SpreadSheet sheet)
{
    const int width = 23 > sheet.maxLen() ? 23 : sheet.maxLen(); 
    const char fillChar = ' ';

    for (int i = 0; i < sheet.get_col(); ++i) 
    {
        out << std::setw(width) << std::setfill('_') << '_';
    }
    out << std::endl;

    for (std::size_t i = 0; i < sheet.get_row(); ++i) 
    {
        for (std::size_t j = 0; j < sheet.get_col(); ++j) 
        {
            out << "|";
            out << std::setw(width - 2) << std::setfill(fillChar) << sheet[i][j];
        }
        out << "|" << std::endl;

        for (int j = 0; j < sheet.get_col(); ++j) 
        {
            out << std::setw(width) << std::setfill('_') << '_';
        }
        out << std::endl;
    }

    return out;
}
