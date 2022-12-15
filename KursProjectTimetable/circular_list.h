#pragma once
//struct Faculty {
//	int number;
//	bool operator==(Faculty current) {
//
//	};
//	bool operator!=(Faculty current) {
//
//	};
//
//};
template <typename T>
class CircularList
{
private:
	struct Node {
		Node* next = this;
		Node* previous = this;
		T data;
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

	void push_end(T data);
	int GetSize() { return size; }
	bool is_empty() { return head == 0; }
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
	void pop_front();
	void removeByValue(T value);
private:
	Node* head = 0;
	int size = 0;
};

template<typename T>
void CircularList<T>::push_end(T data)
{
	if (!head) {
		head = new Node(data);
		size++;
		return;
	}
	if (!head->previous) {
		head->previous = new Node(head, data, head);
		size++;
		return;
	}
	Node* newNode = new Node(head->previous, data, head);
	head->previous->next = newNode;
	head->previous = newNode;
	
	size++;
}

template<typename T>
inline void CircularList<T>::pop_front()
{
	if (is_empty()) throw std::exception("List is empty");
	if (size == 1) { delete head; head = 0; return; }
	head->previous->next = head->next;
	head->next->previous = head->previous;
	Node* removableNode = head;
	head = head->next;
	delete removableNode;
	size--;
}
template<typename T>
inline void CircularList<T>::removeByValue(T value)
{
	if (head->data == value) return pop_front();
	Node* removableNode = head->next;
	while (removableNode->data != value && removableNode != head) {
		removableNode = removableNode->next;
	}
	removableNode->next->previous = removableNode->previous;
	removableNode->previous->next = removableNode->next;
	delete removableNode;
	size--;
}

