#include <iostream>

#include "menu.h"
#include "student_teacher.h"
#include "files.h"

int main() {
    char first_name1[] = "Pavel";
    char last_name1[] = "Kazachenko";
    int marks1[] = { 10, 9, 10, 8, -1 };

    char first_name2[] = "Ivan";
    char last_name2[] = "Ivanich";
    int marks2[] = { 6, 4, 2, -1 };

    char first_name3[] = "John";
    char last_name3[] = "Smith";
    int marks3[] = { 8, 8, -1 };

	StudentTeacher st1(first_name1, last_name1, 198.2, 2, 870, 10);
	StudentTeacher st2(first_name2, last_name2, 104.5, 0.5, 200, 2);
	StudentTeacher st3(first_name3, last_name3, 154.4, 1.5, 1000, 6);

    Queue<StudentTeacher>* queueSource = new Queue<StudentTeacher>();
    Queue<StudentTeacher>* queueResult = new Queue<StudentTeacher>();

    queueSource->push(st1);
    queueSource->push(st2);
    queueSource->push(st3);


    writeToTextFile(queueSource, "D:\\BSUIR\\bsuirLabs\\3sem\\ПнаЯВУ\\laba6\\in.txt");
    readFromTextFile(queueResult, "D:\\BSUIR\\bsuirLabs\\3sem\\ПнаЯВУ\\laba6\\in.txt");

    int size = queueResult->size();
    Node<StudentTeacher>* node = queueResult->front();
    std::cout << "TXT FILE IN OBJECT OUTPUT" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << node->data.get_fisrt_name() << " " << node->data.get_last_name() << " " << node->data.get_scholarship() << " " <<
            node->data.get_rate() << " " << node->data.get_salary() << " " << node->data.get_amount_of_articles() << "\n";
       
        node = node->next;
    }

    queueResult->clear();
    queueResult = new Queue<StudentTeacher>();

    writeToBin(queueSource, "D:\\BSUIR\\bsuirLabs\\3sem\\ПнаЯВУ\\laba6\\in.bin");
    readFromBinFile(queueResult, "D:\\BSUIR\\bsuirLabs\\3sem\\ПнаЯВУ\\laba6\\in.bin");

    size = queueResult->size();
    node = queueResult->front();
    std::cout << std::endl << "BIN FILE IN OBJECT OUTPUT" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << node->data.get_fisrt_name() << " " << node->data.get_last_name() << " " << node->data.get_scholarship() << " " <<
            node->data.get_rate() << " " << node->data.get_salary() << " " << node->data.get_amount_of_articles() << "\n";

        node = node->next;
    }

	return 0;
}