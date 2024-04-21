#ifndef __CELL__H__
#define __CELL__H__

#include <iostream>
#include <vector>
#include <string>
#include <ostream>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob);


class Cell
{
private:
    std::string val;
public:
    Cell();
    Cell(const Cell& rhv);
    Cell(Cell&& rhv);
    Cell(int num);
    Cell(double num);
    Cell(char ch);
    Cell(bool num);
    Cell(std::string str);
    Cell(const std::vector<int>& vec);

    std::string GetVal() const;
    void SetVal(std::string val);

    const Cell& operator=(const Cell& rhv);  
    const Cell& operator=(Cell&& rhv);  
    const Cell& operator=(int rhv);  
    const Cell& operator=(double rhv);  
    const Cell& operator=(char rhv);  
    const Cell& operator=(bool rhv);  
    const Cell& operator=(std::string rhv);  
    const Cell& operator=(const std::vector<int>& rhv);

    operator int();  
    operator double();  
    operator char();  
    operator bool();  
    operator std::string();  
    operator std::vector<int>();  
};

bool operator==(const Cell& lhv, const Cell& rhv);
bool operator!=(const Cell& lhv, const Cell& rhv);

std::ostream& operator<<(std::ostream& out, const Cell& ob);
std::istream& operator>>(std::istream& in, Cell& ob);


#endif //__CELL__H_
