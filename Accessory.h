/*****************************************************************//**
 * \file   Accessory.h
 * \brief  Содержит определения дополнительных функций
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <string>
#include <functional>

/**
 * \brief   Очищает консоль
 */
void ClearConsole();
/**
 * \brief   Вывод в консоль надпись "Для продолжения нажмите любую клавишу..." и ожидает любой ввод
 */
void PressToContinue();
/**
 * \brief   Получает из консоли unsigned long
 * 
 * \return  беззнаковое целое
 */
unsigned long GetULongValue();
/**
 * \brief   Получает из консоли unsigned long
 * 
 * \param   enter_message     Текст, который будет показан перед вводом
 * \param   error_message     Текст, который будет показан при получении ошибки
 * \param   check             Функция проверки введенных данных
 * \return  беззнаковое целое
 */
unsigned long GetULongValue(std::string_view enter_message,
	std::string_view error_message,
	std::function<bool(unsigned long)> check);
/**
 * \brief   Получает из консоли строку.
 *          Чтение до переноса или конца строки.
 * \return  строку
 */
std::string EnterStringValue();
/**
 * \brief   Получает из консоли строку
 * 
 * \param   enter_message     Текст, который будет показан перед вводом
 * \param   error_message     Текст, который будет показан при получении ошибки
 * \param   check             Функция проверки введенных данных
 * \return  строку
 */
std::string EnterStringValue(std::string_view enter_message, 
	std::string_view error_message, 
	std::function<bool(std::string_view)> check);
/**
 * \brief   Прямой поиск в тексте.
 * 
 * \param   str         Строка, в которой производится поиск.
 * \param   substring   Искомая подстрока.
 * \param   start_pos   Позиция начала поиска.
 * 
 * /return  Номер первого символа искомой подстроки в строке. Если не найден, то -1.
 */
int FindSubstring(std::string_view str, std::string_view substring, int start_pos = 0);
/**
 * \brief   Вывести линию размеров size в косноль.
 * 
 * \param   size    Размер линии в символах.
 */
void PrintLine(size_t size);