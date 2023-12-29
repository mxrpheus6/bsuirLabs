#include <iostream>

#include "queue.h"

bool condition(const int num) {
	return num == 128;
}

bool compare(const int a, const int b) {
	return a > b;
}

int main(void) {

	Queue<int> queue;

	queue.push(256);
	queue.push(128);
	queue.push(64);

	//оператор +
	//Queue<int>::Iterator iter = queue.begin();
	//*iter = *(iter + 2);

	//вывод и изменения
	queue.sort(queue.begin(), queue.end(), compare);

	for (auto it = queue.begin(); it != queue.end(); ++it) {
		std::cout << *it << " ";
	}
	//for (auto it = queue.begin(); it != queue.end(); ++it) {
	//	*it = 777;
	//}

	std::cout << std::endl;

	for (auto& it : queue) {
		std::cout << it << " ";
	}

	//проверка поиска
	Queue<int>::Iterator iter = queue.search(queue.begin(), queue.end(), condition);

	if (iter != queue.end()) {
		std::cout << "Found: " << *iter << std::endl;
	}
	else {
		std::cout << "Not found" << std::endl;
	}

	return 0;

}