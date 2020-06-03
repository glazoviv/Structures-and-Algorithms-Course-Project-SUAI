/*****************************************************************//**
 * \file   Accessory.cpp
 * \brief  Содержит реализацию дополнительных функций
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include "Accessory.h"

#include <iostream>
#include <iomanip>
#include <regex>

using namespace std;

void ClearConsole() {
    cout << "\x1B[2J\x1B[H" << endl;
}

void PressToContinue() {
    cout << "\nДля продолжения нажмите любую клавишу..."
        << endl;

    cin.get();
#ifdef __linux__
    cin.get();
#endif
}

unsigned long GetULongValue() {
    bool first = true;

    const regex regex("[[:digit:]]+");

    string value;

    do {
        if (first) {
            first = false;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Ошибка ввода, значение должно быть целым положительным." << endl;
        }

        value = EnterStringValue();

    } while (!regex_match(value, regex));

    return stoul(value.c_str());
}

unsigned long GetULongValue(string_view enter_message, string_view error_message, function<bool(unsigned long)> check) {
    bool bFirst = true;
    unsigned long temp = 0;

    do {
        if (bFirst) {
            bFirst = false;
        }
        else {
            cout << error_message << endl;
        }

        cout << enter_message << " ";

        temp = GetULongValue();

    } while (!check(temp));

    return temp;
}


string EnterStringValue() {
    bool first = true;
    string value;

    do {
        if (first) {
            first = false;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Ошибка ввода, значение должно быть строкой.\n";
        }

        getline(cin, value);

    } while (!cin.good());

    return value;
}

string EnterStringValue(string_view enter_message, string_view error_message, function<bool(string_view)> check) {
    bool bFirst = true;
    string temp;

    do {
        if (bFirst) {
            bFirst = false;
        }
        else {
            cout << error_message << "\n\n";
        }

        cout << enter_message << " ";

        temp = EnterStringValue();

    } while (!check(temp));

    return temp;
}

int FindSubstring(string_view str, string_view substring, int start_pos) {
    if(start_pos >= str.size() 
        || start_pos < 0 
        ||  substring.size() > str.size()) {
        return -1;
    }

    auto str_size = str.size();
    auto sub_size = substring.size();

    int i = start_pos -1;
    int j = 0;

    do {
        j = 0;
        i++;

        while ((j < sub_size) && (str.at(i + j) == substring.at(j))) {
            j++;
        }
    } while (j < sub_size && i < str_size - sub_size);

    return j == sub_size ? i : -1;
}

void PrintLine(size_t size) {
    cout << setfill('-')
        << setw(size)
        << ""
        << setfill(' ')
        << "";
}