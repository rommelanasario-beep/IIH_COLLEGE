#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>

struct Course {
    std::string code;
    std::string name;
    int capacity;
};

bool isValidCourse(const std::string& code);
int getCourseCapacity(const std::string& code);

#endif
