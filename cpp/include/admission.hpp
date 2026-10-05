#ifndef ADMISSION_HPP
#define ADMISSION_HPP

#include <string>

struct Admission {
    std::string applicantName;
    std::string email;
    std::string preferredCourse;
    double grade;
};

bool validateAdmission(const Admission& admission);
std::string evaluateAdmission(const Admission& admission);

#endif
