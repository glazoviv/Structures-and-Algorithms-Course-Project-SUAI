#pragma once

#include "Patient.h"
#include "HashTable.h"


class ClinicManager {
public:
	/**
	 * \brief	Регистрация нового больного.
	 * 
	 * \param	patient	Указатель на пациента.
	 * \return	В случае успеха - истина.
	 */
	bool AddNewPatient(std::shared_ptr<Patient> patient);
	/**
	 * \brief	Удаление информации о больном.
	 * 
	 * \param	register_number	Регистрационный номер.
	 * \return	В случае успеха - истина.
	 */
	bool RemovePatient(std::string_view register_number);
	/**
	 * \brief	Просмотр всех больных.
	 * 
	 * \return Массив указательней на больных.
	 */
	std::vector<std::shared_ptr<Patient>> GetPatients() const;

	//Поиска больного по рег. номеру.
	//Результат - все сведения о больном и ФИО врача к которому у него направление
	//std::pair<const std::string&, const Patient&>> GetPatientInfo();
	/**
	 * \brief	Поиск больного по ФИО.
	 * 
	 * \param	name	ФИО.
	 * \return	Список указателей на больных.
	 */
	std::vector<std::shared_ptr<Patient>> GetPatientsByName(std::string_view name) const;


	//Добавление нового врача

	//Удаление сведений о враче

	//Просмотр всех врачей

	//Очистка всех врачей

	//Поиск врача по ФИО. 
	//Результат - все сведения о враче + ФИО и рег № больных, у которых направление к врачу

	//Поиск врача по должности. Может производится поиск по части должности
	// Список врачей с ФИО, должности, № кабинета и графика приема.

	//Регистрация выдачи больному направления к врачу

	//Возврат направления к врачу

private:
	/** Больных храним в хэш таблице. Ключ - регистрационный номер  */
	HashTable<std::string, std::shared_ptr<Patient>, RegisterNumberHash> number_patient_;
	/** Для быстрого поиска по ФИО используем мульти хэш таблицу. Ключ - ФИО */
	std::unordered_multimap<std::string, std::shared_ptr<Patient>> name_patients_;

	//В сортированном списке храним направления к врачу. Сортируем по ФИО врача
};


