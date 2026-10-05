#include "../include/admission.hpp"
#include "../include/course.hpp"

bool validateAdmission(const Admission& admission) {
    return !admission.applicantName.empty() &&
           !admission.email.empty() &&
           isValidCourse(admission.preferredCourse) &&
           admission.grade >= 0.0 &&
           admission.grade <= 100.0;
}

std::string evaluateAdmission(const Admission& admission) {
    if (!validateAdmission(admission))
        return "INVALID";

    if (admission.grade >= 75.0)
        return "QUALIFIED";

    return "NOT QUALIFIED";
}
