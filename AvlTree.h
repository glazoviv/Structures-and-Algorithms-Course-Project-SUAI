/*****************************************************************//**
 * \file   AvlTree.h
 * \brief  Объявление и реализация шаблонного класса АВЛ дерева.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <memory>

/**
 * \brief   Шаблонный класс представляющий АВЛ (сбалансированное) дерево.
 *          K - тип ключа,
 *          T - тип значения соответствующему ключу,
 *          Less - компаратор, который используется для сравнения элементов дерева.
 */
template <typename K, typename T, typename Less = std::less<K>>
class AvlTree {
public:
    /** Узел дерева */
    struct Node {
        /**
         * \brief   Конструктор с указанием значения.
         * 
         * \param   key     Ключ.
         * \param   value   Значение.
         */
        Node(K key, T value) {
            this->key = key;
            this->value = value;
        }

        /** Ключ */
        K key;
        /** Значение */
        T value;
        /** Высота поддерева с корнем в данном узле */
        size_t height = 1;
        /**  Правое поддерево */
        std::shared_ptr<Node> right;
        /**  Левое поддерево */
        std::shared_ptr<Node> left;
    };
    /**
     * \brief   Вставка значения.
     * 
     * \param   key Значение.
     */
    void Insert(K key, T value) {
        root_ = InsertInternal(root_, key, value);
    }
    /**
     * \brief   Удаление узла по ключу.
     * 
     * \param   key Ключ.
     */
    void Erase(const K& key) {
        root_ = EraseInternal(root_, key);
    }
    /**
     * \brief   Очистка дерева.
     * 
     */
    void Clear() {
        root_ = nullptr;
    }

