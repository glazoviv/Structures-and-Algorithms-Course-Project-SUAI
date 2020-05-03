/*****************************************************************//**
 * \file   Doctor.h
 * \brief  Содержит определения класса представляющего доктора
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <string>
#include <memory>

class Doctor {
public:
    /**
     * \brief	Конструктор по умолчанию.
     */
    Doctor() = default;
    /**
     * \brief	Конструктор доктора из консоли с проверками.
     *			Является основным конструктором.
     * \return	Указатель на объект доктора
     */
    static std::shared_ptr<Doctor> EnterDoctor();
    /**
     * \brief	Получить имя доктора.
     * \return	Имя
     */
    std::string_view GetName();
    /**
     * \brief	Получить должность.
     * \return	Должность
     */
    std::string_view GetPosition();
    /**
     * \brief	Получить номер кабинета.
     * \return	Номер кабинета.
     */
    unsigned int GetCabinetNumber();
    /**
     * \brief	Получить расаписание работы.
     * \return	расписание
     */
    std::string_view GetSchedule();

private:
    /** ФИО, не более 25 символов */
    std::string name_;
    /** Должность, не более 25 символов */
    std::string position_;
    /** Номер кабинета */
    unsigned long cabinet_number_ = 0;
    /** График приема, не более 50 символов */
    std::string schedule_;
};

