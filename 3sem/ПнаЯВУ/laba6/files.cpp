#include "files.h"

void writeToTextFile(Queue<StudentTeacher>* queue, const std::string& filename) {
	std::ofstream inFile(filename, std::ios::out | std::ios::trunc);

	if (!inFile.is_open()) {
		std::cerr << "Error writing to text file!" << std::endl;
		return;
	}

	
	int size = queue->size();
	Node<StudentTeacher>* node = queue->front();
	for (int i = 0; i < size; i++) {
		inFile << node->data.get_fisrt_name() << " "  << node->data.get_last_name() << " " << node->data.get_scholarship() << " " <<
				  node->data.get_rate() << " " << node->data.get_salary() << " " << node->data.get_amount_of_articles() << "\n";

		node = node->next;
	}


	inFile.close();
}

void readFromTextFile(Queue<StudentTeacher>* queue, const std::string& filename) {
	std::ifstream fromFile(filename);

	if (!fromFile.is_open()) {
		std::cerr << "Error writing to text file!" << std::endl;
		return;
	}

	StudentTeacher* st;

	char first_name[20];
	char last_name[20];
	double rate;
	double salary;
	double scholarship;
	int amount_of_articles;

	while (fromFile >> first_name >> last_name >> scholarship >> rate >> salary >> amount_of_articles) {
		st = new StudentTeacher(first_name, last_name, scholarship, rate, salary, amount_of_articles);
		queue->push(*st);
		delete st;
	}

	fromFile.close();
}

void writeToBin(Queue<StudentTeacher>* queue, const std::string& filename) {
	std::ofstream inFile(filename, std::ios::out | std::ios::trunc | std::ios::binary);

	if (!inFile.is_open()) {
		std::cerr << "Error writing to text file!" << std::endl;
		return;
	}

	int size = queue->size();
	Node<StudentTeacher>* node = queue->front();
	StudentTeacher& st = node->data;
	for (int i = 0; i < size; i++) {
		st = node->data;
		inFile.write(reinterpret_cast<const char*>(&st), sizeof(StudentTeacher));

		node = node->next;
	}

}

void readFromBinFile(Queue<StudentTeacher>* queue, const std::string& filename) {
	std::ifstream fromFile(filename);
	if (!fromFile.is_open()) {
		std::cerr << "Error writing to text file!" << std::endl;
		return;
	}

	StudentTeacher st;

	if (fromFile.is_open()) {
		while (fromFile.read(reinterpret_cast<char*>(&st), sizeof(st))) {
			queue->push(st);
		}
	}
	fromFile.close();
}