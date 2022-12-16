
#ifndef  LIST_H
#define LIST_H
#include <iostream>

template<class T>
class SLList
{
private:
	struct Node {//структура записи в списке
		Node* next = 0;
		T data;
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
	void push_end(T data);
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
	T& getByValue(T data) {
		Node* currentNode = head;
		int iterator = 0;
		while (currentNode->data != data && currentNode != 0) {
			currentNode = currentNode->next;
			iterator++;
		}
		if (!currentNode) throw std::exception("Element with this data does not exist");
		return currentNode->data;
	}
	int getSize() { return size; }
	bool is_empty();
	void pop_front();
	void pop_back();
	void removeByValue(T value);
	void sort();
	void clear();
	
private:
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
	if (end == nullptr) { 
		end = newNode; 
		head = newNode;
		size++;
		return;
	}
	end->next = newNode;
	size++;
	end = newNode;
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
	
	Node* current = head->next;
	delete head;
	head = current;
	size--;
}

template<class T>
inline void SLList<T>::pop_back()
{
	if (is_empty()) throw std::exception("List is empty");
	if (head == end) return pop_front();
	Node* previous = head;
	while (previous->next != end) previous = previous->next;
	delete previous->next;
	previous->next = 0;
	size--;
	end = previous;
}

template<class T>
inline void SLList<T>::removeByValue(T value)
{
	if (is_empty()) throw std::exception("List is empty");
	if(value == head->data) return pop_front();
	if (value == end->data) return pop_back();
	Node* previous = head;
	while (previous->next && previous->next->data != value) previous = previous->next;
	if (!previous->next) throw std::exception("Element not found");
	Node* removableNode = previous->next;
	previous->next = previous->next->next;
	delete removableNode;
	size--;
}
template<class T>
inline void SLList<T>::sort()
{	
	for (size_t i = 0; i < size; i++)
	{
		Node x = Node(getNodeAt(i)->data);
		size_t j = i;
		while (j > 0 && getNodeAt(j - 1)->data > x.data) {
			getNodeAt(j)->data = getNodeAt(j - 1)->data;
			j--;
		}
		getNodeAt(j)->data = x.data;
	}
}
template<class T>
inline void SLList<T>::clear()
{
	while (size > 0) {
		pop_front();
	}
	head = 0;
	end = 0;
}
#endif



