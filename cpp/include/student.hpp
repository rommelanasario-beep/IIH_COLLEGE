#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

struct Student {
    int id;
    std::string fullName;
    std::string email;
    std::string course;
    double grade;
};

bool validateStudent(const Student& student);
std::string studentStatus(const Student& student);

#endif
