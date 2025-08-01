//
//  Course.cpp
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#include "Course.h"
#include <iostream>

Course::Course() {
    courseCode = "";
    title = "";
    instructorName = "";
    capacity = 30;
    currentEnrollment = 0;
}

Course::Course(const string& code, const string& courseTitle, const string& instructor, int maxCapacity) {
    courseCode = code;
    title = courseTitle;
    instructorName = instructor;
    capacity = maxCapacity;
    currentEnrollment = 0;
}

string Course::getCourseCode() const {
    return courseCode;
}

string Course::getTitle() const {
    return title;
}

string Course::getInstructorName() const {
    return instructorName;
}

set<string> Course::getEnrolledStudents() const {
    return enrolledStudents;
}

int Course::getCapacity() const {
    return capacity;
}

int Course::getCurrentEnrollment() const {
    return currentEnrollment;
}

int Course::getWaitlistSize() const {
    return waitlist.size();
}

void Course::setCourseCode(const string& code) {
    courseCode = code;
}

void Course::setTitle(const string& courseTitle) {
    title = courseTitle;
}

void Course::setInstructorName(const string& instructor){
    instructorName = instructor;
}

void Course::setCapacity(int maxCapacity) {
    capacity = maxCapacity;
}

bool Course::enrollStudent(const string& studentID) {
    if (studentID.empty()){
        cout << "No student ID provided" << endl;
        return false;
    }
    
    if (isStudentEnrolled(studentID)) {
        cout << "Student already enrolled in course" << endl;
        return false;
    }
    
    if (hasAvailableSeats()) {
        enrolledStudents.insert(studentID);
        currentEnrollment++;
        return true;
    } else {
        bool addedToWaitlist = addToWaitlist(studentID);
        if (addedToWaitlist) {
            cout << "Added student to waitlist" << endl;
        }
        return false;
    }
}

bool Course::dropStudent(const string& studentID) {
    if (studentID.empty()) {
        return false;
    }
    
    size_t removed = enrolledStudents.erase(studentID);
    if (removed > 0) {
        currentEnrollment--;
        
        if (!waitlist.empty()) {
            string waitlistedStudent = removeFromWaitlist();
            if (!waitlistedStudent.empty()) {
                enrolledStudents.insert(waitlistedStudent);
                currentEnrollment++;
            }
        }
        return true;
    }
    
    return false;
}

bool Course::isStudentEnrolled(const string& studentID) const {
    return enrolledStudents.find(studentID) != enrolledStudents.end();
}

bool Course::addToWaitlist(const string& studentID) {
    if (studentID.empty()) {
        return false;
    }
    
    queue<string> tempQueue = waitlist;
    while (!tempQueue.empty()) {
        if (tempQueue.front() == studentID) {
            cout << "already on waitlist" << endl;
            return false;
        }
        tempQueue.pop();
    }
    waitlist.push(studentID);
    return true;
}

string Course::removeFromWaitlist() {
    if (waitlist.empty()) {
        return "";
    }
    
    string studentID = waitlist.front();
    waitlist.pop();
    return studentID;
}

bool Course::isFull() const {
    return currentEnrollment >= capacity;
}

bool Course::hasAvailableSeats() const {
    return currentEnrollment < capacity;
}

void Course::displayInfo() const {
    cout << "Course Code: " << courseCode << endl;
    cout << "Title: " << title << endl;
    cout << "Instructor: " << instructorName << endl;
    cout << "Enrollment: " << currentEnrollment << "/" << capacity << endl;
    cout << "Waitlist Size: " << getWaitlistSize() << endl;
}

void Course::displayEnrolledStudents() const {
    if (enrolledStudents.empty()) {
        cout << "No students enrolled" << endl;
        return;
    }
    
    cout << "Enrolled Students (" << currentEnrollment << "):" << endl;
    for (const auto& student : enrolledStudents) {
        cout << " - " << student << endl;
    }
}

void Course::displayWaitlist() const {
    if (waitlist.empty()) {
        cout << "No students on waitlist" << endl;
        return;
    }
    
    cout << "Waitlist (" << getWaitlistSize() << "):" << endl;
    queue<string> tempQueue = waitlist;
    int position = 1;
    while (!tempQueue.empty()) {
        cout << " " << position << ". " << tempQueue.front() << endl;
        tempQueue.pop();
        position++;
    }
}
