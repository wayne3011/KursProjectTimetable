
#ifndef  LIST_H
#define LIST_H
#include <iostream>

template<class T>
class SLList
{
private:
	struct Node {//структура записи в списке
		Node* next = 0;//указатель на следующий элемент
		T data;//значение записи
		Node(Node* next, T data)
		{
			this->next = next;
			this->data = data;
		}
		Node(T data)
		{
			this->data = data;
		}
	};
public:
	//добавление в конец
	void push_end(T data);
	//оператор доступа по индексу
	T operator[](int index) {
		Node* currentNode = head;
		int iterator = 0;
		while (iterator != index && currentNode != 0) {
			currentNode = currentNode->next;
			iterator++;
		}
		if (!currentNode) throw std::exception("Element with this index does not exist");
		return currentNode->data;
	}
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
		int iterator = 0;
		while (currentNode != 0 && currentNode->data != data) {
			currentNode = currentNode->next;
			iterator++;
		}
		if (!currentNode) throw std::exception("Element with this data does not exist");
		return iterator;
	}
	//получение размера списка
	int getSize() { return size; }
	//проверка на пустоту
	bool is_empty();
	//удаление с начала
	void pop_front();
	//удаление с конца
	void pop_back();
	//удалениме элемента по значению
	void removeByValue(T value);
	//сортировка списка
	void sort();
	//очистка списка
	void clear();

private:
	//получение записи по индексу
	Node* getNodeAt(int index) {
		Node* currentNode = head;
		for (int i = 0; i < index && i < size; i++)
		{
			currentNode = currentNode->next;
		}
		if (!currentNode) std::exception("Element with this index does not exist");
		return currentNode;
	};
	Node* head = 0;//начало списка
	Node* end = 0;//конец списка
	int size = 0;
};
template<class T>
inline void SLList<T>::push_end(T data)
{
	Node* newNode = new Node(data);
	if (end == nullptr) {//если список пустой иницилизируем первую запись
		end = newNode; 
		head = newNode;
		size++;
		return;
	}
	end->next = newNode;//добавляем новое значение в конец
	size++;
	end = newNode;//обноволяем указатель на конец списка
}

template<class T>
inline bool SLList<T>::is_empty()
{
	return head == nullptr;
}

template<class T>
inline void SLList<T>::pop_front()
{
	if (is_empty()) throw std::exception("List is empty");
	
	Node* current = head->next;//запоминаем элемент списка следующий за первым
	delete head;//удаляем первый элемент списка
	head = current;//обновляем указатель на начало списка
	size--;
}

template<class T>
inline void SLList<T>::pop_back()
{
	if (is_empty()) throw std::exception("List is empty");
	if (head == end) return pop_front();//если в списке один элемент удаляем первый
	Node* previous = head;
	//движемся до перпоследнего элемента
	while (previous->next != end) previous = previous->next;
	delete previous->next;//удаляем последний элемент
	previous->next = 0;
	size--;
	end = previous;//обновляем указатель на конец списка
}

template<class T>
inline void SLList<T>::removeByValue(T value)
{
	if (is_empty()) throw std::exception("List is empty");
	if(value == head->data) return pop_front();//если удаляемый элемент первый
	if (value == end->data) return pop_back();//если удаляемый элемент последний
	Node* previous = head;
	//движемся до предшествующего удаляемому элементу
	while (previous->next && previous->next->data != value) previous = previous->next;
	if (!previous->next) throw std::exception("Element not found");
	Node* removableNode = previous->next;//запоминае удаляемый элемент
	previous->next = previous->next->next;//убираем удаляемый элемент из спика
	delete removableNode;//удаляем элемень
	size--;
}
template<class T>
inline void SLList<T>::sort()
{	
	//сортировка встаками
	for (size_t i = 0; i < size; i++)
	{
		Node x = Node(getNodeAt(i)->data);//запоминаем текущий элемент
		size_t j = i;
		//двигаем текущий элемент и ищем место под вставку
		while (j > 0 && getNodeAt(j - 1)->data > x.data) {
			getNodeAt(j)->data = getNodeAt(j - 1)->data;
			j--;
		}
		//всталяем текущий элемент
		getNodeAt(j)->data = x.data;
	}
}
template<class T>
inline void SLList<T>::clear()
{
	while (size > 0) { // пока список не пуст удаляем первый элемент
		pop_front();
	}
	head = 0;
	end = 0;
}
#endif



