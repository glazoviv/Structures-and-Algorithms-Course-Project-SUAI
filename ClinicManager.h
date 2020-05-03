#pragma once

#include "Patient.h"
#include "HashTable.h"


class ClinicManager {
public:
	//����������� ������ ��������
	bool AddNewPatient(std::shared_ptr<Patient> patient);
	//�������� ������ � �������
	bool RemovePatient(std::string_view register_number);
	//�������� ���� �������
	std::vector<const Patient&> GetPatients();

	//������ �������� �� ���. ������.
	//��������� - ��� �������� � ������� � ��� ����� � �������� � ���� �����������
	//std::pair<const std::string&, const Patient&>> GetPatientInfo();

	//����� �������� �� ���.��������� - ������ ������� � ��������� ������ � ���.



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
};


