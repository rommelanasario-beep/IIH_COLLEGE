#include "../include/enrollment.hpp"
#include "../include/course.hpp"

bool canEnroll(const Enrollment& enrollment) {
    return enrollment.studentId > 0 &&
           isValidCourse(enrollment.courseCode);
}

std::string processEnrollment(const Enrollment& enrollment) {
    if (!canEnroll(enrollment))
        return "REJECTED";

    return "APPROVED";
}
