#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_STUDENTS 500
#define MAX_COURSES 50
#define MAX_NAME_LENGTH 50
#define MAX_DEPT_LENGTH 30
#define FILENAME "student_records.dat"

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    char fatherName[MAX_NAME_LENGTH];
    char department[MAX_DEPT_LENGTH];
    char program[MAX_DEPT_LENGTH];
    int semester;
    struct Date dateOfBirth;
    char phoneNumber[15];
    char email[50];
    char address[100];
    float cgpa;
    int isActive;
};

struct Course {
    int courseCode;
    char courseName[MAX_NAME_LENGTH];
    int creditHours;
    char instructor[MAX_NAME_LENGTH];
    int maxStudents;
    int enrolledStudents;
};

struct Attendance {
    int rollNumber;
    int courseCode;
    struct Date date;
    char status;
};

struct Marks {
    int rollNumber;
    int courseCode;
    float midtermMarks;
    float finalMarks;
    float sessionalMarks;
    float totalMarks;
    char grade[3];
};

struct Student students[MAX_STUDENTS];
struct Course courses[MAX_COURSES];
int studentCount = 0;
int courseCount = 0;
int lastRollNumber = 2024000;

void mainMenu();
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void calculateCGPA();
void manageCourses();
void addCourse();
void displayCourses();
void markAttendance();
void viewAttendance();
void enterMarks();
void viewMarks();
void generateReportCard();
void saveToFile();
void loadFromFile();
void clearScreen();
void pressAnyKey();
int generateRollNumber();
int findStudentByRollNumber(int rollNo);
int isValidPhoneNumber(char *phone);
int isValidEmail(char *email);

int main() {
    loadFromFile();
    
    while(1) {
        mainMenu();
    }
    
    return 0;
}

void mainMenu() {
    int choice;
    
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t     UNIVERSITY STUDENT MANAGEMENT SYSTEM\n");
    printf("\t==========================================\n");
    printf("\n\t1. Add New Student");
    printf("\n\t2. Display All Students");
    printf("\n\t3. Search Student");
    printf("\n\t4. Update Student Record");
    printf("\n\t5. Delete Student Record");
    printf("\n\t6. Calculate/Update CGPA");
    printf("\n\t7. Course Management");
    printf("\n\t8. Mark Attendance");
    printf("\n\t9. View Attendance");
    printf("\n\t10. Enter Marks");
    printf("\n\t11. View Marks");
    printf("\n\t12. Generate Report Card");
    printf("\n\t13. Save & Exit");
    printf("\n\t==========================================\n");
    printf("\n\tEnter your choice (1-13): ");
    
    scanf("%d", &choice);
    
    switch(choice) {
        case 1: addStudent(); break;
        case 2: displayAllStudents(); break;
        case 3: searchStudent(); break;
        case 4: updateStudent(); break;
        case 5: deleteStudent(); break;
        case 6: calculateCGPA(); break;
        case 7: manageCourses(); break;
        case 8: markAttendance(); break;
        case 9: viewAttendance(); break;
        case 10: enterMarks(); break;
        case 11: viewMarks(); break;
        case 12: generateReportCard(); break;
        case 13: 
            saveToFile();
            printf("\n\tThank you for using the system!\n");
            printf("\tData saved successfully. Goodbye!\n");
            exit(0);
        default:
            printf("\n\tInvalid choice! Please try again.");
            pressAnyKey();
    }
}

