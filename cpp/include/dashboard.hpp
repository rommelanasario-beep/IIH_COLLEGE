#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

struct DashboardStats {
    int totalStudents;
    int totalEnrollments;
    int pendingAdmissions;
    int availableCourses;
};

DashboardStats calculateDashboard(
    int students,
    int enrollments,
    int pendingAdmissions,
    int courses
);

#endif
