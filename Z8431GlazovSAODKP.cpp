/*****************************************************************//**
 * \file   Z8431GlazovSAODKP.cpp
 * \brief  Главный файл системы регистрации больных в поликлинике.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/

#include <iostream>

#include <windows.h>

#include "Gui.h"

using namespace std;

/**
 * \brief   Точка входа в программу.
 * 
 * \return Код ошибки.
 */
int main() {
    setlocale(LC_ALL, "Rus");

    //Фикс на случай полома настроек консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    ClinicGui gui;
    gui.Handle();

    return 0;
}