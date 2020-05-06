/*****************************************************************//**
 * \file   Gui.h
 * \brief  Содержит определение класса для управления поликлиникой
 *		   через графический интерфейс.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include "ClinicManager.h"

/**
 * \brief	Класс позволяющий выполнять операции поликлиникой через интерфейс.
 */
class ClinicGui {
public:
	/**
	 * \brief	Выполняет взаимодействие с пользователем.
	 * 
	 */
	void Handle();
private:
	/** Пункты меню, соответствующие требуемым операциям */

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
	 * \brief   Отображает в консоль меню с новой строки.
	 */
	static void ShowMenu();
	/**
	 * \brief	Отображает в консоль сообщение.
	 * 
	 * \param	message	Сообщение.
	 */
	static void ShowMessage(std::string_view message);
	/**
	 * \brief	Отображает заголовок в консоль.
	 *
	 * \param	message	Текст заголовка.
	 */
	static void ShowHeader(std::string_view header);

private:
	/** Объект поликлиники, которым управляет Gui */
	ClinicManager clinic_;
};