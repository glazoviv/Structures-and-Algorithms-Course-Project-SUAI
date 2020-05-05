/*****************************************************************//**
 * \file   AvlTree.h
 * \brief  ���������� � ���������� ���������� ������ ��� ������.
 * 
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <memory>

/**
 * \brief   ��������� ����� �������������� ��� (����������������) ������.
 *          K - ��� �����,
 *          T - ��� �������� ���������������� �����,
 *          Less - ����������, ������� ������������ ��� ��������� ��������� ������.
 */
template <typename K, typename T, typename Less = std::less<K>>
class AvlTree {
public:
    /** ���� ������ */
    struct Node {
        /**
         * \brief   ����������� � ��������� ��������.
         * 
         * \param   key     ����.
         * \param   value   ��������.
         */
        Node(K key, T value) {
            this->key = key;
            this->value = value;
        }

        /** ���� */
        K key;
        /** �������� */
        T value;
        /** ������ ��������� � ������ � ������ ���� */
        size_t height = 1;
        /**  ������ ��������� */
        std::shared_ptr<Node> right;
        /**  ����� ��������� */
        std::shared_ptr<Node> left;
    };
    /**
     * \brief   ������� ��������.
     * 
     * \param   key ��������.
     */
    void Insert(K key, T value) {
        root_ = InsertInternal(root_, key, value);
    }
    /**
     * \brief   �������� ���� �� �����.
     * 
     * \param   key ����.
     */
    void Erase(const K& key) {
        root_ = EraseInternal(root_, key);
    }
    /**
     * \brief   ������� ������.
     * 
     */
    void Clear() {
        root_ = nullptr;
    }

    /**
     * \brief       ��������� �������� �� �����.
     * 
     * \param       key ����.
     * \return      ������ �� ��������.
     * \attention   ������������ ������ ��� ������������ ���������.
     */
    const T& GetValue(const K& key) const {
        return FindInternal(root_, key)->value;
    }
    /**
     * \brief       ��������� �������� �� �����.
     *
     * \param       key ����.
     * \return      ������ �� ��������.
     * \attention   ������������ ������ ��� ������������ ���������.
     */
    T& GetValue(const K& key) {
        return FindInternal(root_, key)->value;
    }
    /**
     * \brief   �������� ������������� �������� �� �����.
     * 
     * \param   key ����.
     * \return  ������, ���� �������� ����������.
     */
    bool Contains(const K& key) const {
        return FindInternal(root_, key) != nullptr;
    }
    /**
     * \brief   ������������ ����� ������ � ����������� �� ������ ���� �������.
     * 
     * \param   func    ������� ����������� ����.
     * \see Node
     */
    template <typename Func>
    void SymmetricForEach(Func func) {
        SymmetricForEachInternal(root_, func);
    }

private:
    /**
     * \brief   ������� �������� � ���������.
     * 
     * \param   node    ���������.
     * \param   key     ����.
     * \return  ����� �������� ����.
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
     * \brief   �������� ������ ���������.
     *          ��������������� ������� ��� ����, ����� �� ��������� �������� �� ������������� ����.
     * 
     * \param   node    ����.
     * \return  ���� ���� ���������� ������, ����� 0.
     */
    size_t GetHeight(std::shared_ptr<Node> node) const {
        return node ? node->height : 0;
    }
    /**
     * \brief   �������� ����������� ������������������ ����.
     * 
     * \param   node    ����.
     * \return  ����������� ������������������ ����
     */
    int GetBalanceRatio(std::shared_ptr<Node> node) const {
        return GetHeight(node->right) - GetHeight(node->left);
    }
    /**
     * \brief   ���������� ������ ���������.
     * 
     * \param   node    �������� ���� ���������.
     */
    void ReCalcHeight(std::shared_ptr<Node> node) {
        size_t hleft = GetHeight(node->left);
        size_t hright = GetHeight(node->right);

        node->height = (hleft > hright ? hleft : hright) + 1;
    }
    /**
     * \brief   ������ ��������.
     *
     * \param   node    ��������� ����.
     * \return  ����� ������ ����.
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
     * \brief   ����� ��������.
     * 
     * \param   node    ��������� ����.
     * \return  ����� ������ ����.
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
     * \brief   ������������ ����.
     * 
     * \param   node    ������������� ����.
     * \return  ����� �������� ����.
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
     * \brief   ����� ���� � ����������� ���������.
     * 
     * \param   node    ����, � ��������� �������� ������������ �����.
     * \return  ���� � ����������� ��������� � ���������.
     */
    std::shared_ptr<Node> SearchMin(std::shared_ptr<Node> node) const {
        if (node->left) {
            return SearchMin(node->left);
        }

        return node;
    }
    /**
     * \brief   �������� ������������ ���� �� ���������.
     * 
     * \param   node    �������� ���� ���������.
     * \return  ����� �������� ����.
     */
    std::shared_ptr<Node> DeleteMin(std::shared_ptr<Node> node){
        if (!node->left) {
            return node->right;
        }

        node->left = DeleteMin(node->left);

        return Balance(node);
    }
    /**
     * \brief   �������� �������� �� ��������� ����.
     * 
     * \param   node    ����.
     * \param   key     ����.
     * \return  ����� ������ ���������.
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
     * \brief   ����� � ��������� ���� �� �����.
     * 
     * \param   node    �������� ���� ���������.
     * \param   key     ����.
     * \return  ��������� �� ����, ���� ����������.
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
     * \brief   ������������ ����� ���� � ����������� �������.
     * 
     * \param   node    �������� ����.
     * \param   func    �������, ����������� � ������� ����.
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
    /** �������� ���� */
    std::shared_ptr<Node> root_;
};


