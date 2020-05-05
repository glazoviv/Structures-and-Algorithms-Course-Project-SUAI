/*****************************************************************//**
 * \file   CLinkedList.h
 * \brief  ������������ ����������� ������������ ������.
 *
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <memory>

/**
 * \brief	����� ��������� ���������� ����������� ������.
 */
template <typename T>
class �LinkedList {
public:
	/**
	 * \brief	���� ������.
	 */
	struct Node {
		/** �������� */
		T value;
		/** ��������� ������� */
		std::shared_ptr<Node> next;
		/** ���������� ������� */
		std::shared_ptr<Node> prev;
	};

	/**
	 * \brief	�������� ���� � ������ ������.
	 * 
	 * \param	value	�������� ��������.
	 * \return	��������� �� ����������� ����.
	 */
	std::shared_ptr<Node> PushFront(T value) {
		++count_;

		if (!head_) {
			Init(value);

			return head_;
		}

		auto node = std::make_shared<Node>();
		auto head_prev = head_->prev;

		node->next = head_;
		node->prev = head_prev;
		node->value = std::move(value);

		head_prev->next = node;
		head_->prev = node;

		head_ = node;

		return node;
	}
	/**
	 * \brief	������� ����.
	 * 
	 * \param	node	��������� �� ��������� ����.
	 * \return	��������� �� ��������� �� �����. ��� ������ - nullptr
	 */
	std::shared_ptr<Node> Erase(std::shared_ptr<Node> node) {
		if(!node) {
			return nullptr;
		}

		--count_;

		if(node == head_ && head_->next == node) {
			head_ = nullptr;
			return head_;
		}


		std::shared_ptr<Node> prev	= node->prev;
		std::shared_ptr<Node> next	= node->next;

		prev->next = next;
		next->prev = prev;
		
		return next;
	}
	/**
	 * \brief	����� ����.
	 * 
	 * \param	value	��������, ������� ����.
	 * \return	��������� �� ������ ������������� ���� � ��������� ���������.
	 */
	std::shared_ptr<Node> Find(const T& value) {
		if (!head_) {
			return nullptr;
		}

		if (head_->value == value) {
			return head_;
		}

		auto node = head_->next;
		while (node != head_) {
			if (node->value == value) {
				return node;
			}

			node = node->next;
		}

		return nullptr;
	}
	/**
	 * \brief	�������� �������� ����.
	 * 
	 * \return	��������� �� �������� ����.
	 */
	std::shared_ptr<Node> GetHead() const {
		return head_;
	}
	/**
	 * \brief	�������� ���������� ���������.
	 * 
	 * \return	���������� ���������.
	 */
	size_t GetElementCount() const {
		return count_;
	}

private:
	/**
	 * \brief	������������� ��������� ����.
	 * 
	 * \param	value	�������� ��������� ����.
	 */
	void Init(T value) {
		head_ = std::make_shared<Node>();

		head_->value = value;
		head_->next = head_;
		head_->prev = head_;
	}

private:
	/** �������� ���� */
	std::shared_ptr<Node> head_;
	/** ���������� ����� */
	size_t count_ = 0;
};

/**
 * \brief	���������� "��������" ��� ����������� ������������ ������.
 * 
 * \param	list	����������� ������.
 * \param	comp	����������, �� ��������� - ������.
 */
template<typename T, typename L>
void BubleSort(	�LinkedList<T>& list, const L& comp = std::less<T>()) {
	auto head = list.GetHead();

	if(!head) {
		return;
	}

	if(head == head->next) {
		return;
	}

	auto lhs = head;
	auto rhs = head->next;

	while (lhs->next != head) {
		while (rhs != head) {
			if (comp(rhs->value, lhs->value)) {
				auto temp = std::move(lhs->value);

				lhs->value = std::move(rhs->value);
				rhs->value = std::move(temp);
			}
			rhs = rhs->next;
		}
		lhs = lhs->next;
		rhs = lhs->next;
	}
}
