#ifndef ENROLLMENT_HPP
#define ENROLLMENT_HPP

#include <string>

struct Enrollment {
    int studentId;
    std::string courseCode;
    std::string status;
};

bool canEnroll(const Enrollment& enrollment);
std::string processEnrollment(const Enrollment& enrollment);

#endif
