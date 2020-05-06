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
                FindPatient();
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
                FindDoctor();
                break;
            case 11:
                RegisterReferral();
                break;
            case 12:
                RefundRefferal();
                break;
            case 0:
                ShowMessage("Выход\nСпасибо за использование программы!");
                break;
            default:
                ShowMessage("Ошибка: Неизвестная команда");
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

        << "\n 11.Регистрация направления к врачу"
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

void ClinicGui::FindPatient() {
    ShowHeader("Поиск больного");

    auto number = GetULongValue("По какому параметру будет производится поиск?"
        "\n1.По регистрационному номеру"
        "\n2.По ФИО\n",
        "Ошибка: значение должно быть 1 или 2",
        [](unsigned long val) {
        return val == 1 || val == 2;
    });

    ClearConsole();

    if(number == 1) {
        FindPatientByNumber();
    }
    else {
        FindPatientsByName();
    }
}

void ClinicGui::FindPatientByNumber() {
    ShowHeader("Поиск пациента по регистрационному номеру");

    auto register_number = EnterRegisterNumber();
    auto[patient_w, doctor_name] = clinic_.GetPatient(register_number);

    if(auto patient = patient_w.lock()) {
        cout << "ФИО: " << patient->GetName() << '\n'
             << "Регистрационный номер: " << patient->GetRegistrationNumber() << '\n'
             << "Год рождения: " << patient->GetYear() << '\n'
             << "Адрес: " << patient->GetAddress() << '\n'
             << "Место работы: " << patient->GetWork() << '\n';

        if(doctor_name.empty()) {
            cout << "Направлений к врачу нет";
        }
        else {
            cout << "ФИО врачу к которому есть направление: " << doctor_name;
        }
    }
    else {
        ShowMessage("Пациент не найден");
    }
}

void ClinicGui::FindPatientsByName() {
    ShowHeader("Поиск пациента по ФИО");

    auto name = EnterPatientName();
    auto patients = clinic_.GetPatientsByName(name);

    if (patients.empty()) {
        cout << "Пациенты не найдены";
    }

    for (int i = 0; i < patients.size(); ++i) {
        if (!patients[i].expired())
            cout << i + 1 << ". " << "Рег. номер: " << patients[i].lock()->GetRegistrationNumber()
            << " ФИО: " << patients[i].lock()->GetName()
            << '\n';
    }

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
        ShowMessage("Докторов не найдено");
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

void ClinicGui::FindDoctor() {
    ShowHeader("Поиск врача");

    auto number = GetULongValue("По какому параметру будет производится поиск?"
        "\n1.По ФИО"
        "\n2.По должности\n",
        "Ошибка: значение должно быть 1 или 2",
        [](unsigned long val) {
        return val == 1 || val == 2;
    });

    ClearConsole();

    if (number == 1) {
        FindDoctorByName();
    }
    else {
        FindDoctorsByPosition();
    }
}

void ClinicGui::FindDoctorByName() {
    ShowHeader("Поиск врача по ФИО");

    auto name = EnterDoctorName();
    const auto&[doctor_w, patients] = clinic_.GetDoctorByName(name);

    if(auto doctor = doctor_w.lock()) {
        cout << "ФИО: "             << doctor->GetName()            << '\n'
             << "Должность: "       << doctor->GetPosition()        << '\n'
             << "Номер кабинета: "  << doctor->GetCabinetNumber()   << '\n'
             << "График приема: "   << doctor->GetSchedule()        << '\n';

        if(patients.empty()) {
            cout << "Пациентов на приём нет";
        } 
        else {
            cout << "Рег. номера пациентов:";

            for(string_view number : patients) {
                cout << '\n' << number;
            }
        }

    } else {
        ShowMessage("Доктор не найден");
    }
}

void ClinicGui::FindDoctorsByPosition() {
    ShowHeader("Поиск врача по должности");

    auto position = EnterStringValue("Введите должность или её часть:",
        {},
        [](auto str) {
        return true;
    });

    auto doctors = clinic_.GetDoctorsByPosition(position);
    
    if(doctors.empty()) {
        ShowMessage("Докторов не найдено");
    }

    for (auto doctor_w : doctors) {
        if(auto doctor = doctor_w.lock()) {
            PrintLine(70);

            cout << "ФИО: " << doctor->GetName() << '\n'
                 << "Должность: " << doctor->GetPosition() << '\n'
                 << "Номер кабинета: " << doctor->GetCabinetNumber() << '\n'
                 << "График приема: " << doctor->GetSchedule();
        }
    }
}

void ClinicGui::RegisterReferral() {
    ShowHeader("Регистрация направления к врачу");

    auto referral = Referral::Enter();
    auto code = clinic_.RegistrationRefferal(referral);

    string message = "Направление зарегистрированно успешно";
    
    switch(code) {
    case ClinicManager::ReferralError::DOCTOR_NOT_EXISTS:
        message = "Ошибка: доктор не найден";
        break;
    case ClinicManager::ReferralError::PATIENT_NOT_EXISTS:
        message = "Ошибка: пациент не найден";
        break;
    case ClinicManager::ReferralError::REFERRAL_EMPTY:
        message = "Ошибка: направление не заполнено";
        break;
    case ClinicManager::ReferralError::DATETIME_BUSY:
        message = "Ошибка: на это время уже существует запись";
        break;
    }

    ShowMessage(message);
}

void ClinicGui::RefundRefferal() {
    ShowHeader("Регистрация направления к врачу");

    auto referral = Referral::Enter();
    auto result = clinic_.RefundRefferal(referral);

    ShowMessage(result ? "Направление возвращено успешно" : "Ошибка: направление не найдено");
}

void ClinicGui::ShowMessage(std::string_view message) {
    cout << '\n' << message;
}

void ClinicGui::ShowHeader(std::string_view header) {
    cout << header << "\n\n";
}