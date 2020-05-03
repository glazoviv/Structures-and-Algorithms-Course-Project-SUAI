/*****************************************************************//**
 * \file   Z8431GlazovSAODKP.cpp
 * \brief  
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include <iostream>
/*
1 табл - 3          Регистрация больных в поликлинике
2 табл - 1          Закрытое хеширование с линейным опробованием        +
3 табл - 3          Пузырьковый
4 табл - 3          Циклический двунаправленный
5 табл - 0          Симметричный
6 табл - 1          Прямой
*/

#include "ClinicManager.h"
#include "HashTable.h"

#include <fstream>
#include <random>

using namespace std;

std::vector<size_t> TestHash() {
    std::vector<size_t> result;
    result.resize(1024, 0);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> intGenerator(0, 100000000);

    for (int i = 0; i < 16000; ++i) {

        ++result[intGenerator(gen) % 1024];

    }

    int a = 1;

    return result;
}

bool AllocationToCsv(const std::vector<size_t>& arrHashTableAlloc)
{
    std::fstream file;
    file.open("test.csv", std::fstream::out);

    if (!file.is_open())
    {
        return false;
    }

    for (size_t i = 0; i < arrHashTableAlloc.size(); ++i)
    {
        file << arrHashTableAlloc[i] << std::endl;
    }

    file.close();

    return true;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    AllocationToCsv(TestHash());

    //Patient::EnterPatient();
    //Doctor::EnterDoctor();

    HashTable<std::string, Patient, RegisterNumberHash> hash;

    hash.Insert(  "12-111111", {});
    hash.Insert( "12-111112", {});
    hash.Insert("12-111113", {});

    bool reset = hash.Erase("12-111111");;

    bool c = hash.Contains("12-111114");
    bool c1 = hash.Contains("12-111111");
    bool c2 = hash.Contains("12-111112");
    bool c3 = hash.Contains("12-111113");

    

    auto all = hash.GetAll();

    //int a = 1;


    ClinicManager manager;

    auto patinet = Patient::EnterPatient();
    bool bAd1 = manager.AddNewPatient(patinet);

    auto patinet2 = Patient::EnterPatient();
    bool bAd2 = manager.AddNewPatient(patinet2);

    bool bR = manager.RemovePatient("11-123456");

    int a = 1;

}