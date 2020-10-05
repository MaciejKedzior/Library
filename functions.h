//
// Created by Dabutsu on 29.09.2020.
//

#ifndef BIBLIOTEKA_FUNCTIONS_H
#define BIBLIOTEKA_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>



enum class Scores{
    BardzoZla = 1,
    Zla,
    Srednia,
    Dobra,
    BardzoDobra
};

struct Book{
    Book();
    Book(std::wstring t_, std::wstring a_, std::wstring c_, unsigned int s_);
    explicit Book(std::vector<std::wstring> items);
    friend bool operator ==(const Book& b1, const Book& b2);
    std::wstring title;
    std::wstring author;
    std::wstring comment;
    Scores score;
};

std::wostream& operator<<(std::wostream& os, const Book &b);
void submitBook(std::wofstream& os);
std::vector<std::wstring> splitString(std::wstring wide, const std::wstring& delimiter);
void readFromFile(std::wifstream & os, std::vector<Book>& books);
#endif //BIBLIOTEKA_FUNCTIONS_H
