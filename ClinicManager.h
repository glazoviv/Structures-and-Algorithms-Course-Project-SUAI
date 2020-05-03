#pragma once

#include "Patient.h"
#include "HashTable.h"


class ClinicManager {
public:
	//регистрация нового больного
	bool AddNewPatient(std::shared_ptr<Patient> patient);
	//удаление данных о больном
	bool RemovePatient(std::string_view register_number);
	//просмотр всех больных
	std::vector<const Patient&> GetPatients();

	//Поиска больного по рег. номеру.
	//Результат - все сведения о больном и ФИО врача к которому у него направление
	//std::pair<const std::string&, const Patient&>> GetPatientInfo();

	//Поиск больного по ФИО.Результат - список больных с указанием номера и ФИО.



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
};


