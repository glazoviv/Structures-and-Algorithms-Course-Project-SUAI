/*****************************************************************//**
 * \file   HashTable.h
 * \brief  ���������� � ���������� ���������� ������ ��� �������
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <vector>
#include <functional>
#include <optional>
/**
 * \brief   ��������� ����� �������� ��� ������� � �������� ������������
 */
template<typename Key, typename T, typename Hash >
class HashTable {
public:
    /**
     * \brief   ����������� �� ���������.
     */
	HashTable() {
        storage_.resize(capacity_);
    }
    /**
     * \brief   ������� � ������. ���� ������� ����������, ����� ����� ��������������� ����� ��������.
     * 
     * \param   key     ����
     * \param   value   ��������
     */
    void Insert(const Key& key, T value) {
        if (busy_count_ / capacity_  >= 0.8) {
            this->Resize();
        }


        size_t bucket = GetBucket(key);
        
        if(!storage_[bucket].has_value()) {
            storage_[bucket] = { key, std::move(value) };
            ++busy_count_;
        } else {
            storage_[bucket]->value = std::move(value);
        }
    }
    /**
     * \brief   �������� ������� �� �����.
     *          ������������ ������ ��� ������������ ���������.         
     * 
     * \param   key ����
     * \return  ������ �� ������� �� �����
     */
    const T& Get(const Key& key) {
        return storage_[GetBucket(key)]->value;
    }

    /**
     * \brief   �������� �� ������������� �������� �� �����.
     * 
     * \param   key ����
     * \return  ������, ���� �������� ����������.
     */
    bool Contains(const Key& key) const {
        size_t bucket = GetBucket(key);
        return storage_.at(bucket).has_value() && storage_.at(bucket)->key == key;
    }
    /**
     * \brief   �������� �������� �� �����.
     * 
     * \param   key ����
     * \return  ������, ���� ������� ��� ������.
     */
    bool Erase(const Key& key) {
        bool result = false;

        if(Contains(key)) {
            size_t bucket = GetBucket(key);
            storage_[bucket].reset();

            result = true;

            --busy_count_;
        }

        return result;
    }
    /**
     * \brief   ������� �������.
     *          ����������������� ������ �� ����������.
     */
    void Clear() {
        storage_.clear();
        storage_.resize(capacity_);
    }
    /**
     * \brief   ������ ������ �� ��� �������� �������.
     * 
     * \return ������ ������ �������� �������.
     */
    std::vector<const T&> GetRefValues() const {
        std::vector<const T&> result;
        result.reserve(busy_count_);

        for (const auto& cell : storage_)
        {
            if(cell) {
                result.push_back(cell->value);
            }
        }

        return result;
    }
    /**
     * \brief   ������ ���� �������� �������.
     *
     * \return ������ �������� �������.
     */
    std::vector<T> GetValues() const {
        std::vector<T> result;
        result.reserve(busy_count_);

        for (const auto& cell : storage_)
        {
            if (cell) {
                result.push_back(cell->value);
            }
        }

        return result;
    }

private:
    /**
     * \brief   �������� ����� ������� ��������������� �����.
     * 
     * \param   key ����
     * \return  ����� �������.
     */
    size_t GetBucket(const Key& key) const {
        static Hash hash_function;

        size_t bucket = hash_function(key) % capacity_;

        while (storage_[bucket].has_value() && storage_[bucket]->key != key) {
            bucket = (bucket + step_) % capacity_;
        }

        return bucket;
    }
    /**
     * \brief   ���������� ������� ������� � 2 ���� � ������������ ������ ��������.
     */
    void Resize() {
        auto old_storage = std::move(storage_);

        capacity_ *= 2;
        busy_count_ = 0;

        storage_.resize(capacity_);

        for(auto& cell : old_storage) {
            if(cell) {
                this->Insert(std::move(cell->key), std::move(cell->value));
            }
        }
    }

private:
    /**
     * \brief   ������ �������.
     */
    struct Cell {
        /** ���� */
        Key key;
        /** �������� */
        T value;
    };
    /** ��������� ������ */
    std::vector<std::optional<Cell>> storage_;
    /** ��� �������� */
    const uint8_t step_ = 1;
    /** ������� ������� */
	size_t capacity_  = 2;
    /** ���������� ������� ����� */
    size_t busy_count_ = 0;
};