void addStudent() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t            ADD NEW STUDENT\n");
    printf("\t==========================================\n");
    
    if(studentCount >= MAX_STUDENTS) {
        printf("\n\tCannot add more students. Database full!");
        pressAnyKey();
        return;
    }
    
    struct Student newStudent;
    
    newStudent.rollNumber = generateRollNumber();
    printf("\n\tRoll Number (Auto-generated): %d", newStudent.rollNumber);
    
    printf("\n\tEnter Student Name: ");
    scanf(" %[^\n]", newStudent.name);
    
    printf("\n\tEnter Father's Name: ");
    scanf(" %[^\n]", newStudent.fatherName);
    
    printf("\n\tEnter Department (e.g., CS, EE, ME): ");
    scanf(" %[^\n]", newStudent.department);
    
    printf("\n\tEnter Program (e.g., BS, MS, PhD): ");
    scanf(" %[^\n]", newStudent.program);
    
    printf("\n\tEnter Semester (1-8): ");
    scanf("%d", &newStudent.semester);
    
    printf("\n\tEnter Date of Birth (DD MM YYYY): ");
    scanf("%d %d %d", &newStudent.dateOfBirth.day, 
          &newStudent.dateOfBirth.month, 
          &newStudent.dateOfBirth.year);
    
    do {
        printf("\n\tEnter Phone Number (11 digits): ");
        scanf("%s", newStudent.phoneNumber);
    } while(!isValidPhoneNumber(newStudent.phoneNumber));
    
    do {
        printf("\n\tEnter Email: ");
        scanf("%s", newStudent.email);
    } while(!isValidEmail(newStudent.email));
    
    printf("\n\tEnter Address: ");
    scanf(" %[^\n]", newStudent.address);
    
    newStudent.cgpa = 0.0;
    newStudent.isActive = 1;
    
    students[studentCount] = newStudent;
    studentCount++;
    lastRollNumber = newStudent.rollNumber;
    
    printf("\n\tStudent added successfully!");
    saveToFile();
    pressAnyKey();
}

void displayAllStudents() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         ALL STUDENTS RECORDS\n");
    printf("\t==========================================\n");
    
    if(studentCount == 0) {
        printf("\n\tNo students found in database!");
        pressAnyKey();
        return;
    }
    
    printf("\n\t%-10s %-20s %-15s %-10s %-8s %-10s",
           "Roll No", "Name", "Department", "Program", "Semester", "CGPA");
    printf("\n\t----------------------------------------------------------------\n");
    
    for(int i = 0; i < studentCount; i++) {
        if(students[i].isActive) {
            printf("\n\t%-10d %-20.20s %-15s %-10s %-8d %-10.2f",
                   students[i].rollNumber,
                   students[i].name,
                   students[i].department,
                   students[i].program,
                   students[i].semester,
                   students[i].cgpa);
        }
    }
    
    printf("\n\n\tTotal Active Students: %d", studentCount);
    pressAnyKey();
}

void searchStudent() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t           SEARCH STUDENT\n");
    printf("\t==========================================\n");
    
    int choice;
    printf("\n\t1. Search by Roll Number");
    printf("\n\t2. Search by Name");
    printf("\n\tEnter choice: ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        int rollNo;
        printf("\n\tEnter Roll Number: ");
        scanf("%d", &rollNo);
        
        int index = findStudentByRollNumber(rollNo);
        if(index != -1 && students[index].isActive) {
            printf("\n\tStudent Found!\n");
            printf("\n\tRoll Number: %d", students[index].rollNumber);
            printf("\n\tName: %s", students[index].name);
            printf("\n\tFather's Name: %s", students[index].fatherName);
            printf("\n\tDepartment: %s", students[index].department);
            printf("\n\tProgram: %s", students[index].program);
            printf("\n\tSemester: %d", students[index].semester);
            printf("\n\tDate of Birth: %02d/%02d/%d", 
                   students[index].dateOfBirth.day,
                   students[index].dateOfBirth.month,
                   students[index].dateOfBirth.year);
            printf("\n\tPhone: %s", students[index].phoneNumber);
            printf("\n\tEmail: %s", students[index].email);
            printf("\n\tAddress: %s", students[index].address);
            printf("\n\tCGPA: %.2f", students[index].cgpa);
        } else {
            printf("\n\tStudent not found!");
        }
    } else if(choice == 2) {
        char searchName[MAX_NAME_LENGTH];
        printf("\n\tEnter Name to search: ");
        scanf(" %[^\n]", searchName);
        
        int found = 0;
        for(int i = 0; i < studentCount; i++) {
            if(students[i].isActive && 
               strstr(students[i].name, searchName) != NULL) {
                if(!found) {
                    printf("\n\tMatching Students:\n");
                    found = 1;
                }
                printf("\n\tRoll No: %d, Name: %s, Dept: %s", 
                       students[i].rollNumber,
                       students[i].name,
                       students[i].department);
            }
        }
        
        if(!found) {
            printf("\n\tNo matching students found!");
        }
    }
    
    pressAnyKey();
}

