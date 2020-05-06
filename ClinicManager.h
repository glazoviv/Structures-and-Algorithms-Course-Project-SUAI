#pragma once

#include "Patient.h"
#include "Doctor.h"
#include "Referral.h"

#include "HashTable.h"
#include "AvlTree.h"
#include "CLinkedList.h"


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
	 * 
	 * \attention Побочный эффект - удаление направлений связанных с этим пациентом.
	 */
	bool ErasePatient(std::string_view register_number);
	/**
	 * \brief	Просмотр всех больных.
	 * 
	 * \return Массив указательней на больных.
	 */
	std::vector<std::weak_ptr<Patient>> GetPatients() const;
	/**
	 * \brief	Очистка всех пациентов.
	 *
	 * \attention Побочный эффект - удаление направлений.
	 */
	void ErasePatients();

	//Поиска больного по рег. номеру.
	//Результат - все сведения о больном и ФИО врача к которому у него направление
	std::pair<std::weak_ptr<Patient>, std::string> GetPatient(std::string_view reg_number);
	/**
	 * \brief	Поиск больного по ФИО.
	 * 
	 * \param	name	ФИО.
	 * \return	Список указателей на больных.
	 */
	std::vector<std::weak_ptr<Patient>> GetPatientsByName(std::string_view name) const;


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
	 * 
	 * \attention Побочный эффект - удаление направлений связанных с этим доктором.
	 */
	bool EraseDoctor(std::string_view name);
	/**
	 * \brief	Получить всех врачей.
	 * 
	 * \return	Массив указателей на врачей.
	 */
	std::vector<std::weak_ptr<Doctor>> GetDoctors();
	/**
	 * \brief	Очистка всех врачей.
	 * 
	 * \attention Побочный эффект - удаление направлений.
	 */
	void EraseDoctors();

	/**
	 * \brief	Поиск врача и данных пациентов по ФИО.
	 * 
	 * \param	name	ФИО врача.
	 * 
	 * \return	Врач + ФИО и рег № больных, у которых направление к врачу.
	 */
	std::pair <std::weak_ptr<Doctor>, std::vector<std::string>> GetDoctorByName(std::string_view name);

	/**
	 * \brief	Поиск врача по должностиили её части.
	 * 
	 * \param	position	Должность или её часть.
	 * \return	Список врачей.
	 */
	std::vector<std::weak_ptr<Doctor>> GetDoctorsByPosition(std::string_view position);

	/**
	 * \brief	Ошибки регистрации направления к врачу.
	 */
	enum class ReferralError {
		DOCTOR_NOT_EXISTS,
		PATIENT_NOT_EXISTS,
		REFERRAL_EMPTY,
		DATETIME_BUSY,
		OK
	};

	/**
	 * \brief	Регистрация выдачи больному направления к врачу.
	 * 
	 * \param	refferral	Заполненное направление.
	 * \return	Код ошибки регистрации направления.
	 */
	ReferralError RegistrationRefferal(std::shared_ptr<Referral> refferral);

	/**
	 * \brief	Возврат направления к врачу.
	 * 
	 * \param	refferral	Заполненное направление.
	 * \return	В случае успеха - истина.
	 */
	bool RefundRefferal(std::shared_ptr<Referral> refferral);

private:
	/** Больных храним в хэш таблице. Ключ - регистрационный номер  */
	HashTable<std::string_view, std::shared_ptr<Patient>, RegisterNumberHash> number_patient_;
	/** Для быстрого поиска по ФИО используем мульти хэш таблицу. Ключ - ФИО */
	std::unordered_multimap<std::string_view, std::shared_ptr<Patient>> name_patients_;

	/** В сортированном по ФИО дереве храним врачей. Сортируем по ФИО врача */
	AvlTree<std::string_view, std::shared_ptr<Doctor>> name_doctor_;

	/** Сортированные по ФИО врача направления */
	СLinkedList<std::shared_ptr<Referral>> referrals_;
};