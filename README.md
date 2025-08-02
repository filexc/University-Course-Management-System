# University Course Management System
A C++ application that manages student and course data, handles enrollment operations, and provides administrative tools for university course management. The project demonstrates the
use of Standard Template Library (STL) containers and object-oriented design in a real-world application.

## Compilation & Running

### Prerequisites
- C++17 compatible compiler
- Make (optional, for using Makefile)

### Compilation

#### Using Makefile
```bash
# Compile the program
make

# Run the program
make run

# Clean compiled files
make clean
```

#### Manual Compilation
```bash
g++ -std=c++17 -Wall -o university_system main.cpp Student.cpp Course.cpp UniversitySystem.cpp
```

### Running the Program
```bash
./university_system
```

## STL Containers Used

| Container | Purpose | Location |
|:---------:|:-------:|:--------:|
| `map` | Student and course registries | `UniversitySystem` class |
| `set` | Enrollment Lists | `Student` and `Course` classes |
| `pair` | Search operations and associations | `UniversitySystem` class |
| `queue` | Course Waitlists | `Course` class |
| `deque` | Activity Logs | `UniversitySystem` class |

## Features

### Student Management
- Add, remove, and update student records
- Store student information (`ID`, `name`, `enrolled courses`)

### Course Management
- Add, remove, and update course information
- Store course information (`course code`, `title`, `instructor name`, `enrolled student list`, `capacity`)

### Enrollment Operations
- Enroll & drop students in/from courses
- Prevent duplicate enrollments
- Maintain a waitlist if enrollment exceeds course capacity
- Automatic waitlist management when seats become available

### Administrative Tools
- List all courses a student is enrolled in
- List all students in a specific course
- Activity logging for all operations
- Load data from external files
- Search students by instructor
- Search students by name
- Search courses by title
- Display system statistics

## Usage Guide

### Interactive Menu
The program provides an interactive menu with the following options:

  1. **Add Student** - Add a new student to the system
  2. **Add Course** - Add a new course to the system
  3. **Enroll Student in Course** - Enroll a student in a course
  4. **Drop Student from Course** - Drop a student from a course
  5. **List Student's Courses** - Display all courses a student is enrolled in
  6. **List Course's Students** - Display all students in a course
  7. **Display All Students** - Show all students in the system
  8. **Display All Courses** - Show all courses in the system
  9. **Search Student by Name** - Find a student by their name (displays their student ID)
  10. **Search Course by Title** - Find a course by its title (displays the course code)
  11. **Get Students by Instructor** - List all students taught by an instructor
  12. **Display System Statistics** - Show system overview
  13. **Display Activity Log** - Show all system activities
  14. **Display Recent Activities** - Show recent system activities
  15. **Remove Student** - Remove a student from the system
  16. **Remove Course** - Remove a course from the system
  17. **Update Student** - Update student information
  18. **Update Course** - Update course information
  19. **Load Data from File** - Load data from a text file (can add students, courses, and enroll students in courses)
  20. **Demo Mode (Run all features)** - Run an automated demonstration of program features
  21. **Exit** - Exit the program

### Demo Mode
The demo mode automatically tests system features:
- Adds sample students and courses
- Performs enrollments and creates waitlists
- Tests search operations
- Demonstrates administrative tools
- Shows activity logging

### Loading Data from Files
The system can load data from text files with the following format:
```
# Comments start with #
STUDENT,ID,Full Name
COURSE,Code,Title,Instructor,Capacity
ENROLL,Student ID,Course Code
```

Example:
```
STUDENT,S001,Alice Johnson
COURSE,CS101,Introduction to Computer Science,Dr. Smith,25
ENROLL,S001,CS101
```

## Test Data Files
The system includes four test data files for different scenarios and can all be added in a single execution of the program.

Test files:
- **test_data1.txt**: Basic functionality with 10 students and 10 courses
- **test_data2.txt**: Waitlist testing with a popular course (PHYS501)
- **test_data3.txt**: Advanced waitlist scenarios with more courses
- **test_data4.txt**: Specialized courses with small capacities

## Error Handling
The system includes comprehensive error handling for:
- Invalid input validation
- Duplicate student/course IDs
- Non-existent students or courses
- Enrollment in non-existent courses
- Dropping from non-enrolled courses
- File loading errors

## Team Members and Roles
* Violet Chaffee – Sole Developer
