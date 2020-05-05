/*****************************************************************//**
 * \file   Z8431GlazovSAODKP.cpp
 * \brief  Главный файл системы регистрации больных в поликлинике.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/

#include <iostream>

#include "Gui.h"

using namespace std;

/**
 * \brief   Точка входа в программу.
 * 
 * \return Код ошибки.
 */
int main() {
    setlocale(LC_ALL, "Rus");
    
    ClinicGui gui;
    gui.Handle();

    return 0;
}