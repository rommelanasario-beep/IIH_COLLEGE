#include "../include/student.hpp"

bool validateStudent(const Student& student) {
    return student.id > 0 &&
           !student.fullName.empty() &&
           !student.email.empty() &&
           !student.course.empty() &&
           student.grade >= 0.0 &&
           student.grade <= 100.0;
}

std::string studentStatus(const Student& student) {
    if (!validateStudent(student))
        return "INVALID";

    if (student.grade >= 90)
        return "EXCELLENT";

    if (student.grade >= 75)
        return "REGULAR";

    return "AT RISK";
}