void updateStudent() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         UPDATE STUDENT RECORD\n");
    printf("\t==========================================\n");
    
    int rollNo;
    printf("\n\tEnter Roll Number of student to update: ");
    scanf("%d", &rollNo);
    
    int index = findStudentByRollNumber(rollNo);
    if(index == -1 || !students[index].isActive) {
        printf("\n\tStudent not found!");
        pressAnyKey();
        return;
    }
    
    printf("\n\tUpdating record for: %s", students[index].name);
    printf("\n\tLeave blank to keep existing value\n");
    
    char temp[100];
    
    printf("\n\tEnter new Name [%s]: ", students[index].name);
    scanf(" %[^\n]", temp);
    if(strlen(temp) > 0) {
        strcpy(students[index].name, temp);
    }
    
    printf("\n\tEnter new Phone [%s]: ", students[index].phoneNumber);
    scanf("%s", temp);
    if(strlen(temp) > 0 && isValidPhoneNumber(temp)) {
        strcpy(students[index].phoneNumber, temp);
    }
    
    printf("\n\tEnter new Address [%s]: ", students[index].address);
    scanf(" %[^\n]", temp);
    if(strlen(temp) > 0) {
        strcpy(students[index].address, temp);
    }
    
    printf("\n\tUpdate Semester? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if(choice == 'y' || choice == 'Y') {
        printf("\n\tEnter new Semester: ");
        scanf("%d", &students[index].semester);
    }
    
    printf("\n\tRecord updated successfully!");
    saveToFile();
    pressAnyKey();
}

void deleteStudent() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         DELETE STUDENT RECORD\n");
    printf("\t==========================================\n");
    
    int rollNo;
    printf("\n\tEnter Roll Number of student to delete: ");
    scanf("%d", &rollNo);
    
    int index = findStudentByRollNumber(rollNo);
    if(index == -1 || !students[index].isActive) {
        printf("\n\tStudent not found!");
        pressAnyKey();
        return;
    }
    
    printf("\n\tStudent: %s", students[index].name);
    printf("\n\tAre you sure you want to delete? (y/n): ");
    
    char choice;
    scanf(" %c", &choice);
    
    if(choice == 'y' || choice == 'Y') {
        students[index].isActive = 0;
        printf("\n\tStudent record deleted successfully!");
        saveToFile();
    } else {
        printf("\n\tDeletion cancelled.");
    }
    
    pressAnyKey();
}

void calculateCGPA() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         CALCULATE CGPA\n");
    printf("\t==========================================\n");
    
    int rollNo;
    printf("\n\tEnter Roll Number: ");
    scanf("%d", &rollNo);
    
    int index = findStudentByRollNumber(rollNo);
    if(index == -1 || !students[index].isActive) {
        printf("\n\tStudent not found!");
        pressAnyKey();
        return;
    }
    
    printf("\n\tStudent: %s", students[index].name);
    printf("\n\tCurrent CGPA: %.2f", students[index].cgpa);
    printf("\n\tEnter new CGPA: ");
    scanf("%f", &students[index].cgpa);
    
    printf("\n\tCGPA updated successfully!");
    saveToFile();
    pressAnyKey();
}

void manageCourses() {
    int choice;
    
    do {
        clearScreen();
        printf("\n\t==========================================\n");
        printf("\t         COURSE MANAGEMENT\n");
        printf("\t==========================================\n");
        printf("\n\t1. Add New Course");
        printf("\n\t2. Display All Courses");
        printf("\n\t3. Back to Main Menu");
        printf("\n\tEnter choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addCourse(); break;
            case 2: displayCourses(); break;
            case 3: return;
            default: printf("\n\tInvalid choice!");
        }
    } while(choice != 3);
}

void addCourse() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         ADD NEW COURSE\n");
    printf("\t==========================================\n");
    
    if(courseCount >= MAX_COURSES) {
        printf("\n\tCannot add more courses!");
        pressAnyKey();
        return;
    }
    
    struct Course newCourse;
    
    printf("\n\tEnter Course Code: ");
    scanf("%d", &newCourse.courseCode);
    
    printf("\n\tEnter Course Name: ");
    scanf(" %[^\n]", newCourse.courseName);
    
    printf("\n\tEnter Credit Hours: ");
    scanf("%d", &newCourse.creditHours);
    
    printf("\n\tEnter Instructor Name: ");
    scanf(" %[^\n]", newCourse.instructor);
    
    printf("\n\tEnter Maximum Students: ");
    scanf("%d", &newCourse.maxStudents);
    
    newCourse.enrolledStudents = 0;
    
    courses[courseCount] = newCourse;
    courseCount++;
    
    printf("\n\tCourse added successfully!");
    saveToFile();
    pressAnyKey();
}

