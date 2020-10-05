
#include <io.h>
#include <fcntl.h>
#include <windows.h>

#include <locale>
//#include <codecvt>
#include "functions.h"

int main(){

    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wifstream file_read;
    std::wofstream file_write;

    int flag;
    std::vector<Book> books;

    while(true){
        std::wcout<<L"0. Wyjście 1. Wpis 2. Odczyt ";

        std::cin>>flag;

        if (flag == 1){
            file_write.open("../dane.txt", std::ios_base::app | std::ios_base::in);

            /*std::locale utf8_locale(std::locale(), new std::codecvt_utf8<char32_t>);
            file_write.imbue(utf8_locale);*/

            if (file_write.bad())
                std::wcout<<"Blad otwierania pliku!"<<std::endl;
            else
                submitBook(file_write);
            file_write.close();
        }
        else if (flag == 2){
            file_read.open("../dane.txt");
            //file_read.imbue(std::locale("pl_PL.UTF-8"));
            readFromFile(file_read, books);
            for (const auto& i: books)
                std::wcout<<i;
            file_read.close();
        }
        else break;
    }

    system("pause");
    return 0;
}
