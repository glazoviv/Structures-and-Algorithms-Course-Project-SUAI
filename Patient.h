/*****************************************************************//**
 * \file   Patient.h
 * \brief  Содержит определения класса представляющего пациента 
 *		   клиники
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <string>
#include <memory>

class Patient;

/**
 * \brief	Класс представляющий пациента клиники.
 */
class Patient {
public:
	/**
	 * \brief	Конструктор по умолчанию.
	 */
	Patient() = default;
	/**
	 * \brief	Конструктор пациента из консоли с проверками.
	 *			Является основным конструктором.
	 * \return	Указатель на объект пациента
	 */
	static std::shared_ptr<Patient> EnterPatient();
	/**
	 * \brief	Получить регистрационный номер пациента.
	 * \return	Регистрационный номер
	 */
	std::string_view GetRegistrationNumber() const;
	/**
	 * \brief	Получить имя пациента.
	 * \return	Имя
	 */
	std::string_view GetName() const;
	/**
	 * \brief	Получить год рождения пациента.
	 * \return	Год рождения пациента в промежутке 1900-2020 включительно.
	 */
	unsigned int GetYear() const;
	/**
	 * \brief	Получить адрес проживания пациента.
	 * \return	Адрес проживания.
	 */
	std::string_view GetAddress() const;
	/**
	 * \brief	Получить место работы пациента.
	 * \return	Место работы.
	 */
	std::string_view GetWork() const;
private:
	/**
	 * \brief	Проверяет регистрационный номер согласно формату.
	 * \param	number	Регистрационный номер
	 * 
	 * \return	Истину, если номер валиден.
	 */
	static bool IsValidRegistrationNumber(std::string_view number);

private:
	/** Регистрационный номер - формат "MM-NNNNNN". MM - номер участка, NNNNNN - порядковый номер */
	std::string registration_number_;
	/** ФИО - не более 50 символов */
	std::string name_;
	/**  Год рождения */
	unsigned int year_ = 1900;
	/** Адрес, не более 50 символов */
	std::string address_;
	/** Место работы, учебы, не более 50 символов */
	std::string work_;
};

/**
 * \brief	Структура для расчета хэша по номеру регистрации.
 */
struct RegisterNumberHash {
	size_t operator() (std::string_view number) const {
		int iX = 2'123'417;

		auto first = std::stoi(number.substr(0, 2).data());
		auto second = std::stoi(number.substr(3).data());

		return second * iX + first;
	}
};