void displayCourses() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         ALL COURSES\n");
    printf("\t==========================================\n");
    
    if(courseCount == 0) {
        printf("\n\tNo courses found!");
        pressAnyKey();
        return;
    }
    
    printf("\n\t%-15s %-25s %-10s %-20s %-10s",
           "Course Code", "Course Name", "Credit Hrs", "Instructor", "Enrolled");
    printf("\n\t--------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < courseCount; i++) {
        printf("\n\t%-15d %-25.25s %-10d %-20.20s %-10d",
               courses[i].courseCode,
               courses[i].courseName,
               courses[i].creditHours,
               courses[i].instructor,
               courses[i].enrolledStudents);
    }
    
    pressAnyKey();
}

void markAttendance() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         MARK ATTENDANCE\n");
    printf("\t==========================================\n");
    
    int courseCode;
    printf("\n\tEnter Course Code: ");
    scanf("%d", &courseCode);
    
    int courseIndex = -1;
    for(int i = 0; i < courseCount; i++) {
        if(courses[i].courseCode == courseCode) {
            courseIndex = i;
            break;
        }
    }
    
    if(courseIndex == -1) {
        printf("\n\tCourse not found!");
        pressAnyKey();
        return;
    }
    
    struct Date attDate;
    printf("\n\tEnter Date (DD MM YYYY): ");
    scanf("%d %d %d", &attDate.day, &attDate.month, &attDate.year);
    
    printf("\n\tMarking attendance for %s", courses[courseIndex].courseName);
    printf("\n\tEnter 'P' for Present, 'A' for Absent\n");
    
    FILE *attendanceFile = fopen("attendance.txt", "a");
    if(attendanceFile == NULL) {
        printf("\n\tError opening attendance file!");
        pressAnyKey();
        return;
    }
    
    for(int i = 0; i < studentCount; i++) {
        if(students[i].isActive) {
            printf("\n\t%s (Roll: %d) - P/A: ", 
                   students[i].name, students[i].rollNumber);
            
            char status;
            scanf(" %c", &status);
            
            fprintf(attendanceFile, "%d,%d,%d,%d,%d,%c\n",
                    students[i].rollNumber,
                    courseCode,
                    attDate.day,
                    attDate.month,
                    attDate.year,
                    status);
        }
    }
    
    fclose(attendanceFile);
    printf("\n\tAttendance marked successfully!");
    saveToFile();
    pressAnyKey();
}

void viewAttendance() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         VIEW ATTENDANCE\n");
    printf("\t==========================================\n");
    
    int rollNo, courseCode;
    printf("\n\tEnter Roll Number: ");
    scanf("%d", &rollNo);
    printf("\n\tEnter Course Code: ");
    scanf("%d", &courseCode);
    
    FILE *attendanceFile = fopen("attendance.txt", "r");
    if(attendanceFile == NULL) {
        printf("\n\tNo attendance records found!");
        pressAnyKey();
        return;
    }
    
    char line[100];
    int total = 0, present = 0;
    
    printf("\n\tAttendance Record:\n");
    printf("\n\tDate\t\tStatus");
    printf("\n\t-------------------\n");
    
    while(fgets(line, sizeof(line), attendanceFile)) {
        int r, c, d, m, y;
        char status;
        sscanf(line, "%d,%d,%d,%d,%d,%c", &r, &c, &d, &m, &y, &status);
        
        if(r == rollNo && c == courseCode) {
            printf("\n\t%02d/%02d/%d\t%c", d, m, y, status);
            total++;
            if(status == 'P' || status == 'p') present++;
        }
    }
    
    fclose(attendanceFile);
    
    if(total > 0) {
        float percentage = (float)present/total * 100;
        printf("\n\n\tTotal Classes: %d", total);
        printf("\n\tPresent: %d", present);
        printf("\n\tAbsent: %d", total - present);
        printf("\n\tAttendance Percentage: %.2f%%", percentage);
    } else {
        printf("\n\tNo attendance records found for this student/course!");
    }
    
    pressAnyKey();
}

