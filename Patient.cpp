/*****************************************************************//**
 * \file   Patient.cpp
 * \brief  �������� ���������� ������ ��������������� �������� 
 *		   �������
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include "Patient.h"

#include "Accessory.h"

#include <iostream>
#include <regex>

using namespace std;

shared_ptr<Patient> Patient::EnterPatient() {
	auto patient = make_shared<Patient>();

	cout << "���� ������ � ��������\n\n";

	patient->registration_number_ = EnterRegisterNumber();

	patient->year_ = GetULongValue(	"������� ��� ��������:",
										"������: ��� ������ ���� � ���������� 1900-2020",
										[](unsigned long year) -> bool {
											return year >= 1900 && year <= 2020;
										});


	//����������� �� ����� ��������� ������ ��������
	auto check_length = [](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 50;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	};

	patient->name_ = EnterStringValue(	"������� ��� ��������:",
									"������: ��� ������ ���� �� ����� 1 � �� ����� 50 ��������",
									check_length);
	patient->address_ = EnterStringValue("������� ����� ��������:",
		"������: ����� ������ ���� �� ����� 1 � �� ����� 50 ��������",
		check_length);
	patient->work_ = EnterStringValue("������� ����� ������ ��������:",
		"������: ����� ������ ���� �� ����� 1 � �� ����� 50 ��������",
		check_length);

	return patient;
}

std::string_view Patient::GetRegistrationNumber() const {
	return registration_number_;
}

std::string_view Patient::GetName() const {
	return name_;
}

unsigned int Patient::GetYear() const {
	return year_;
}

std::string_view Patient::GetAddress() const {
	return address_;
}

std::string_view Patient::GetWork() const {
	return work_;
}

bool IsValidRegistrationNumber(string_view number) {
	const regex regex("(\\d{2})-(\\d{6})");
	return regex_match(number.data(), regex);
}

std::string EnterRegisterNumber() {
	return EnterStringValue("������� ��������������� �����:",
		"������: ��������������� ����� ������ ���� ������� MM-NNNNNN",
		IsValidRegistrationNumber);
}

size_t RegisterNumberHash::operator() (std::string_view number) const {
	int iX = 2'123'417;

	auto first = std::stoi(number.substr(0, 2).data());
	auto second = std::stoi(number.substr(3).data());

	return second * iX + first;
}

