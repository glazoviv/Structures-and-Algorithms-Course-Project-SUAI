#pragma once

#include "Patient.h"
#include "HashTable.h"


class ClinicManager {
public:
	/**
	 * \brief	����������� ������ ��������.
	 * 
	 * \param	patient	��������� �� ��������.
	 * \return	� ������ ������ - ������.
	 */
	bool AddNewPatient(std::shared_ptr<Patient> patient);
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


	//���������� ������ �����

	//�������� �������� � �����

	//�������� ���� ������

	//������� ���� ������

	//����� ����� �� ���. 
	//��������� - ��� �������� � ����� + ��� � ��� � �������, � ������� ����������� � �����

	//����� ����� �� ���������. ����� ������������ ����� �� ����� ���������
	// ������ ������ � ���, ���������, � �������� � ������� ������.

	//����������� ������ �������� ����������� � �����

	//������� ����������� � �����

private:
	/** ������� ������ � ��� �������. ���� - ��������������� �����  */
	HashTable<std::string, std::shared_ptr<Patient>, RegisterNumberHash> number_patient_;
	/** ��� �������� ������ �� ��� ���������� ������ ��� �������. ���� - ��� */
	std::unordered_multimap<std::string, std::shared_ptr<Patient>> name_patients_;

	//� ������������� ������ ������ ����������� � �����. ��������� �� ��� �����
};


