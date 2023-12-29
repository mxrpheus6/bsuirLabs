#pragma once
#include <iostream>

template<typename T>
struct Node {
	T data;
	Node* next;
	Node(const T data);
};

template<typename T>
class Queue {
private:
	Node<T>* _front;
	Node<T>* _rear;
	int _size;
public:
	Queue();
	Queue(const Queue& queue);
	~Queue();
	
	bool empty();
	int size();
	void push(const T data);
	T pop();
	void print();
	T front();
	T rear();

	class Iterator {
		Node<T>* current;
	public:
		Iterator(Node<T>* start) : current(start) {}

		T& operator*() const {
			return (current->data);
		}

		Iterator& operator++() {
			current = current->next;
			return *this;
		}

		Iterator operator+(int offset) const {
			Iterator result = *this;
			for (int i = 0; i < offset; i++) {
				if (result.current == nullptr)
					break;
				result.current = result.current->next;
			}
			return result;
		}

		bool operator==(const Iterator& other) const {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}
	};

	Iterator begin() const {
		return Iterator(_front);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}

	template <typename Predicate>
	Iterator search(Iterator begin, Iterator end, Predicate condition) {
		while (begin != end) {
			if (condition(*begin)) {
				return begin;
			}
			++begin;
		}
		return end;
	}

	template <typename Predicate>
	void sort(Iterator begin, Iterator end, Predicate condition) {
		bool swapped;
		do {
			swapped = false;
			for (Iterator it = begin ; it != end && it + 1 != end; ++it) {
				Iterator nextIt = it + 1;
				if (condition(*it, *nextIt)) {
					std::swap(*it, *nextIt);
					swapped = true;
				}
			}
		} while (swapped);
	}

	class ConstIterator {
		const Node<T>* current;

	public:
		ConstIterator(const Node<T>* start) : current(start) {}

		const T& operator*() const {
			return current->data;
		}

		ConstIterator& operator++() {
			current = current->next;
			return *this;
		}

		ConstIterator operator+(int offset) const {
			ConstIterator result = *this;
			for (int i = 0; i < offset; ++i) {
				if (result.current == nullptr)
					break;
				result.current = result.current->next;
			}
			return result;
		}

		bool operator==(const ConstIterator& other) const {
			return current == other.current;
		}

		bool operator!=(const ConstIterator& other) const {
			return current != other.current;
		}
	};

	ConstIterator cbegin() const {
		return ConstIterator(_front);
	}

	ConstIterator cend() const {
		return ConstIterator(nullptr);
	}

	template <typename Predicate>
	ConstIterator search(ConstIterator begin, ConstIterator end, Predicate condition) {
		while (begin != end) {
			if (condition(*begin)) {
				return begin;
			}
			++begin;
		}
		return end;
	}
};

template<typename T>
Node<T>::Node(const T data) {
	this->data = data;
	next = nullptr;
}

template<typename T>
Queue<T>::Queue() {
	_front = _rear = nullptr;
	_size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue& queue) {
	_front = queue._front;
	_rear = queue._rear;
	_size = queue._size;
}

template<typename T>
Queue<T>::~Queue() {
	while (_front != nullptr) {
		pop();
	}
}

template<typename T>
bool Queue<T>::empty() {
	return _size <= 0;
}

template<typename T>
int Queue<T>::size() {
	return _size;
}

template<typename T>
void Queue<T>::push(const T data) {
	Node<T>* new_node = new Node<T>(data);
	if (empty()) {
		_front = _rear = new_node;
	}
	else {
		_rear->next = new_node;
		_rear = new_node;
	}

	_size++;
}

template<typename T>
T Queue<T>::pop() {
	if (empty())
		throw std::string("Queue is empty!");

	Node<T>* temp = _front;
	T deleted_data = _front->data;
	_front = _front->next;
	_size--;
	delete temp;

	return deleted_data;
}

template<typename T>
void Queue<T>::print() {
	if (empty()) 
		throw std::string("Queue is empty!");
	
	Node<T>* temp = _front;

	while (temp != nullptr) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}

template<typename T>
T Queue<T>::front() {
	if (empty())
		throw std::string("Queue is empty!");

	return _front->data;
}

template<typename T>
T Queue<T>::rear() {
	if (empty())
		throw std::string("Queue is empty!");

	return _rear->data;
}