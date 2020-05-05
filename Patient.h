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
 * \brief	��������� ��������������� ����� �������� �������.
 * \param	number	��������������� �����
 *
 * \return	������, ���� ����� �������.
 */
bool IsValidRegistrationNumber(std::string_view number);
/**
 * \brief	���� �� ������� ���������������� ������.
 */
std::string EnterRegisterNumber();

/**
 * \brief	��������� ��� ������� ���� �� ������ �����������.
 */
struct RegisterNumberHash {
	size_t operator() (std::string_view number) const;
};

