/*****************************************************************//**
 * \file   Accessory.cpp
 * \brief  Содержит реализацию дополнительных функций
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include "Accessory.h"

#include <iostream>
#include <regex>

using namespace std;

void ClearConsole() {
    cout << "\x1B[2J\x1B[H" << endl;
}

void PressToContinue() {
    cout << "\nДля продолжения нажмите любую клавишу..."
        << endl;

    cin.get();
    cin.get();
}

void ShowMenu() {
    cout << " Menu:"
        << "\n 1.Add flight"
        << "\n 2.Edit flight"
        << "\n 3.Remove flight"
        << "\n 4.Find flights operated by air"
        << "\n 5.Display the entire list of flights"
        << "\n 6.Sort flights list"
        << "\n 7.Save database"
        << "\n 8.Load database"
        << "\n 0.Exit"
        << endl;
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

unsigned long GetULongValue(std::string_view enter_message, std::string_view error_message, std::function<bool(unsigned long)> check) {
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

        getline(std::cin, value);

    } while (!cin.good());

    return value;
}

std::string EnterStringValue(std::string_view enter_message, std::string_view error_message, std::function<bool(std::string_view)> check) {
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

