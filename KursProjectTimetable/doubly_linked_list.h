#pragma once
#include <iostream>
template<typename T>
class DLList
{
private:
	struct Node {
		Node* previous = 0;
		Node* next = 0;
		T data;
		Node(T data) {
			this->data = data;
		}
		Node(Node* previous, T data, Node* next) {
			this->data = data;
			this->next = next;
			this->previous = previous;
		}
	};
public:
	bool is_empty() { return head == 0; }
	int getSize() { return size; }
	void push_begin(T data);
	void push_end(T data);
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
	void pop_front();
	void pop_back();
	void removeByValue(T value);
private:
	Node* head = 0;
	Node* end = 0;
	int size = 0;
};

template<typename T>
inline void DLList<T>::push_begin(T data)
{
	if (is_empty()) {
		end = head = new Node(data);
		size++;
		return;
	}
	head->previous = new Node(0,data,head);
	head = head->previous;
	size++;
}

template<typename T>
inline void DLList<T>::push_end(T data)
{
	if (is_empty()) return push_begin(data);
	end->next = new Node(end, data, 0);
	end = end->next;
	size++;
}

template<typename T>
inline void DLList<T>::pop_front()
{
	if (is_empty()) throw std::exception("List is empty");
	if (head->next) head->next->previous = 0;
	Node* removableNode = head;
	head = head->next;
	delete removableNode;
	size--;
}

template<typename T>
inline void DLList<T>::pop_back()
{
	if (is_empty()) throw std::exception("List is empty");
	if (end == head) return pop_front();
	end->previous->next = 0;
	Node* removableNode = end;
	end = end->previous;
	delete removableNode;
	size--;
}

template<typename T>
inline void DLList<T>::removeByValue(T value)
{
	if (is_empty()) throw std::exception("List is empty");
	if (head->data == value) return pop_front();
	if (end->data == value) return pop_back();
	Node* currentNode = head;
	while (currentNode->data != value && currentNode) {
		currentNode = currentNode->next;
	}
	if (!currentNode) throw std::exception("Element not found");
	currentNode->previous->next = currentNode->next;
	currentNode->next->previous = currentNode->previous;
	delete currentNode;
	size--;
}
