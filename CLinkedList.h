/*****************************************************************//**
 * \file   CLinkedList.h
 * \brief  Опеределение двусвязного циклического списка.
 *
 * \author Glazov I.V.
 * \date   May 2020
 *********************************************************************/
#pragma once

#include <memory>

/**
 * \brief	Класс описывает двусвязный циклический список.
 */
template <typename T>
class СLinkedList {
public:
	/**
	 * \brief	Узел списка.
	 */
	struct Node {
		/** Значение */
		T value;
		/** Следующий элемент */
		std::shared_ptr<Node> next;
		/** Предыдущий элемент */
		std::shared_ptr<Node> prev;
	};

	/**
	 * \brief	Добавить узел в начало списка.
	 * 
	 * \param	value	Значение элемента.
	 * \return	Указатель на вставленный узел.
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
	 * \brief	Удалить узел.
	 * 
	 * \param	node	Указатель на удаляемый узел.
	 * \return	Указатель на следующий за узлом. При ошибке - nullptr
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
	 * \brief	Удалить узлы соответствующие условию.
	 *
	 * \param	predicate	Функция, возвращающая истину для подходящего элемента.	
	 */
	template<typename Func>
	void Erase(const Func& predicate) {
		if (!head_) {
			return;
		}

		auto node = head_->next;

		while(node != head_) {
			auto next = node->next;

			if(predicate(node->value)) {
				Erase(node);
			}

			node = next;
		}

		if(predicate(head_->value)) {
			Erase(head_);
		}
	}
	/**
	 * \brief	Очистка контейнера.
	 * 
	 */
	void Clear() {
		head_ = nullptr;
	}

	/**
	 * \brief	Найти узел.
	 * 
	 * \param	value	Значение, которое ищем.
	 * \return	Указатель на первый встретившийся узел с указанным значением.
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
	 * \brief	Найти узел.
	 *
	 * \param	predicate	Функция, возвращающая истину для подходящего элемента.
	 * \return	Указатель на первый встретившийся узел с указанным значением.
	 */
	template<typename Func>
	std::shared_ptr<Node> Find(const Func& predicate) {
		if (!head_) {
			return nullptr;
		}

		if (predicate(head_->value)) {
			return head_;
		}

		auto node = head_->next;
		while (node != head_) {
			if (predicate(node->value)) {
				return node;
			}

			node = node->next;
		}

		return nullptr;
	}

	/**
	 * \brief	Пройти всё с применением функции к каждому элементу.
	 * 
	 * \param	predicate	Функция, применяемая к каждому элементу.
	 */
	template<typename Func>
	void ForEach(Func predicate) {
		if (!head_) {
			return;
		}

		predicate(head_->value);

		auto node = head_->next;
		while (node != head_) {
			predicate(node->value);
			node = node->next;
		}
	}

	/**
	 * \brief	Получить корневой узел.
	 * 
	 * \return	Указатель на корневой узел.
	 */
	std::shared_ptr<Node> GetHead() const {
		return head_;
	}
	/**
	 * \brief	Получить количество элементов.
	 * 
	 * \return	Количество элементов.
	 */
	size_t GetElementCount() const {
		return count_;
	}

private:
	/**
	 * \brief	Инициализация корневого узла.
	 * 
	 * \param	value	Значение корневого узла.
	 */
	void Init(T value) {
		head_ = std::make_shared<Node>();

		head_->value = value;
		head_->next = head_;
		head_->prev = head_;
	}

private:
	/** Коренвой узел */
	std::shared_ptr<Node> head_;
	/** Количество узлов */
	size_t count_ = 0;
};

/**
 * \brief	Сортировка "Пузыьком" для двусвязного циклического списка.
 * 
 * \param	list	Сортируемый список.
 * \param	comp	Компаратор, по умолчанию - меньше.
 */
template<typename T, typename L>
void BubleSort(	СLinkedList<T>& list, const L& comp = std::less<T>()) {
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
