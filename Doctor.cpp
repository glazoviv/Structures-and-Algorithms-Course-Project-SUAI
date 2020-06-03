/*****************************************************************//**
 * \file   Doctor.cpp
 * \brief  Содержит реализацию класса представляющего доктора
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

	cout << "Ввод данных о враче\n\n";

	//Ограничение на длину строковых данных пациента
	auto check_length_25 = [](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 25;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	};

	doctor->name_ = EnterDoctorName();

	doctor->position_ = EnterStringValue("Введите должность врача:",
		"Ошибка: должность должна быть не менее 1 и не более 25 символов",
		check_length_25);

	doctor->cabinet_number_ = GetULongValue("Введите номер кабинета:",
		"",
		[](unsigned long year) -> bool {
		return true;
	});

	doctor->schedule_ = EnterStringValue("Введите расписание врача:",
		"Ошибка: расписание должно быть не менее 1 и не более 50 символов",
		[](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 50;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	});

	return doctor;
}

std::string_view Doctor::GetName() const {
    return name_;
}

std::string_view Doctor::GetPosition() const {
    return position_;
}

unsigned int Doctor::GetCabinetNumber() const {
    return cabinet_number_;
}

std::string_view Doctor::GetSchedule() const {
    return schedule_;
}

std::string EnterDoctorName() {
	return EnterStringValue("Введите ФИО врача:",
		"Ошибка: ФИО должно быть не менее 1 и не более 25 символов",
		[](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 25;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	});
}