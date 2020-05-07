/*****************************************************************//**
 * \file   Referral.h
 * \brief  �������� ����������� ������������ � ����� � ����� ��� ��
 *         �������.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
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
     * \brief   ���� ����������� �� ������� � ����������.
     * 
     * \return �����������.
     */
    static std::shared_ptr<Referral> Enter();
};
