#pragma once
#include <iostream>
template<typename T>
class DLList
{
private:
	struct Node {//структура записи в списке
		Node* previous = 0;//указатель на предыдущий элемент
		Node* next = 0;//указатель на следующий элемент
		T data;//значение записи
		Node(T data) {
			this->data = data;
		}
		Node(Node* previous, T data, Node* next) {
			this->data = data;
			this->next = next;
			this->previous = previous;
		}
		Node operator=(Node other) {
			this->data = other.data;
			this->next = other.next;
			this->previous = other.previous;
			return *this;
		}
	};
public:
	//проверка на пустоту
	bool is_empty() { return head == 0; }
	//получение размера списка
	int getSize() { return size; }
	//добавление в начало
	void push_begin(T data);
	//добавление в конец
	void push_end(T data);
	//оператор доступа по индексу
	T operator[](int index) {
		if (is_empty()) throw std::exception("List is empty");
		int iterator = 0;
		Node* currentNode = head;
		while (iterator != index && currentNode != NULL) {
			currentNode = currentNode->next;
			iterator++;
		}
		if (!currentNode) throw std::exception("Element with this index does not exist");
		return currentNode->data;
	};
	//получение ссылки на значение элемента списка по значению
	T& getByValue(T data) {
		Node* currentNode = head;
		while (currentNode != 0 && currentNode->data != data) {
			currentNode = currentNode->next;
		}
		if (!currentNode) throw std::exception("Element with this data does not exist");
		return currentNode->data;
	}
	//получение индекса элемента по значению
	int getIndexByValue(T data) {
		Node* currentNode = head;
		int index = 0;
		while (currentNode != 0 && currentNode->data != data) {
			currentNode = currentNode->next;
			index++;
		}
		if (!currentNode) throw std::exception("Element with this data does not exist");
		return index;
	}
	//удаление с начала
	void pop_front();
	//удаление с конца
	void pop_back();
	//удалениме элемента по значению
	void removeByValue(T value);
	//очистка списка
	void clear();
	//сортировка списка
	void sort();
	
private:
	Node* head = 0;//указатель на начало списка
	Node* end = 0;//указатель на конец списка
	int size = 0;//размер списка
};

template<typename T>
inline void DLList<T>::push_begin(T data)
{
	if (is_empty()) {//если список пустой иницилизируем первую запись
		end = head = new Node(data);
		size++;
		return;
	}
	head->previous = new Node(0,data,head);//ставим элемент перед первым
	head = head->previous;//обноляем указатель на начало списка
	size++;
}

template<typename T>
inline void DLList<T>::push_end(T data)
{
	if (is_empty()) return push_begin(data);//если список пустой то боавляем с начала
	end->next = new Node(end, data, 0);//добавляем новое значение в конец
	end = end->next;//обноволяем указатель на конец списка
	size++;
}

template<typename T>
inline void DLList<T>::pop_front()
{
	if (is_empty()) throw std::exception("List is empty");
	//если в массиве не один элемент
	if (head->next) head->next->previous = 0;//убираем связь со следующим элементом
	Node* removableNode = head;
	head = head->next;//обновляем указатель на первый элемент
	delete removableNode;//удаляем бывший первый элемент
	size--;
}

template<typename T>
inline void DLList<T>::pop_back()
{
	if (is_empty()) throw std::exception("List is empty");
	if (end == head) return pop_front();//если в списке один элемент удаляем первый
	end->previous->next = 0;//убиравем связь с предыдущим элементом
	Node* removableNode = end;
	end = end->previous;//обновляем указатель на конец списка
	delete removableNode;//удаляем бывший конец списка
	size--;
}

template<typename T>
inline void DLList<T>::removeByValue(T value)
{
	if (is_empty()) throw std::exception("List is empty");
	if (head->data == value) return pop_front();//если удаляемый элемент первый
	if (end->data == value) return pop_back();//если удаляемый элемент последний
	Node* currentNode = head;
	//ищем в списке элемент с удаляемым значением
	while (currentNode && currentNode->data != value) {
		currentNode = currentNode->next;
	}
	if (!currentNode) throw std::exception("Element not found");//если не нашли
	//убираем связь удаляемой записи с элементами списка
	currentNode->previous->next = currentNode->next;
	currentNode->next->previous = currentNode->previous;
	delete currentNode;//удаляем элемент
	size--;
}

template<typename T>
inline void DLList<T>::clear()
{
	while (size > 0) {// пока список не пуст удаляем первый элемент
		pop_front();
	}
	head = 0;
	end = 0;
}

template<typename T>
inline void DLList<T>::sort()
{
	//сортировка встаками
	Node* i_pointer = head;//заись-итератор i для движения по списку
	for (size_t i = 0; i < size; i++)
	{
		Node x = Node(i_pointer->data);//запоминаем текущий элемент
		size_t j = i;
		Node* node_j = i_pointer;//запись итератор j для движения по списку в обратном нарпавлении
		while (j > 0 && node_j->previous->data > x.data)//движемся по списку в обратном направлении 																
		{												//ищем место под вставку
			node_j->data = node_j->previous->data;//сдвигаем значение влево
			node_j = node_j->previous;//сдвигаем переменную-итератор на предыдущий элемент
			j--;
		}
		node_j->data = x.data;//вставлем текущий элемент
		i_pointer = i_pointer->next;//двишаем переменную-итератор i далее
	}
}
