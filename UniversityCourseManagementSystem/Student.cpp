//
//  Student.cpp
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#include "Student.h"
#include <iostream>

Student::Student() {
    studentID = "";
    fullName = "";
}

Student::Student(const string& ID, const string& name) {
    studentID = ID;
    fullName = name;
}

string Student::getStudentID() const {
    return studentID;
}

string Student::getFullName() const {
    return fullName;
}

set<string> Student::getEnrolledCourses() const {
    return enrolledCourses;
}

void Student::setFullName(const string& name) {
    fullName = name;
}

void Student::enrollInCourse(const string& courseCode) {
    if (courseCode.empty()) {
        return;
    }
    
    enrolledCourses.insert(courseCode);
}

void Student::dropCourse(const string& courseCode) {
    if (courseCode.empty()) {
        return;
    }
    
    enrolledCourses.erase(courseCode);
}

int Student::getEnrollmentCount() const {
    return enrolledCourses.size();
}

void Student::displayEnrolledCourses() const {
    if (enrolledCourses.empty()){
        cout << "No courses enrolled." << endl;
        return;
    }
    
    cout << "Enrolled Courses: " << endl;
    for (const auto& course : enrolledCourses) {
        cout << " - " << course << endl;
    }
}
