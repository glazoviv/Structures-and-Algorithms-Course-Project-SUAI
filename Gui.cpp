/*****************************************************************//**
 * \file   Gui.cpp
 * \brief  Содержит реализацию класса для управления поликлиникой
 *		   через графический интерфейс.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include "Gui.h"
#include "Accessory.h"

#include <iostream>

using namespace std;

void ClinicGui::Handle() {
    size_t nCommand = 1;

    while (nCommand != 0) {
        ClearConsole();
        ShowMenu();

        nCommand = GetULongValue();

        ClearConsole();

        switch (nCommand) {
            case 1: 
                RegistrationNewPatient();
                break;
            case 2: 
                ErasePatient();
                break;
            case 3: 
                ShowPatients();
                break;
            case 4:
                ErasePatients();
                break;
            case 5:
                break;
            case 6:
                AddNewDoctor();
                break;
            case 7:
                EraseDoctor();
                break;
            case 8:
                ShowDoctors();
                break;
            case 9:
                EraseDoctors();
                break;
            case 10:

                break;
            case 11:

                break;
            case 12:

                break;
            case 0:
                std::cout << "Выход\nСпасибо за использование программы!";
                break;
            default:
                std::cout << "Ошибка: неизвестная команда";
                break;  
        }
        cout << endl;
        PressToContinue();
    }
}



void ClinicGui::ShowMenu() {
    cout << " Меню:"
        << "\n 1.Регистрация нового больного"
        << "\n 2.Удаление данных о больном"
        << "\n 3.Показать информацию о больных"
        << "\n 4.Очистка данных о больных"
        << "\n 5.Поиск больного"

        << "\n 6.Добавить врача"
        << "\n 7.Удалить сведения о враче"
        << "\n 8.Показать всех врачей"
        << "\n 9.Очистить данные о врачах"
        << "\n 10.Поиск по врачам"

        << "\n 11.Регистрачия направления к врачу"
        << "\n 12.Возврат направления к врачу"

        << "\n 0.Выход"
        << endl;
}

void ClinicGui::RegistrationNewPatient() {
    auto patient = Patient::EnterPatient();

    auto result = clinic_.AddPatient(patient);

    ShowMessage(result ? "Пациент добавлен успешно" : "Ошибка: Пациент уже существует");
}

void ClinicGui::ErasePatient() {
    ShowHeader("Удаление данных о больном");

    auto number = EnterRegisterNumber();
    auto result = clinic_.ErasePatient(number);

    ShowMessage(result ? "Пациент удален успешно" : "Ошибка: Пациент отсутствует");
}

void ClinicGui::ShowPatients() {
    ShowHeader("Показать информацию о больных");

    auto patients = clinic_.GetPatients();

    if(patients.empty()) {
        cout << "Пациенты отсутствуют";
    }

    for (int i = 0; i < patients.size(); ++i) {
        if(!patients[i].expired())
        cout << i + 1 << ". " << "Рег. номер: " << patients[i].lock()->GetRegistrationNumber() 
             << " ФИО: " << patients[i].lock()->GetName() 
             << '\n';
    }
}

void ClinicGui::ErasePatients() {
    ShowHeader("Удаление информации о больных");

    clinic_.ErasePatients();
    ShowMessage("Больные успешно удалены");
}

void ClinicGui::AddNewDoctor() {
    auto doctor = Doctor::EnterDoctor();

    auto result = clinic_.AddDoctor(doctor);

    ShowMessage(result ? "Доктор добавлен успешно" : "Ошибка: Доктор уже существует");
}

void ClinicGui::EraseDoctor() {
    ShowHeader("Удаление сведений о враче");

    auto name = EnterDoctorName();
    auto result = clinic_.EraseDoctor(name);

    ShowMessage(result ? "Доктор удален успешно" : "Ошибка: Доктор не найден");
}

void ClinicGui::ShowDoctors() {
    ShowHeader("Показать всех врачей");

    auto doctors = clinic_.GetDoctors();

    if (doctors.empty()) {
        cout << "Докторов не найдено";
    }

    for (int i = 0; i < doctors.size(); ++i) {
        if (!doctors[i].expired())
            cout << i + 1 << ". " << "ФИО: " << doctors[i].lock()->GetName()
            << " расписание: " << doctors[i].lock()->GetSchedule()
            << '\n';
    }
}

void ClinicGui::EraseDoctors() {
    ShowHeader("Очистка данных о врачах");
    clinic_.EraseDoctors();
    ShowMessage("Данные удалены успешно");
}

void ClinicGui::ShowMessage(std::string_view message) {
    cout << '\n' << message;
}

void ClinicGui::ShowHeader(std::string_view header) {
    cout << header << "\n\n";
}
