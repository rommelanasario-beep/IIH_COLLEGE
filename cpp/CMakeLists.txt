cmake_minimum_required(VERSION 3.16)
project(iih_college_algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(course_recommender src/course_recommender.cpp)
add_executable(student_ranker src/student_ranker.cpp)
add_executable(enrollment_allocator src/enrollment_allocator.cpp)
