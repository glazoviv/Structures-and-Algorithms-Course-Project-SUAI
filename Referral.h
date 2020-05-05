#pragma once

#include <string>
#include <memory>

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

    /**
     * \brief   ���� ����������� �� �������.
     * 
     * \return �����������.
     */
    static std::shared_ptr<Referral> Enter();
};
