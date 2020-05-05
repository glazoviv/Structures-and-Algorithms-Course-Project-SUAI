#pragma once

#include <string>

/**
 * \brief   Нправление к врачу.
 */
struct Referral {
    /** Регистрационный номер пациента */
    std::string register_number;
    /** ФИО врача */
    std::string doctor_name;
    /** Дата направления. 1-20 символов */
    std::string date;
    /** Время направления. 1-20 символов */
    std::string time;
};