/*****************************************************************//**
 * \file   Gui.cpp
 * \brief  �������� ���������� ������ ��� ���������� ������������
 *		   ����� ����������� ���������.
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
                std::cout << "�����\n������� �� ������������� ���������!";
                break;
            default:
                std::cout << "������: ����������� �������";
                break;  
        }
        cout << endl;
        PressToContinue();
    }
}



void ClinicGui::ShowMenu() {
    cout << " ����:"
        << "\n 1.����������� ������ ��������"
        << "\n 2.�������� ������ � �������"
        << "\n 3.�������� ���������� � �������"
        << "\n 4.������� ������ � �������"
        << "\n 5.����� ��������"

        << "\n 6.�������� �����"
        << "\n 7.������� �������� � �����"
        << "\n 8.�������� ���� ������"
        << "\n 9.�������� ������ � ������"
        << "\n 10.����� �� ������"

        << "\n 11.����������� ����������� � �����"
        << "\n 12.������� ����������� � �����"

        << "\n 0.�����"
        << endl;
}

void ClinicGui::RegistrationNewPatient() {
    auto patient = Patient::EnterPatient();

    auto result = clinic_.AddPatient(patient);

    ShowMessage(result ? "������� �������� �������" : "������: ������� ��� ����������");
}

void ClinicGui::ErasePatient() {
    ShowHeader("�������� ������ � �������");

    auto number = EnterRegisterNumber();
    auto result = clinic_.ErasePatient(number);

    ShowMessage(result ? "������� ������ �������" : "������: ������� �����������");
}

void ClinicGui::ShowPatients() {
    ShowHeader("�������� ���������� � �������");

    auto patients = clinic_.GetPatients();

    if(patients.empty()) {
        cout << "�������� �����������";
    }

    for (int i = 0; i < patients.size(); ++i) {
        if(!patients[i].expired())
        cout << i + 1 << ". " << "���. �����: " << patients[i].lock()->GetRegistrationNumber() 
             << " ���: " << patients[i].lock()->GetName() 
             << '\n';
    }
}

void ClinicGui::ErasePatients() {
    ShowHeader("�������� ���������� � �������");

    clinic_.ErasePatients();
    ShowMessage("������� ������� �������");
}

void ClinicGui::AddNewDoctor() {
    auto doctor = Doctor::EnterDoctor();

    auto result = clinic_.AddDoctor(doctor);

    ShowMessage(result ? "������ �������� �������" : "������: ������ ��� ����������");
}

void ClinicGui::EraseDoctor() {
    ShowHeader("�������� �������� � �����");

    auto name = EnterDoctorName();
    auto result = clinic_.EraseDoctor(name);

    ShowMessage(result ? "������ ������ �������" : "������: ������ �� ������");
}

void ClinicGui::ShowDoctors() {
    ShowHeader("�������� ���� ������");

    auto doctors = clinic_.GetDoctors();

    if (doctors.empty()) {
        cout << "�������� �� �������";
    }

    for (int i = 0; i < doctors.size(); ++i) {
        if (!doctors[i].expired())
            cout << i + 1 << ". " << "���: " << doctors[i].lock()->GetName()
            << " ����������: " << doctors[i].lock()->GetSchedule()
            << '\n';
    }
}

void ClinicGui::EraseDoctors() {
    ShowHeader("������� ������ � ������");
    clinic_.EraseDoctors();
    ShowMessage("������ ������� �������");
}

void ClinicGui::ShowMessage(std::string_view message) {
    cout << '\n' << message;
}

void ClinicGui::ShowHeader(std::string_view header) {
    cout << header << "\n\n";
}