    /**
     * \brief       Получение значения по ключу.
     * 
     * \param       key Ключ.
     * \return      Ссылка на значение.
     * \attention   Использовать только для существующих элементов.
     */
    const T& GetValue(const K& key) const {
        return FindInternal(root_, key)->value;
    }
    /**
     * \brief       Получение значения по ключу.
     *
     * \param       key Ключ.
     * \return      Ссылка на значение.
     * \attention   Использовать только для существующих элементов.
     */
    T& GetValue(const K& key) {
        return FindInternal(root_, key)->value;
    }
    /**
     * \brief   Проверка существования занчения по ключу.
     * 
     * \param   key Ключ.
     * \return  Истина, если значение существует.
     */
    bool Contains(const K& key) const {
        return FindInternal(root_, key) != nullptr;
    }
    /**
     * \brief   Симметричный обход дерева с применением на каждый узел функцию.
     * 
     * \param   func    Функция принимающая узел.
     * \see Node
     */
    template <typename Func>
    void SymmetricForEach(Func func) {
        SymmetricForEachInternal(root_, func);
    }

private:
    /**
     * \brief   Вставка значения в поддерево.
     * 
     * \param   node    Поддерево.
     * \param   key     Ключ.
     * \return  Новый корневой узел.
     */
    std::shared_ptr<Node> InsertInternal(std::shared_ptr<Node> node, K key, T value) {
        if(!node) {
            return std::make_shared<Node>(key, value);
        }

        static Less less;

        if (less(key,node->key)) {
            node->left = InsertInternal(node->left, key, value);
        }
        else if(key == node->key) {
            node->value = value;
        }
        else {
            node->right = InsertInternal(node->right, key, value);
        }

        return Balance(node);
    }
    /**
     * \brief   Получить высоту поддерева.
     *          Вспомогательная функция для того, чтобы не выполнять проверки на существование узла.
     * 
     * \param   node    Узел.
     * \return  Если узел существует высоту, иначе 0.
     */
    size_t GetHeight(std::shared_ptr<Node> node) const {
        return node ? node->height : 0;
    }
    /**
     * \brief   Получить коэффициент сбалансированности узла.
     * 
     * \param   node    Узел.
     * \return  Коэффициент сбалансированности узла
     */
    int GetBalanceRatio(std::shared_ptr<Node> node) const {
        return GetHeight(node->right) - GetHeight(node->left);
    }
    /**
     * \brief   Перерасчет высоты поддерева.
     * 
     * \param   node    Корневой узел поддерева.
     */
    void ReCalcHeight(std::shared_ptr<Node> node) {
        size_t hleft = GetHeight(node->left);
        size_t hright = GetHeight(node->right);

        node->height = (hleft > hright ? hleft : hright) + 1;
    }
    /**
     * \brief   Правое вращение.
     *
     * \param   node    Вращаемый узел.
     * \return  Новый корень узла.
     */
    std::shared_ptr<Node> RightRotation(std::shared_ptr<Node> node) {
        auto left = node->left;

        node->left = left->right;

        left->right = node;

        ReCalcHeight(node);
        ReCalcHeight(left);

        return left;
    }
    /**
     * \brief   Левое вращение.
     * 
     * \param   node    Вращаемый узел.
     * \return  Новый корень узла.
     */
    std::shared_ptr<Node> LeftRotation(std::shared_ptr<Node> node) {
        auto right = node->right;

        node->right = right->left;

        right->left = node;

        ReCalcHeight(node);
        ReCalcHeight(right);

        return right;
    }
    /**
     * \brief   Балансировка узла.
     * 
     * \param   node    Балансируемый узел.
     * \return  Новый корневой узел.
     */
    std::shared_ptr<Node> Balance(std::shared_ptr<Node> node) {
        ReCalcHeight(node);

        if (GetBalanceRatio(node) == 2) {
            if (GetBalanceRatio(node->right) < 0) {
                node->right = RightRotation(node->right);
            }

            return LeftRotation(node);
        }
        if (GetBalanceRatio(node) == -2) {
            if (GetBalanceRatio(node->left) > 0) {
                node->left = LeftRotation(node->left);
            }

            return RightRotation(node);
        }

        return node;
    }
    /**
     * \brief   Поиск узла с минимальным значением.
     * 
     * \param   node    Узел, в поддереве которого производится поиск.
     * \return  Узел с минимальным значением в поддереве.
     */
    std::shared_ptr<Node> SearchMin(std::shared_ptr<Node> node) const {
        if (node->left) {
            return SearchMin(node->left);
        }

        return node;
    }
    /**
     * \brief   Удаление минимального узла из поддерева.
     * 
     * \param   node    Корневой узел поддерева.
     * \return  Новый корневой узел.
     */
    std::shared_ptr<Node> DeleteMin(std::shared_ptr<Node> node){
        if (!node->left) {
            return node->right;
        }

        node->left = DeleteMin(node->left);

        return Balance(node);
    }
    /**
     * \brief   Удаление значения из поддерева узла.
     * 
     * \param   node    Узел.
     * \param   key     Ключ.
     * \return  Новый корень поддерева.
     */
    std::shared_ptr<Node> EraseInternal(std::shared_ptr<Node> node, const K& key) {
        if (!node) {
            return nullptr;
        }

        static Less less;

        if (less(key, node->key)) {
            node->left = EraseInternal(node->left, key);
        }
        else if (key == node->key) {
            std::shared_ptr<Node> left = node->left;
            std::shared_ptr<Node> right = node->right;

            if (!right) {
                return left;
            }

            auto min = SearchMin(right);
            min->right = DeleteMin(right);
            min->left = left;

            return Balance(min);
        }
        else {
            node->right = EraseInternal(node->right, key);
        }

        return Balance(node);
    }
    /**
     * \brief   Поиск в поддереве узла по ключу.
     * 
     * \param   node    Корневой узел поддерева.
     * \param   key     Ключ.
     * \return  Указатель на узел, если существует.
     */
    std::shared_ptr<Node> FindInternal(std::shared_ptr<Node> node, const K& key) const {
        if (!node) {
            return nullptr;
        }

        static Less less;

        if (less(key, node->key)) {
            node = FindInternal(node->left, key);
        }
        else if (key == node->key) {
            return node;
        }
        else {
            node = FindInternal(node->right, key);
        }

        return node;
    }
    /**
     * \brief   Симметричный обход узла с применением функции.
     * 
     * \param   node    Корневой узел.
     * \param   func    Функция, применяемая к каждому узлу.
     */
    template <typename Func>
    void SymmetricForEachInternal(std::shared_ptr<Node> node, Func func) {
        if (!node) {
            return;
        }

        SymmetricForEachInternal(node->left, func);
        func(*node);
        SymmetricForEachInternal(node->right, func);
    }

private:
    /** Корневой узел */
    std::shared_ptr<Node> root_;
};