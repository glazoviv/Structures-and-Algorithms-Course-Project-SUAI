/*****************************************************************//**
 * \file   Referral.cpp
 * \brief  Содержит реализацию направляения к врачу и ввода его из
 *         консоли.
 *
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#include "Referral.h"
#include "Patient.h"
#include "Doctor.h"
#include "Accessory.h"

#include <regex>

using namespace std;

std::shared_ptr<Referral> Referral::Enter() {
	auto referral = make_shared<Referral>();

	referral->register_number = EnterRegisterNumber();
	referral->doctor_name = EnterDoctorName();

	referral->date = EnterStringValue("Введите дату посещения в формате ДД-ММ-ГГГГ:",
		"Ошибка: Дата должна быть формата ДД-ММ-ГГГГ",

		[](std::string_view date) {
			static const std::regex regex("^([0]?[1-9]|[1|2][0-9]|[3][0|1])[./-]([0]?[1-9]|[1][0-2])[./-]([0-9]{4}|[0-9]{2})$");
			return regex_match(date.data(), regex);
		}
	);

	referral->time = EnterStringValue("Введите время посещения в формате ЧЧ:ММ",
		"Ошибка: Время должно быть корректным",

		[](std::string_view date) {
		static const std::regex regex("^([0-1][0-9]|[2][0-3]):([0-5][0-9])$");
		return regex_match(date.data(), regex);
	}
	);


	return referral;
}