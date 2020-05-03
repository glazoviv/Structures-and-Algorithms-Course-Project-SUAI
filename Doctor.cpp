/*****************************************************************//**
 * \file   Doctor.cpp
 * \brief  —одержит реализацию класса представл€ющего доктора
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

	cout << "¬вод данных о враче\n\n";

	//ќграничение на длину строковых данных пациента
	auto check_length_25 = [](string_view value) -> bool {
		constexpr size_t MAX_SIZE_STR = 25;
		return !value.empty() && value.size() <= MAX_SIZE_STR;
	};

	doctor->name_ = EnterStringValue("¬ведите ‘»ќ врача:",
		"ќшибка: ‘»ќ должно быть не менее 1 и не более 25 символов",
		check_length_25);

	doctor->position_ = EnterStringValue("¬ведите должность врача:",
		"ќшибка: должность должна быть не менее 1 и не более 25 символов",
		check_length_25);

	doctor->cabinet_number_ = GetULongValue("¬ведите номер кабинета:",
		"",
		[](unsigned long year) -> bool {
		return true;
	});

	doctor->schedule_ = EnterStringValue("¬ведите расписание врача:",
		"ќшибка: расписание должно быть не менее 1 и не более 50 символов",
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
