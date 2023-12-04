#pragma once
#include <iostream>

#include "student_teacher.h"
#include "queue.h"

int input_check();
void press_to_continue();
void print_menu();

template<typename T>
void test() {
    char first_name1[] = "Pavel";
    char last_name1[] = "Kazachenko";
    int marks1[] = { 10, 9, 10, 8, -1 };

    char first_name2[] = "Ivan";
    char last_name2[] = "Ivanich";
    int marks2[] = { 6, 4, 2, -1 };

    char first_name3[] = "John";
    char last_name3[] = "Smith";
    int marks3[] = { 8, 8, -1 };

    StudentTeacher st1(first_name1, last_name1, marks1, 198.2, 2, 870, 10);
    StudentTeacher st2(first_name2, last_name2, marks2, 104.5, 0.5, 200, 2);
    StudentTeacher st3(first_name3, last_name3, marks3, 154.4, 1.5, 1000, 6);

    Queue<T> queueSource;

    queueSource.push(st1);

}
