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
                ShowMessage("�����\n������� �� ������������� ���������!");
                break;
            default:
                ShowMessage("������: ����������� �������");
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

void ClinicGui::FindPatient() {
    ShowHeader("����� ��������");

    auto number = GetULongValue("�� ������ ��������� ����� ������������ �����?"
        "\n1.�� ���������������� ������"
        "\n2.�� ���\n",
        "������: �������� ������ ���� 1 ��� 2",
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
    ShowHeader("����� �������� �� ���������������� ������");

    auto register_number = EnterRegisterNumber();
    auto[patient_w, doctor_name] = clinic_.GetPatient(register_number);

    if(auto patient = patient_w.lock()) {
        cout << "���: " << patient->GetName() << '\n'
             << "��������������� �����: " << patient->GetRegistrationNumber() << '\n'
             << "��� ��������: " << patient->GetYear() << '\n'
             << "�����: " << patient->GetAddress() << '\n'
             << "����� ������: " << patient->GetWork() << '\n';

        if(doctor_name.empty()) {
            cout << "����������� � ����� ���";
        }
        else {
            cout << "��� ����� � �������� ���� �����������: " << doctor_name;
        }
    }
    else {
        ShowMessage("������� �� ������");
    }
}

void ClinicGui::FindPatientsByName() {
    ShowHeader("����� �������� �� ���");

    auto name = EnterPatientName();
    auto patients = clinic_.GetPatientsByName(name);

    if (patients.empty()) {
        cout << "�������� �� �������";
    }

    for (int i = 0; i < patients.size(); ++i) {
        if (!patients[i].expired())
            cout << i + 1 << ". " << "���. �����: " << patients[i].lock()->GetRegistrationNumber()
            << " ���: " << patients[i].lock()->GetName()
            << '\n';
    }

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
        ShowMessage("�������� �� �������");
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

void ClinicGui::FindDoctor() {
    ShowHeader("����� �����");

    auto number = GetULongValue("�� ������ ��������� ����� ������������ �����?"
        "\n1.�� ���"
        "\n2.�� ���������\n",
        "������: �������� ������ ���� 1 ��� 2",
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
    ShowHeader("����� ����� �� ���");

    auto name = EnterDoctorName();
    const auto&[doctor_w, patients] = clinic_.GetDoctorByName(name);

    if(auto doctor = doctor_w.lock()) {
        cout << "���: "             << doctor->GetName()            << '\n'
             << "���������: "       << doctor->GetPosition()        << '\n'
             << "����� ��������: "  << doctor->GetCabinetNumber()   << '\n'
             << "������ ������: "   << doctor->GetSchedule()        << '\n';

        if(patients.empty()) {
            cout << "��������� �� ���� ���";
        } 
        else {
            cout << "���. ������ ���������:";

            for(string_view number : patients) {
                cout << '\n' << number;
            }
        }

    } else {
        ShowMessage("������ �� ������");
    }
}

void ClinicGui::FindDoctorsByPosition() {
    ShowHeader("����� ����� �� ���������");

    auto position = EnterStringValue("������� ��������� ��� � �����:",
        {},
        [](auto str) {
        return true;
    });

    auto doctors = clinic_.GetDoctorsByPosition(position);
    
    if(doctors.empty()) {
        ShowMessage("�������� �� �������");
    }

    for (auto doctor_w : doctors) {
        if(auto doctor = doctor_w.lock()) {
            PrintLine(70);

            cout << "���: " << doctor->GetName() << '\n'
                 << "���������: " << doctor->GetPosition() << '\n'
                 << "����� ��������: " << doctor->GetCabinetNumber() << '\n'
                 << "������ ������: " << doctor->GetSchedule();
        }
    }
}

void ClinicGui::RegisterReferral() {
    ShowHeader("����������� ����������� � �����");

    auto referral = Referral::Enter();
    auto code = clinic_.RegistrationRefferal(referral);

    string message = "����������� ����������������� �������";
    
    switch(code) {
    case ClinicManager::ReferralError::DOCTOR_NOT_EXISTS:
        message = "������: ������ �� ������";
        break;
    case ClinicManager::ReferralError::PATIENT_NOT_EXISTS:
        message = "������: ������� �� ������";
        break;
    case ClinicManager::ReferralError::REFERRAL_EMPTY:
        message = "������: ����������� �� ���������";
        break;
    case ClinicManager::ReferralError::DATETIME_BUSY:
        message = "������: �� ��� ����� ��� ���������� ������";
        break;
    }

    ShowMessage(message);
}

void ClinicGui::RefundRefferal() {
    ShowHeader("����������� ����������� � �����");

    auto referral = Referral::Enter();
    auto result = clinic_.RefundRefferal(referral);

    ShowMessage(result ? "����������� ���������� �������" : "������: ����������� �� �������");
}

void ClinicGui::ShowMessage(std::string_view message) {
    cout << '\n' << message;
}

void ClinicGui::ShowHeader(std::string_view header) {
    cout << header << "\n\n";
}