void enterMarks() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         ENTER MARKS\n");
    printf("\t==========================================\n");
    
    int rollNo, courseCode;
    printf("\n\tEnter Roll Number: ");
    scanf("%d", &rollNo);
    
    int studentIndex = findStudentByRollNumber(rollNo);
    if(studentIndex == -1 || !students[studentIndex].isActive) {
        printf("\n\tStudent not found!");
        pressAnyKey();
        return;
    }
    
    printf("\n\tEnter Course Code: ");
    scanf("%d", &courseCode);
    
    int courseIndex = -1;
    for(int i = 0; i < courseCount; i++) {
        if(courses[i].courseCode == courseCode) {
            courseIndex = i;
            break;
        }
    }
    
    if(courseIndex == -1) {
        printf("\n\tCourse not found!");
        pressAnyKey();
        return;
    }
    
    struct Marks marks;
    marks.rollNumber = rollNo;
    marks.courseCode = courseCode;
    
    printf("\n\tStudent: %s", students[studentIndex].name);
    printf("\n\tCourse: %s", courses[courseIndex].courseName);
    
    printf("\n\n\tEnter Midterm Marks (out of 100): ");
    scanf("%f", &marks.midtermMarks);
    
    printf("\n\tEnter Final Marks (out of 100): ");
    scanf("%f", &marks.finalMarks);
    
    printf("\n\tEnter Sessional Marks (out of 100): ");
    scanf("%f", &marks.sessionalMarks);
    
    marks.totalMarks = marks.midtermMarks + marks.finalMarks + marks.sessionalMarks;
    
    float percentage = marks.totalMarks / 3;
    if(percentage >= 85) strcpy(marks.grade, "A");
    else if(percentage >= 75) strcpy(marks.grade, "B+");
    else if(percentage >= 65) strcpy(marks.grade, "B");
    else if(percentage >= 55) strcpy(marks.grade, "C+");
    else if(percentage >= 50) strcpy(marks.grade, "C");
    else if(percentage >= 40) strcpy(marks.grade, "D");
    else strcpy(marks.grade, "F");
    
    FILE *marksFile = fopen("marks.txt", "a");
    if(marksFile == NULL) {
        printf("\n\tError opening marks file!");
        pressAnyKey();
        return;
    }
    
    fprintf(marksFile, "%d,%d,%.2f,%.2f,%.2f,%.2f,%s\n",
            marks.rollNumber,
            marks.courseCode,
            marks.midtermMarks,
            marks.finalMarks,
            marks.sessionalMarks,
            marks.totalMarks,
            marks.grade);
    
    fclose(marksFile);
    
    printf("\n\tMarks entered successfully!");
    printf("\n\tTotal Marks: %.2f", marks.totalMarks);
    printf("\n\tGrade: %s", marks.grade);
    
    saveToFile();
    pressAnyKey();
}

void viewMarks() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         VIEW MARKS\n");
    printf("\t==========================================\n");
    
    int rollNo;
    printf("\n\tEnter Roll Number: ");
    scanf("%d", &rollNo);
    
    FILE *marksFile = fopen("marks.txt", "r");
    if(marksFile == NULL) {
        printf("\n\tNo marks records found!");
        pressAnyKey();
        return;
    }
    
    char line[100];
    int found = 0;
    
    printf("\n\tMarks Record for Roll No: %d\n", rollNo);
    printf("\n\t%-15s %-10s %-10s %-10s %-10s %s",
           "Course Code", "Midterm", "Final", "Sessional", "Total", "Grade");
    printf("\n\t----------------------------------------------------------------\n");
    
    while(fgets(line, sizeof(line), marksFile)) {
        int r, c;
        float mid, fin, sess, tot;
        char grade[3];
        
        sscanf(line, "%d,%d,%f,%f,%f,%f,%s", 
               &r, &c, &mid, &fin, &sess, &tot, grade);
        
        if(r == rollNo) {
            printf("\n\t%-15d %-10.2f %-10.2f %-10.2f %-10.2f %s",
                   c, mid, fin, sess, tot, grade);
            found = 1;
        }
    }
    
    fclose(marksFile);
    
    if(!found) {
        printf("\n\tNo marks found for this student!");
    }
    
    pressAnyKey();
}

