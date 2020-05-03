/*****************************************************************//**
 * \file   Doctor.h
 * \brief  �������� ����������� ������ ��������������� �������
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
     * \brief	����������� �� ���������.
     */
    Doctor() = default;
    /**
     * \brief	����������� ������� �� ������� � ����������.
     *			�������� �������� �������������.
     * \return	��������� �� ������ �������
     */
    static std::shared_ptr<Doctor> EnterDoctor();
    /**
     * \brief	�������� ��� �������.
     * \return	���
     */
    std::string_view GetName();
    /**
     * \brief	�������� ���������.
     * \return	���������
     */
    std::string_view GetPosition();
    /**
     * \brief	�������� ����� ��������.
     * \return	����� ��������.
     */
    unsigned int GetCabinetNumber();
    /**
     * \brief	�������� ����������� ������.
     * \return	����������
     */
    std::string_view GetSchedule();

private:
    /** ���, �� ����� 25 �������� */
    std::string name_;
    /** ���������, �� ����� 25 �������� */
    std::string position_;
    /** ����� �������� */
    unsigned long cabinet_number_ = 0;
    /** ������ ������, �� ����� 50 �������� */
    std::string schedule_;
};

