#pragma once
#include "queue.h"
#include "student_teacher.h"

void writeToTextFile(Queue<StudentTeacher>* queue, const std::string& filename);
void readFromTextFile(Queue<StudentTeacher>* queue, const std::string& filename);
void writeToBin(Queue<StudentTeacher>* queue, const std::string& filename);
void readFromBinFile(Queue<StudentTeacher>* queue, const std::string& filename);