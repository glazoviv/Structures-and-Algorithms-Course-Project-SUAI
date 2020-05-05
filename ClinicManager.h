#pragma once

#include "Patient.h"
#include "Doctor.h"

#include "HashTable.h"
#include "AvlTree.h"


class ClinicManager {
public:
	/**
	 * \brief	����������� ������ ��������.
	 * 
	 * \param	patient	��������� �� ��������.
	 * \return	� ������ ������ - ������.
	 */
	bool AddPatient(std::shared_ptr<Patient> patient);
	/**
	 * \brief	�������� ���������� � �������.
	 * 
	 * \param	register_number	��������������� �����.
	 * \return	� ������ ������ - ������.
	 */
	bool RemovePatient(std::string_view register_number);
	/**
	 * \brief	�������� ���� �������.
	 * 
	 * \return ������ ������������ �� �������.
	 */
	std::vector<std::shared_ptr<Patient>> GetPatients() const;

	//������ �������� �� ���. ������.
	//��������� - ��� �������� � ������� � ��� ����� � �������� � ���� �����������
	//std::pair<const std::string&, const Patient&>> GetPatientInfo();
	/**
	 * \brief	����� �������� �� ���.
	 * 
	 * \param	name	���.
	 * \return	������ ���������� �� �������.
	 */
	std::vector<std::shared_ptr<Patient>> GetPatientsByName(std::string_view name) const;


	/**
	 * \brief	���������� ������ �����.
	 * 
	 * \param	doctor	��������� �� �����.
	 * \return	� ������ ���������� - ������.
	 */
	bool AddDoctor(std::shared_ptr<Doctor> doctor);
	/**
	 * \brief	�������� �������� � �����.
	 * 
	 * \param	name	��� �����.
	 * \return	� ������ �������� - ������.
	 */
	bool EraseDoctor(std::string_view name);
	//�������� ���� ������
	std::vector<std::shared_ptr<Doctor>> GetDoctors();
	/**
	 * \brief	������� ���� ������.
	 * 
	 */
	void EraseDoctors();

	//����� ����� �� ���. 
	//��������� - ��� �������� � ����� + ��� � ��� � �������, � ������� ����������� � �����
	//GetDoctorByName(std::string_view name) const;

	//����� ����� �� ���������. ����� ������������ ����� �� ����� ���������
	// ������ ������ � ���, ���������, � �������� � ������� ������.
	std::vector<std::shared_ptr<Doctor>> GetDoctorsByPosition(std::string_view position) const;


	//����������� ������ �������� ����������� � �����

	//������� ����������� � �����

private:
	/** ������� ������ � ��� �������. ���� - ��������������� �����  */
	HashTable<std::string_view, std::shared_ptr<Patient>, RegisterNumberHash> number_patient_;
	/** ��� �������� ������ �� ��� ���������� ������ ��� �������. ���� - ��� */
	std::unordered_multimap<std::string_view, std::shared_ptr<Patient>> name_patients_;

	/** � ������������� �� ��� ������ ������ ������. ��������� �� ��� ����� */
	AvlTree<std::string_view, std::shared_ptr<Doctor>> name_doctor_;
};


