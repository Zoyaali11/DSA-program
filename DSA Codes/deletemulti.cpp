#include <iostream>
#include <string>

using namespace std;

struct Course {
    int CNO;
    Course* next;
};

struct Student {
    int ID;
    string name;
    Student* next;
    Course* enrolledCourses;
};

Course* Cstart = nullptr;
Student* Sstart = nullptr;

void insertCourse(int cno) {
    Course* newCourse = new Course;
    newCourse->CNO = cno;
    newCourse->next = Cstart;
    Cstart = newCourse;
}

void insertStudent(int id, string name) {
    Student* newStudent = new Student;
    newStudent->ID = id;
    newStudent->name = name;
    newStudent->next = Sstart;
    newStudent->enrolledCourses = nullptr;
    Sstart = newStudent;
}

void enrollStudentInCourse(int studentID, int courseCNO) {
    Student* student = Sstart;
    Course* course = Cstart;

    while (student != nullptr && student->ID != studentID) {
        student = student->next;
    }

    while (course != nullptr && course->CNO != courseCNO) {
        course = course->next;
    }

    if (student != nullptr && course != nullptr) {
        // Enroll the student in the course and the course in the student
        Course* enrolledCourse = new Course;
        enrolledCourse->CNO = course->CNO;
        enrolledCourse->next = student->enrolledCourses;
        student->enrolledCourses = enrolledCourse;
    }
}

void deleteStudent(int id) {
    Student* current = Sstart;
    Student* previous = nullptr;

    while (current != nullptr && current->ID != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Student with ID " << id << " not found." << endl;
        return;
    }

    // Remove the student from the list
    if (previous != nullptr) {
        previous->next = current->next;
    } else {
        Sstart = current->next;
    }

    // Deallocate memory for the student and their enrolled courses
    while (current->enrolledCourses != nullptr) {
        Course* temp = current->enrolledCourses;
        current->enrolledCourses = current->enrolledCourses->next;
        delete temp;
    }

    delete current;
}

void deleteCourse(int cno) {
    Course* current = Cstart;
    Course* previous = nullptr;

    while (current != nullptr && current->CNO != cno) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Course with CNO " << cno << " not found." << endl;
        return;
    }

    // Remove the course from the list
    if (previous != nullptr) {
        previous->next = current->next;
    } else {
        Cstart = current->next;
    }

    delete current;
}

void printStudents() {
    Student* student = Sstart;
    while (student != nullptr) {
        cout << "Student ID: " << student->ID << ", Name: " << student->name << ", Enrolled Courses: ";
        Course* course = student->enrolledCourses;
        while (course != nullptr) {
            cout << course->CNO << " ";
            course = course->next;
        }
        cout << endl;
        student = student->next;
    }
}

int main() {
    insertCourse(101);
    insertCourse(102);
    insertCourse(103);

    insertStudent(1, "Feriha");
    insertStudent(2, "Hayat");
    insertStudent(3, "Areeba");

    enrollStudentInCourse(1, 101);
    enrollStudentInCourse(1, 102);
    enrollStudentInCourse(2, 102);
    enrollStudentInCourse(2, 103);
    enrollStudentInCourse(3, 101);

    cout << "Student Info:" << endl;
    printStudents();

    // Delete a student with ID 2
    deleteStudent(2);

    // Delete a course with CNO 102
    deleteCourse(102);

    cout << "\nAfter Deletion:\n";
    printStudents();

    return 0;
}
