//
// Created by Dabutsu on 29.09.2020.
//

#include "functions.h"

Book::Book() {
    title = reinterpret_cast<const wchar_t *>(" ");
    author = reinterpret_cast<const wchar_t *>(" ");
    comment = reinterpret_cast<const wchar_t *>(" ");
    score = Scores::BardzoZla;
}

Book::Book(std::wstring t_, std::wstring a_, std::wstring c_, unsigned int s_):title(std::move(t_)),author(std::move(a_)),comment(std::move(c_))
{
    switch (s_) {
        case 1:
            score = Scores::BardzoZla;
            break;
        case 2:
            score = Scores::Zla;
            break;
        case 3:
            score = Scores::Srednia;
            break;
        case 4:
            score = Scores::Dobra;
            break;
        case 5:
            score = Scores::BardzoDobra;
            break;
        default:
            break;
    }
}

Book::Book(std::vector<std::wstring> items):title(std::move(items[0])),author(std::move(items[1])),comment(std::move(items[2])){
    switch (std::stoi(items[3])) {
        case 1:
            score = Scores::BardzoZla;
            break;
        case 2:
            score = Scores::Zla;
            break;
        case 3:
            score = Scores::Srednia;
            break;
        case 4:
            score = Scores::Dobra;
            break;
        case 5:
            score = Scores::BardzoDobra;
            break;
        default:
            break;
    }
}


std::wostream& operator<<(std::wostream& os, const Book &b) {
    int value = static_cast<std::underlying_type<Scores>::type>(b.score);
    return os<<"Tytul: "<<b.title<<" Autor: "<<b.author<<" Komentarz: "<<b.comment<<" Ocena: "<<value<<std::endl;
}

bool operator == (const Book& b1, const Book& b2){
    return (b1.comment == b2.comment) && (b1.author == b2.author) && (b1.title == b2.title);
}


void submitBook(std::wofstream& os){
    Book tmp;
    while(true) {
        std::wcout << "Podaj tytul ksiazki: "; std::getline(std::wcin, tmp.title);
        if (tmp.title.empty())
            std::wcout << "Nie podano tytulu! Sprobuj jeszcze raz" << std::endl;
        else
            break;
    }
    while(true) {
        std::wcout << "Podaj imie i nazwisko autora: "; std::getline(std::wcin, tmp.author);
        if (tmp.author.empty())
            std::wcout << "Nie podano imienia i nazwiska! Sprobuj jeszcze raz" << std::endl;
        else
            break;
    }
    while(true) {
        std::wcout << "Podaj komentarz: "; std::getline(std::wcin, tmp.comment);
        if (tmp.comment.empty())
            std::wcout << "Nie podano komentarza! Sprobuj jeszcze raz" << std::endl;
        else
            break;
    }
    while(true) {
        int buffer;
        std::wcout << "Podaj ocene (liczba od 1 do 5): "; std::cin>>buffer;
        if (buffer < 1 or buffer > 5)
            std::wcout<<"Bledna wartosc! Wpisz cyfre od 1 do 5"<<std::endl;
        else{
            switch (buffer) {
                case 1:
                    tmp.score = Scores::BardzoZla;
                    break;
                case 2:
                    tmp.score = Scores::Zla;
                    break;
                case 3:
                    tmp.score = Scores::Srednia;
                    break;
                case 4:
                    tmp.score = Scores::Dobra;
                    break;
                case 5:
                    tmp.score = Scores::BardzoDobra;
                    break;
                default:
                    break;
            }
            break;
        }
    }
    int value = static_cast<std::underlying_type<Scores>::type>(tmp.score);
    os<<tmp.title<<"|"<<tmp.author<<"|"<<tmp.comment<<"|"<<value<<std::endl;
    std::wcout<<"Zapisano do pliku"<<std::endl;
}

std::vector<std::wstring> splitString(std::wstring wide, const std::wstring& delimiter){
    std::vector <std::wstring> temp;
    size_t position=0;
    std::wstring token;

    while( (position = wide.find(delimiter)) != std::wstring::npos){
        token = wide.substr(0, position);
        temp.emplace_back(std::wstring(token.begin(), token.end()));
        wide.erase(0, position + delimiter.length());
    }
    temp.emplace_back(wide);

    return temp;
}

void readFromFile(std::wifstream & os, std::vector<Book>& books){
    std::wstring temp;
    while (std::getline(os, temp)){
        Book temporary (splitString(temp,L"|"));
        if (std::find(books.begin(), books.end(), temporary) != books.end())
            continue;
        else
            books.emplace_back(temporary);
    }
    std::wcout<<"Pobrano dane z pliku!"<<std::endl;
}