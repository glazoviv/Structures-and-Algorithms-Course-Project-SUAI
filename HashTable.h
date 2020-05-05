/*****************************************************************//**
 * \file   HashTable.h
 * \brief  Объявление и реализация шаблонного класса хэш таблицы
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <vector>
#include <functional>
#include <optional>
/**
 * \brief   Шаблонный класс закрытой хэш таблицы с линейным опробованием
 */
template<typename Key, typename T, typename Hash >
class HashTable {
public:
    /**
     * \brief   Конструктор по умолчанию.
     */
	HashTable() {
        storage_.resize(capacity_);
    }
    /**
     * \brief   Вставка в табицу. Если элемент существует, ключу будет соответствовать новое значение.
     * 
     * \param   key     Ключ
     * \param   value   Значение
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
     * \brief   Получить элемент по ключу.
     *          Использовать только для существующих элементов.         
     * 
     * \param   key Ключ
     * \return  Ссылка на элемент по ключу
     */
    const T& Get(const Key& key) {
        return storage_[GetBucket(key)]->value;
    }

    /**
     * \brief   Проверка на существование значения по ключу.
     * 
     * \param   key Ключ
     * \return  Истина, усли значение существует.
     */
    bool Contains(const Key& key) const {
        size_t bucket = GetBucket(key);
        return storage_.at(bucket).has_value() && storage_.at(bucket)->key == key;
    }
    /**
     * \brief   Удаление элемента по ключу.
     * 
     * \param   key Ключ
     * \return  Истину, если элемент был удален.
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
     * \brief   Очистка таблицы.
     *          Зарезервированный размер не изменяется.
     */
    void Clear() {
        storage_.clear();
        storage_.resize(capacity_);
    }
    /**
     * \brief   Запрос ссылок на все значения таблицы.
     * 
     * \return Массив ссылок значений таблицы.
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
     * \brief   Запрос всех значений таблицы.
     *
     * \return Массив значений таблицы.
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
     * \brief   Получить номер корзины соответствующий ключу.
     * 
     * \param   key Ключ
     * \return  Номер корзины.
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
     * \brief   Увеличение размера таблицы в 2 раза с перемещением старых значений.
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
     * \brief   Ячейка корзины.
     */
    struct Cell {
        /** Ключ */
        Key key;
        /** Значение */
        T value;
    };
    /** Хранилище корзин */
    std::vector<std::optional<Cell>> storage_;
    /** Шаг перебора */
    const uint8_t step_ = 1;
    /** Емкость таблицы */
	size_t capacity_  = 2;
    /** Количество занятых ячеек */
    size_t busy_count_ = 0;
};