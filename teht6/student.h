#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student {
private:
    string name;
    int age;

public:
    Student();
    Student(string n, int a);

    string getName() const;
    int getAge() const;

    void setName(string n);
    void setAge(int a);

    void printStudentInfo() const;
};

bool compareByName(const Student& s1, const Student& s2);
bool compareByAge(const Student& s1, const Student& s2);

#endif
