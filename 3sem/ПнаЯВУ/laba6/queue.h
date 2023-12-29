#pragma once
#include <iostream>
#include <fstream>

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
	Node<T>* front();
	Node<T>* rear();
	void clear();
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
Node<T>* Queue<T>::front() {
	if (empty())
		throw std::string("Queue is empty!");

	return _front;
}

template<typename T>
Node<T>* Queue<T>::rear() {
	if (empty())
		throw std::string("Queue is empty!");

	return _rear->data;
}

template<typename T>
void Queue<T>::clear() {
	while (_front != nullptr) {
		Node<T>* temp = _front;
		_front = _front->next;
		delete temp;
	}
}