void generateReportCard() {
    clearScreen();
    printf("\n\t==========================================\n");
    printf("\t         GENERATE REPORT CARD\n");
    printf("\t==========================================\n");
    
    int rollNo;
    printf("\n\tEnter Roll Number: ");
    scanf("%d", &rollNo);
    
    int studentIndex = findStudentByRollNumber(rollNo);
    if(studentIndex == -1 || !students[studentIndex].isActive) {
        printf("\n\tStudent not found!");
        pressAnyKey();
        return;
    }
    
    printf("\n\n\t==========================================");
    printf("\n\t           UNIVERSITY REPORT CARD");
    printf("\n\t==========================================");
    
    printf("\n\n\tStudent Name: %s", students[studentIndex].name);
    printf("\n\tFather's Name: %s", students[studentIndex].fatherName);
    printf("\n\tRoll Number: %d", students[studentIndex].rollNumber);
    printf("\n\tDepartment: %s", students[studentIndex].department);
    printf("\n\tProgram: %s", students[studentIndex].program);
    printf("\n\tSemester: %d", students[studentIndex].semester);
    
    FILE *marksFile = fopen("marks.txt", "r");
    if(marksFile != NULL) {
        char line[100];
        printf("\n\n\tCourse-wise Performance:");
        printf("\n\t------------------------------------------------");
        printf("\n\t%-20s %-10s %-10s", "Course", "Total", "Grade");
        printf("\n\t------------------------------------------------");
        
        float semesterTotal = 0;
        int courseCount = 0;
        
        while(fgets(line, sizeof(line), marksFile)) {
            int r, c;
            float mid, fin, sess, tot;
            char grade[3];
            
            sscanf(line, "%d,%d,%f,%f,%f,%f,%s", 
                   &r, &c, &mid, &fin, &sess, &tot, grade);
            
            if(r == rollNo) {
                char courseName[50] = "Unknown";
                for(int i = 0; i < courseCount; i++) {
                    if(courses[i].courseCode == c) {
                        strcpy(courseName, courses[i].courseName);
                        break;
                    }
                }
                
                printf("\n\t%-20.20s %-10.2f %-10s", 
                       courseName, tot, grade);
                
                semesterTotal += tot;
                courseCount++;
            }
        }
        
        fclose(marksFile);
        
        if(courseCount > 0) {
            float semesterAvg = semesterTotal / courseCount;
            printf("\n\t------------------------------------------------");
            printf("\n\tSemester Average: %.2f", semesterAvg);
            printf("\n\tCGPA: %.2f", students[studentIndex].cgpa);
        }
    }
    
    printf("\n\n\t==========================================");
    printf("\n\t      *** End of Report Card ***");
    printf("\n\t==========================================");
    
    pressAnyKey();
}

int generateRollNumber() {
    return ++lastRollNumber;
}

int findStudentByRollNumber(int rollNo) {
    for(int i = 0; i < studentCount; i++) {
        if(students[i].rollNumber == rollNo) {
            return i;
        }
    }
    return -1;
}

int isValidPhoneNumber(char *phone) {
    int len = strlen(phone);
    if(len != 11) return 0;
    
    for(int i = 0; i < len; i++) {
        if(phone[i] < '0' || phone[i] > '9') return 0;
    }
    return 1;
}

int isValidEmail(char *email) {
    int atSymbol = 0;
    int dot = 0;
    int len = strlen(email);
    
    for(int i = 0; i < len; i++) {
        if(email[i] == '@') atSymbol = i;
        if(email[i] == '.') dot = i;
    }
    
    return (atSymbol > 0 && dot > atSymbol + 1 && dot < len - 1);
}

void saveToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if(file == NULL) {
        printf("\n\tError saving data!");
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), studentCount, file);
    
    fwrite(&courseCount, sizeof(int), 1, file);
    fwrite(courses, sizeof(struct Course), courseCount, file);
    
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if(file == NULL) {
        return;
    }
    
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), studentCount, file);
    
    fread(&courseCount, sizeof(int), 1, file);
    fread(courses, sizeof(struct Course), courseCount, file);
    
    if(studentCount > 0) {
        lastRollNumber = students[studentCount-1].rollNumber;
    }
    
    fclose(file);
}

void clearScreen() {
    system("cls");
}

void pressAnyKey() {
    printf("\n\n\tPress any key to continue...");
    getch();
}