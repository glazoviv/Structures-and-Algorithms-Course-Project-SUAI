#pragma once

#include "Patient.h"
#include "Doctor.h"

#include "HashTable.h"
#include "AvlTree.h"


class ClinicManager {
public:
	/**
	 * \brief	Регистрация нового больного.
	 * 
	 * \param	patient	Указатель на пациента.
	 * \return	В случае успеха - истина.
	 */
	bool AddPatient(std::shared_ptr<Patient> patient);
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


	/**
	 * \brief	Добавление нового врача.
	 * 
	 * \param	doctor	Указатель на врача.
	 * \return	В случае добавления - истина.
	 */
	bool AddDoctor(std::shared_ptr<Doctor> doctor);
	/**
	 * \brief	Удаление сведений о враче.
	 * 
	 * \param	name	ФИО врача.
	 * \return	В случае удаления - истина.
	 */
	bool EraseDoctor(std::string_view name);
	//Просмотр всех врачей
	std::vector<std::shared_ptr<Doctor>> GetDoctors();
	/**
	 * \brief	Очистка всех врачей.
	 * 
	 */
	void EraseDoctors();

	//Поиск врача по ФИО. 
	//Результат - все сведения о враче + ФИО и рег № больных, у которых направление к врачу
	//GetDoctorByName(std::string_view name) const;

	//Поиск врача по должности. Может производится поиск по части должности
	// Список врачей с ФИО, должности, № кабинета и графика приема.
	std::vector<std::shared_ptr<Doctor>> GetDoctorsByPosition(std::string_view position) const;


	//Регистрация выдачи больному направления к врачу

	//Возврат направления к врачу

private:
	/** Больных храним в хэш таблице. Ключ - регистрационный номер  */
	HashTable<std::string_view, std::shared_ptr<Patient>, RegisterNumberHash> number_patient_;
	/** Для быстрого поиска по ФИО используем мульти хэш таблицу. Ключ - ФИО */
	std::unordered_multimap<std::string_view, std::shared_ptr<Patient>> name_patients_;

	/** В сортированном по ФИО дереве храним врачей. Сортируем по ФИО врача */
	AvlTree<std::string_view, std::shared_ptr<Doctor>> name_doctor_;
};


