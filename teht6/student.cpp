#include "Student.h"
#include <iostream>

Student::Student() : name(""), age(0) {
}

Student::Student(string n, int a) : name(n), age(a) {
}

string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

void Student::setName(string n) {
    name = n;
}

void Student::setAge(int a) {
    age = a;
}

void Student::printStudentInfo() const {
    cout << "Name: " << name << ", Age: " << age << endl;
}

bool compareByName(const Student& s1, const Student& s2) {
    return s1.getName() < s2.getName();
}

bool compareByAge(const Student& s1, const Student& s2) {
    return s1.getAge() < s2.getAge();
}
