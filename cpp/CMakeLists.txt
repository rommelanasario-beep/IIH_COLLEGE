cmake_minimum_required(VERSION 3.16)

project(IIHCollegeEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(iih_college_engine
    src/main.cpp
    src/student.cpp
    src/course.cpp
    src/enrollment.cpp
    src/admission.cpp
    src/dashboard.cpp
    src/student_ranker.cpp
    src/course_recommender.cpp
    src/enrollment_allocator.cpp
)
