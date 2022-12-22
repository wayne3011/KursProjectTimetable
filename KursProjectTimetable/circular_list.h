#pragma once
template <typename T>
class CircularList
{
private:
	struct Node {//структура записи в списке
		Node* next = this;//указатель на следующий элемент
		Node* previous = this;//указатель на предыдущий элемент
		T data;//значение записи
		Node(T data)
		{
			this->data = data;
		}
		Node(Node* previous, T data, Node* next)
		{
			this->next = next;
			this->data = data;
			this->previous = previous;
		}
	};
public:
	//добавление в конец
	void push_end(T data);
	//получение размера списка
	int GetSize() { return size; }
	//проверка на пустоту
	bool is_empty() { return head == 0; }
	//оператор доступа по индексу
	T operator[](int index) {
		if (is_empty()) throw std::exception("List is empty");
		Node* currentNode = head;
		int iterator = 0;
		while (iterator != index && iterator < size) {
			currentNode = currentNode->next;
			iterator ++;
		}
		if (iterator == size) throw std::exception("Element with this index does not exist");
		return currentNode->data;
	}
	//получение ссылки на значение элемента списка по значению
	T& getByValue(T data) {
		Node* currentNode = head;
		int iterator = 0;
		while (currentNode->data != data && iterator!=size) {
			currentNode = currentNode->next;
			iterator++;
		}
		if (iterator == size) throw std::exception("Element with this data does not exist");
		return currentNode->data;
	}
	//получение индекса элемента по значению
	int getIndexByValue(T data) {
		Node* currentNode = head;
		int iterator = 0;
		while (currentNode->data != data && iterator != size) {
			currentNode = currentNode->next;
			iterator++;
		}
		if (iterator == size) throw std::exception("Element with this data does not exist");
		return iterator;
	}
	//получение следующего элемента от данного значения
	T getNext(T node) {
		Node* current = head;
		int iterator = 0;
		while (node != current->data && iterator < size) {
			current = current->next;
			iterator++;
		}
		if (iterator == size) throw std::exception("Element with this count does not exist");
		return current->next->data;
	}
	//получение предыдущего элемента от данного значения
	T getPrevious(T node) {
		Node* current = head;
		int iterator = 0;
		while (node != current->data && iterator < size) {
			current = current->next;
			iterator++;
		}
		if (iterator == size) throw std::exception("Element with this count does not exist");
		return current->previous->data;
	}
	//удаление с начала
	void pop_front();
	//удалениме элемента по значению
	void removeByValue(T value);
	//очистка списка
	void clear();
	//сортировка списка
	void sort();
	
private:
	Node* head = 0;//указатель на начало списка
	int size = 0;//размер списка
};

template<typename T>
void CircularList<T>::push_end(T data)
{
	if (!head) {//если список пустой
		
		head = new Node(data);
		size++;
		return;
	}
	//иницилизируем новую запись
	//указатель на следующий - начало списка
	//указатель на предыдущий - элемент перед головой списка
	Node* newNode = new Node(head->previous, data, head);
	//вставляем новую запись в список
	head->previous->next = newNode;					
	head->previous = newNode;
	
	size++;
}

template<typename T>
inline void CircularList<T>::pop_front()
{
	if (is_empty()) throw std::exception("List is empty");
	//если в массиве не один элемент
	if (size == 1) { delete head; head = 0; return; }
	//разрушаем связи удаляемой записи со списком
	head->previous->next = head->next;
	head->next->previous = head->previous;
	Node* removableNode = head;
	head = head->next;//обновляем указатель на голову списка
	delete removableNode;//удаляем элемент
	size--;
}
template<typename T>
inline void CircularList<T>::removeByValue(T value)
{
	if (head->data == value) return pop_front();//если элемент с данными значением является головой списка
	//ищем удаляемый элемент с данным значением
	Node* removableNode = head->next;
	while (removableNode->data != value && removableNode != head) {
		removableNode = removableNode->next;
	}
	////если не нашли
	if (removableNode == head) throw std::exception("Element with this count does not exist");
	//убираем связь удаляемой записи с элементами списка
	removableNode->next->previous = removableNode->previous;
	removableNode->previous->next = removableNode->next;
	delete removableNode;//удаляем элемент
	size--;
}

template<typename T>
inline void CircularList<T>::clear()
{
	while (size > 0) {// пока список не пуст удаляем первый элемент
		pop_front();
	}
	head = 0;
}

template<typename T>
inline void CircularList<T>::sort()
{
	//сортировка встаками
	Node* i_pointer = head;//заись-итератор i для движения по списку
	for (size_t i = 0; i < size; i++)
	{
		Node x = Node(i_pointer->data);
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

