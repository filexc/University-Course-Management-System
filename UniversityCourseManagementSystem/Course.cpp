//
//  Course.cpp
//  University Course Management System
//
//  Created by Violet Chaffee on 7/30/25.
//

#include "Course.h"
#include <iostream>

/**
 @brief default constructor for the Course class
 
 @details initializes courseCode, title, and instructorName to empty strings, capacity to 30, and currentEnrollment to 0
 */
Course::Course() {
    courseCode = "";
    title = "";
    instructorName = "";
    capacity = 30;
    currentEnrollment = 0;
}

/**
 @brief parameterized constructor for the Course class
 
 @details initializes the course with the given code, title, instructor name, and capacity. currentEnrollment is initialized to 0
 
 @param code the course code
 @param courseTitle the course title
 @param instructor the instructor's name
 @param maxCapacity the maximum capacity of the course
 */
Course::Course(const string& code, const string& courseTitle, const string& instructor, int maxCapacity) {
    courseCode = code;
    title = courseTitle;
    instructorName = instructor;
    capacity = maxCapacity;
    currentEnrollment = 0;
}

/**
 @brief returns the course code
 
 @return (string) the course code
 */
string Course::getCourseCode() const {
    return courseCode;
}

/**
 @brief returns the course title
 
 @return (string) the course title
 */
string Course::getTitle() const {
    return title;
}

/**
 @brief returns the instructor's name
 
 @return (string) the instructor's name
 */
string Course::getInstructorName() const {
    return instructorName;
}

/**
 @brief returns the list of enrolled students
 
 @return (set<string>) a set of student IDs currently enrolled in the course
 */
set<string> Course::getEnrolledStudents() const {
    return enrolledStudents;
}

/**
 @brief returns the course capacity
 
 @return (int) the maximum number of students allowed in the course
 */
int Course::getCapacity() const {
    return capacity;
}

/**
 @brief returns the number of students currently enrolled in the course
 
 @return (int) the current enrollment count
 */
int Course::getCurrentEnrollment() const {
    return currentEnrollment;
}

/**
 @brief returns the size of the waitlist
 
 @return (int) the number of students on the waitlist
 */
int Course::getWaitlistSize() const {
    return waitlist.size();
}

/**
 @brief sets the course title
 
 @param courseTitle the new course title
 */
void Course::setTitle(const string& courseTitle) {
    title = courseTitle;
}

/**
 @brief sets the instructor's name
 
 @param instructor the new instructor's name
 */
void Course::setInstructorName(const string& instructor){
    instructorName = instructor;
}

/**
 @brief sets the course capacity
 
 @param maxCapacity the new maximum capacity
 */
void Course::setCapacity(int maxCapacity) {
    capacity = maxCapacity;
}

/**
 @brief enrolls a student in the course
 
 @details adds the student to the enrolled list if space is available. If the course is full, the student is added to the waitlist. handles duplicates and exmpty IDs.
 
 @param studentID the student ID to enroll
 
 @return (bool) true if the student is enrolled, false otherwise
 */
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

/**
 @brief drops a student from the course
 
 @details if the student is enrolled, removes them and fills the spot from the waitlist
 
 @param studentID the student ID to drop
 
 @return (bool) true if the student was enrolled and removed, false otherwise
 */
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

/**
 @brief checks if a student is enrolled in the course
 
 @param studentID the student ID to check
 
 @return (bool) true if the student is enrolled, false otherwise
 */
bool Course::isStudentEnrolled(const string& studentID) const {
    return enrolledStudents.find(studentID) != enrolledStudents.end();
}

/**
 @brief adds a student to the waitlist
 
 @details prevents duplicates by scanning the waitlist before adding
 
 @param studentID the student ID to add to the waitlist
 
 @return (bool) true if successfully added, false if already on the waitlist
 */
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

/**
 @brief removes and returns the next student from the waitlist
 
 @details follows first in, first out behavior
 
 @return (string) the student ID removed from the waitlist, or an empty string if none
 */
string Course::removeFromWaitlist() {
    if (waitlist.empty()) {
        return "";
    }
    
    string studentID = waitlist.front();
    waitlist.pop();
    return studentID;
}

/**
 @brief checks if the course has available seats
 
 @return (bool) true if there is space in the course, false otherwise
 */
bool Course::hasAvailableSeats() const {
    return currentEnrollment < capacity;
}

/**
 @brief displays the list of enrolled students
 
 @details outputs all enrolled student IDs to the console
 */
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

/**
 @brief displays the waitlist for the course
 
 @details outputs the current waitlisted students in order
 */
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
