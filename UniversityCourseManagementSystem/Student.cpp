//
//  Student.cpp
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#include "Student.h"
#include <iostream>

/**
 @brief default constructor for the Student class
 
 @details initializes studentID and fullName to empty strings
 */
Student::Student() {
    studentID = "";
    fullName = "";
}

/**
 @brief paramaterized constructor for the Student class
 
 @details initializes studentID and fullName to the provided values
 
 @param ID the student ID
 @param name the full name of the student
 */
Student::Student(const string& ID, const string& name) {
    studentID = ID;
    fullName = name;
}

/**
 @brief returns the student ID
 
 @return (string) the student ID
 */
string Student::getStudentID() const {
    return studentID;
}

/**
 @brief returns the student's full name
 
 @return (string) the student's full name
 */
string Student::getFullName() const {
    return fullName;
}

/**
 @brief returns the courses the student is enrolled in
 
 @return (set<string>) the set of strings representing the enrolled course codes
 */
set<string> Student::getEnrolledCourses() const {
    return enrolledCourses;
}

/**
 @brief sets the full name of the student to a new name
 
 @param name the new full name of the student
 */
void Student::setFullName(const string& name) {
    fullName = name;
}

/**
 @brief enrolls a student in a course
 
 @details adds a course code to the enrolledCourses set. if the courseCode is empty, the operation is ignored
 
 @param courseCode the course code to enroll in
 */
void Student::enrollInCourse(const string& courseCode) {
    if (courseCode.empty()) {
        return;
    }
    
    enrolledCourses.insert(courseCode);
}

/**
 @brief drops acourse from the student's enrollment
 
 @details removes the course code from the enrolledCourses set. if the courseCode is empty, the operation is ignored
 
 @param courseCode the course code to drop
 */
void Student::dropCourse(const string& courseCode) {
    if (courseCode.empty()) {
        return;
    }
    
    enrolledCourses.erase(courseCode);
}

/**
 @brief returns the number of courses the student is enrolled in
 
 @return (int) the number of enrolled courses
 */
int Student::getEnrollmentCount() const {
    return enrolledCourses.size();
}

/**
 @brief displays the list of enrolled courses
 
 @details outputs a formatted list of all enrolled course codes to the console. if no courses are enrolled, it notifies the user in the console accordingly
 */
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
