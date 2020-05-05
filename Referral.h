#pragma once

#include <string>

/**
 * \brief   ���������� � �����.
 */
struct Referral {
    /** ��������������� ����� �������� */
    std::string register_number;
    /** ��� ����� */
    std::string doctor_name;
    /** ���� �����������. 1-20 �������� */
    std::string date;
    /** ����� �����������. 1-20 �������� */
    std::string time;
};