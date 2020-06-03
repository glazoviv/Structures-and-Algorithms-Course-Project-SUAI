/*****************************************************************//**
 * \file   Patient.cpp
 * \brief  Содержит реализацию класса представляющего пациента 
 *		   клиники
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

	cout << "Ввод данных о пациенте\n\n";

	patient->registration_number_ = EnterRegisterNumber();

	patient->year_ = GetULongValue(	"Введите год рождения:",
										"Ошибка: год должен быть в промежутке 1900-2020",
										[](unsigned long year) -> bool {
											return year >= 1900 && year <= 2020;
										});


	//Ограничение на длину строковых данных пациента
	auto check_length = [](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 50;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	};

	patient->name_ = EnterPatientName();

	patient->address_ = EnterStringValue("Введите адрес пациента:",
		"Ошибка: адрес должен быть не менее 1 и не более 50 символов",
		check_length);
	patient->work_ = EnterStringValue("Введите место работы пациента:",
		"Ошибка: место должно быть не менее 1 и не более 50 символов",
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
	static const regex regex("(\\d{2})-(\\d{6})");
	return regex_match(number.data(), regex);
}

std::string EnterRegisterNumber() {
	return EnterStringValue("Введите регистрационный номер:",
		"Ошибка: Регистрационный номер должен быть формата MM-NNNNNN",
		IsValidRegistrationNumber);
}

std::string EnterPatientName() {
	return EnterStringValue("Введите ФИО пациента:",
		"Ошибка: имя должно быть не менее 1 и не более 50 символов",
		[](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 50;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	});
}

size_t RegisterNumberHash::operator() (std::string_view number) const {
	int iX = 2'123'417;

	auto first = std::stoi(number.substr(0, 2).data());
	auto second = std::stoi(number.substr(3).data());

	return second * iX + first;
}