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
6 табл - 1          Прямой
*/

#include "ClinicManager.h"
#include "HashTable.h"
#include "CLinkedList.h"

#include "Accessory.h"

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
    auto doctor = Doctor::EnterDoctor();

    ClinicManager clinic;

    auto res = clinic.AddDoctor(doctor);

    auto doctors = clinic.GetDoctors();

    int a = 1;

    /*
    HashTable<std::string, Patient, RegisterNumberHash> hash;

    hash.Insert(  "12-111111", {});
    hash.Insert( "12-111112", {});
    hash.Insert("12-111113", {});

    bool reset = hash.Erase("12-111111");;

    bool c = hash.Contains("12-111114");
    bool c1 = hash.Contains("12-111111");
    bool c2 = hash.Contains("12-111112");
    bool c3 = hash.Contains("12-111113");

    AvlTree<int, int> tree;

    tree.Insert(3, 1);
    tree.Insert(5, 2);
    tree.Insert(11, 55);


    tree.Insert(11, 777);
    
    auto a = tree.Contains(11);

    auto a235325 = tree.Contains(1587578785);

    auto e = tree.GetValue(11);

    tree.SymmetricForEach([](AvlTree<int, int>::Node node) {
        cout << node.key << " " << node.value << endl;
    });

    */

    /*
    СLinkedList<int> list;

    list.PushFront(6);
    list.PushFront(5);
    list.PushFront(4);
    list.PushFront(3);
    list.PushFront(88);
    list.PushFront(1);

    auto node = list.Find(3);
    auto node1 = list.Find(2);
    auto node2 = list.Find(1);

    BubleSort(list, std::greater<int>());
    */
    /*
    ClinicManager manager;

    auto patinet = Patient::EnterPatient();
    bool bAd1 = manager.AddNewPatient(patinet);

    auto patinet2 = Patient::EnterPatient();
    bool bAd2 = manager.AddNewPatient(patinet2);

    bool bR = manager.RemovePatient("11-123456");
    */
}