/*****************************************************************//**
 * \file   Z8431GlazovSAODKP.cpp
 * \brief  Главный файл системы регистрации больных в поликлинике.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include <iostream>
/*
1 табл - 3          Регистрация больных в поликлинике
2 табл - 1          Закрытое хеширование с линейным опробованием        +
3 табл - 3          Пузырьковый +
4 табл - 3          Циклический двунаправленный +
5 табл - 0          Симметричный    +
6 табл - 1          Прямой  +
*/

#include "ClinicManager.h"
#include "HashTable.h"
#include "CLinkedList.h"

#include "Accessory.h"

#include <fstream>
#include <random>

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    
    ClinicManager clinic;
    

}