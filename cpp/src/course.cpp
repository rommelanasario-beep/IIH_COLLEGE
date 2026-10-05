#include "../include/course.hpp"

bool isValidCourse(const std::string& code) {
    return code == "BSCRIM" ||
           code == "BSTM" ||
           code == "BSIS" ||
           code == "BSAIS" ||
           code == "BSA" ||
           code == "BTVTED";
}

int getCourseCapacity(const std::string& code) {
    if (!isValidCourse(code))
        return 0;

    return 50;
}
