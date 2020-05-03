/*****************************************************************//**
 * \file   Doctor.cpp
 * \brief  �������� ���������� ������ ��������������� �������
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include "Doctor.h"
#include "Accessory.h"

#include <iostream>

using namespace std;

std::shared_ptr<Doctor> Doctor::EnterDoctor() {
	auto doctor = make_shared<Doctor>();

	cout << "���� ������ � �����\n\n";

	//����������� �� ����� ��������� ������ ��������
	auto check_length_25 = [](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 25;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	};

	doctor->name_ = EnterStringValue("������� ��� �����:",
		"������: ��� ������ ���� �� ����� 1 � �� ����� 25 ��������",
		check_length_25);

	doctor->position_ = EnterStringValue("������� ��������� �����:",
		"������: ��������� ������ ���� �� ����� 1 � �� ����� 25 ��������",
		check_length_25);

	doctor->cabinet_number_ = GetULongValue("������� ����� ��������:",
		"",
		[](unsigned long year) -> bool {
		return true;
	});

	doctor->schedule_ = EnterStringValue("������� ���������� �����:",
		"������: ���������� ������ ���� �� ����� 1 � �� ����� 50 ��������",
		[](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 50;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	});

	return doctor;
}

std::string_view Doctor::GetName() {
    return name_;
}

std::string_view Doctor::GetPosition() {
    return position_;
}

unsigned int Doctor::GetCabinetNumber() {
    return cabinet_number_;
}

std::string_view Doctor::GetSchedule() {
    return schedule_;
}
