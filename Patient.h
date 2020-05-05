/*****************************************************************//**
 * \file   Patient.h
 * \brief  �������� ����������� ������ ��������������� �������� 
 *		   �������
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <string>
#include <memory>

class Patient;

/**
 * \brief	����� �������������� �������� �������.
 */
class Patient {
public:
	/**
	 * \brief	����������� �� ���������.
	 */
	Patient() = default;
	/**
	 * \brief	����������� �������� �� ������� � ����������.
	 *			�������� �������� �������������.
	 * \return	��������� �� ������ ��������
	 */
	static std::shared_ptr<Patient> EnterPatient();
	/**
	 * \brief	�������� ��������������� ����� ��������.
	 * \return	��������������� �����
	 */
	std::string_view GetRegistrationNumber() const;
	/**
	 * \brief	�������� ��� ��������.
	 * \return	���
	 */
	std::string_view GetName() const;
	/**
	 * \brief	�������� ��� �������� ��������.
	 * \return	��� �������� �������� � ���������� 1900-2020 ������������.
	 */
	unsigned int GetYear() const;
	/**
	 * \brief	�������� ����� ���������� ��������.
	 * \return	����� ����������.
	 */
	std::string_view GetAddress() const;
	/**
	 * \brief	�������� ����� ������ ��������.
	 * \return	����� ������.
	 */
	std::string_view GetWork() const;
private:
	/**
	 * \brief	��������� ��������������� ����� �������� �������.
	 * \param	number	��������������� �����
	 * 
	 * \return	������, ���� ����� �������.
	 */
	static bool IsValidRegistrationNumber(std::string_view number);

private:
	/** ��������������� ����� - ������ "MM-NNNNNN". MM - ����� �������, NNNNNN - ���������� ����� */
	std::string registration_number_;
	/** ��� - �� ����� 50 �������� */
	std::string name_;
	/**  ��� �������� */
	unsigned int year_ = 1900;
	/** �����, �� ����� 50 �������� */
	std::string address_;
	/** ����� ������, �����, �� ����� 50 �������� */
	std::string work_;
};

/**
 * \brief	��������� ��� ������� ���� �� ������ �����������.
 */
struct RegisterNumberHash {
	size_t operator() (std::string_view number) const {
		int iX = 2'123'417;

		auto first = std::stoi(number.substr(0, 2).data());
		auto second = std::stoi(number.substr(3).data());

		return second * iX + first;
	}
};

