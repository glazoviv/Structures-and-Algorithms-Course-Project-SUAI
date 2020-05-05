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
 * \brief	Проверяет регистрационный номер согласно формату.
 * \param	number	Регистрационный номер
 *
 * \return	Истину, если номер валиден.
 */
bool IsValidRegistrationNumber(std::string_view number);
/**
 * \brief	Ввод из консоли регистрационного номера.
 */
std::string EnterRegisterNumber();

/**
 * \brief	Структура для расчета хэша по номеру регистрации.
 */
struct RegisterNumberHash {
	size_t operator() (std::string_view number) const;
};

