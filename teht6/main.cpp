#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Student.h"

using namespace std;

int main()
{
    int selection = 0;
    vector<Student> studentList;

    do
    {
        cout << endl;
        cout << "Select" << endl;
        cout << "Add students = 0" << endl;
        cout << "Print all students = 1" << endl;
        cout << "Sort and print students according to Name = 2" << endl;
        cout << "Sort and print students according to Age = 3" << endl;
        cout << "Find and print student = 4" << endl;
        cout << "Exit = 5" << endl;
        cin >> selection;

        switch(selection)
        {
        case 0:
        {
            string name;
            int age;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter student age: ";
            cin >> age;
            Student newStudent(name, age);
            studentList.push_back(newStudent);
            cout << "Student added successfully!" << endl;
            break;
        }
        case 1:
        {
            if (studentList.empty()) {
                cout << "No students in the list." << endl;
            } else {
                cout << "\nAll students:" << endl;
                for (const Student& student : studentList) {
                    student.printStudentInfo();
                }
            }
            break;
        }
        case 2:
        {
            if (studentList.empty()) {
                cout << "No students to sort." << endl;
            } else {
                sort(studentList.begin(), studentList.end(), compareByName);
                cout << "\nStudents sorted by name:" << endl;
                for (const Student& student : studentList) {
                    student.printStudentInfo();
                }
            }
            break;
        }
        case 3:
        {
            if (studentList.empty()) {
                cout << "No students to sort." << endl;
            } else {
                sort(studentList.begin(), studentList.end(), compareByAge);
                cout << "\nStudents sorted by age:" << endl;
                for (const Student& student : studentList) {
                    student.printStudentInfo();
                }
            }
            break;
        }
        case 4:
        {
            if (studentList.empty()) {
                cout << "No students in the list." << endl;
            } else {
                string searchName;
                cout << "Enter student name to search: ";
                cin.ignore();
                getline(cin, searchName);
                auto it = find_if(studentList.begin(), studentList.end(),
                                  [&searchName](const Student& s) {
                                      return s.getName() == searchName;
                                  });
                if (it != studentList.end()) {
                    cout << "\nStudent found:" << endl;
                    it->printStudentInfo();
                } else {
                    cout << "Student '" << searchName << "' not found." << endl;
                }
            }
            break;
        }
        case 5:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Wrong selection, stopping..." << endl;
            break;
        }
    } while(selection < 5);

    return 0;
}
