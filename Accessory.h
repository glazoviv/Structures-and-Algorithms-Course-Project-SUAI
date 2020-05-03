/*****************************************************************//**
 * \file   Accessory.h
 * \brief  �������� ����������� �������������� �������
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <string>
#include <functional>

/**
 * \brief   ������� �������
 */
void ClearConsole();
/**
 * \brief   ����� � ������� ������� "��� ����������� ������� ����� �������..." � ������� ����� ����
 */
void PressToContinue();
/**
 * \brief   �������� �� ������� unsigned long
 * \return  ����������� �����
 */
unsigned long GetULongValue();
/**
 * \brief   �������� �� ������� unsigned long
 * \param   enter_message     �����, ������� ����� ������� ����� ������
 * \param   error_message     �����, ������� ����� ������� ��� ��������� ������
 * \param   check             ������� �������� ��������� ������
 * \return  ����������� �����
 */
unsigned long GetULongValue(std::string_view enter_message,
	std::string_view error_message,
	std::function<bool(unsigned long)> check);
/**
 * \brief   �������� �� ������� ������.
 *          ������ �� �������� ��� ����� ������.
 * \return  ������
 */
std::string EnterStringValue();
/**
 * \brief   �������� �� ������� ������
 * \param   enter_message     �����, ������� ����� ������� ����� ������
 * \param   error_message     �����, ������� ����� ������� ��� ��������� ������
 * \param   check             ������� �������� ��������� ������
 * \return  ������
 */
std::string EnterStringValue(std::string_view enter_message, 
	std::string_view error_message, 
	std::function<bool(std::string_view)> check);