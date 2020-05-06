/*****************************************************************//**
 * \file   Gui.h
 * \brief  �������� ����������� ������ ��� ���������� ������������
 *		   ����� ����������� ���������.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include "ClinicManager.h"

/**
 * \brief	����� ����������� ��������� �������� ������������ ����� ���������.
 */
class ClinicGui {
public:
	/**
	 * \brief	��������� �������������� � �������������.
	 * 
	 */
	void Handle();
private:
	/** ������ ����, ��������������� ��������� ��������� */

	void RegistrationNewPatient();
	void ErasePatient();
	void ShowPatients();
	void ErasePatients();

	void FindPatient();
	void FindPatientByNumber();
	void FindPatientsByName();


	void AddNewDoctor();
	void EraseDoctor();
	void ShowDoctors();
	void EraseDoctors();

	void FindDoctor();
	void FindDoctorByName();
	void FindDoctorsByPosition();


	void RegisterReferral();
	void RefundRefferal();

	/**
	 * \brief   ���������� � ������� ���� � ����� ������.
	 */
	static void ShowMenu();
	/**
	 * \brief	���������� � ������� ���������.
	 * 
	 * \param	message	���������.
	 */
	static void ShowMessage(std::string_view message);
	/**
	 * \brief	���������� ��������� � �������.
	 *
	 * \param	message	����� ���������.
	 */
	static void ShowHeader(std::string_view header);

private:
	/** ������ �����������, ������� ��������� Gui */
	ClinicManager clinic_;
};