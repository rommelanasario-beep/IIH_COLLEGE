#include "../include/dashboard.hpp"

DashboardStats calculateDashboard(
    int students,
    int enrollments,
    int pendingAdmissions,
    int courses
) {
    DashboardStats stats{};

    stats.totalStudents = students;
    stats.totalEnrollments = enrollments;
    stats.pendingAdmissions = pendingAdmissions;
    stats.availableCourses = courses;

    return stats;
}
