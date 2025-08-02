# University Course Management System Design Decisions and STL Usage Documentation

## Overview
This document outlines design decisions and STL contained usage in the University Course Management System. The system demonstrates the effective use of various Standard Template Library (STL) containers and object-oriented programming principles in a real-world C++ application.

## System Architecture

### Object-Oriented Design

#### Class Hierarchy
The system follows a clear modular design with three main classes:
- **`Student` Class**: Manages individual student data and enrollment
- **`Course` Class**: Manages course information and student enrollment
- **`UniversitySystem` Class**: Handles all operations and maintains the state of the system

#### Encapsulation
Each class encapsulates its data and provides controlled access through public methods:
- Private member variables protect data
- Public getter/setter methods provide controlled access
- Logic and actions are contained within appropriate classes

## STL Container Usage

### `map` Usage

#### Student & Course Registry
```cpp
map<string, Student> students;
map<string, Course> courses;
```
- **Key**: Student ID or Course Code (string)
- **Value**: Student or Course Object
- **Purpose**: Store all student and course records with unique IDs or codes
- **Advantages**:
    - O(log n) lookup
    - Automatic sorting by key
    - Prevents duplicate elements
    - Efficient insertion and deletion

#### Instructor Search Results
```cpp
map<string, string> getStudentsByInstructor(const string& instructor) const;
```
- **Purpose**: Return student ID to name mappings for an instructor
- **Advantages**:
- Efficient lookup by instructor
- Structured data return
- Easy iteration and display

### `set` Usage

#### Student & Course Enrollments
```cpp
set<string> enrolledCourses; // In Student class
set<string> enrolledStudents; // In Course class
```
- **Purpose**: Track courses a student is enrolled in / students enrolled in a course
- **Advantages**:
- Automatically prevents duplicate enrollments
- O(log n) insertion and lookup
- Sorted order for consistent display
- Efficient removal operations

### `queue` Usage

#### Course Waitlists
```cpp
queue<string> waitlist; // In Course class
```
- **Purpose**: Manage students waiting for course seats
- **Advantages**:
    - First In, First Out behavior ensures proper waitlist ordering
    - O(1) insertion and removal


### `deque` Usage

#### Activity Log
```cpp
deque<ActivityLogEntry> activityLog; // In UniversitySystem class
```
- **Purpose**: Track all system activities
- **Advantages**:
    - O(1) insertion at both ends
    - Efficient access to the front for recent activities

### `pair` Usage

#### Search Results
```cpp
pair<bool, string> searchStudentByName(const string& name) const;
pair<bool, string> searchCourseByTitle(const string& title) const;
```
- **Purpose**: Return structured search results
- **Advantages**:
- Combines success status with result data
- Clear interface for error handling
