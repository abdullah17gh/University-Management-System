# University-Management-System
# 🎓 University Student Management System (C Language)

A comprehensive **console-based Student Management System** developed in **C programming language**. This project is designed to manage student records, courses, attendance, and academic performance efficiently using file handling.

---

## 📌 Features

### 👨‍🎓 Student Management

* Add new student records (auto-generated roll numbers)
* View all students in tabular format
* Search students by:

  * Roll Number
  * Name
* Update existing student information
* Soft delete (mark inactive instead of permanent deletion)

---

### 📚 Course Management

* Add new courses
* Display all available courses
* Manage course details like:

  * Course Code
  * Credit Hours
  * Instructor

---

### 📝 Attendance System

* Mark attendance (Present/Absent)
* Store attendance in file (`attendance.txt`)
* View attendance records
* Calculate attendance percentage

---

### 📊 Marks & Grading System

* Enter student marks:

  * Midterm
  * Final
  * Sessional
* Automatic grade calculation (A, B+, B, etc.)
* Store marks in file (`marks.txt`)
* View marks per student

---

### 🧾 Report Card Generation

* Generate detailed report cards including:

  * Student information
  * Course-wise performance
  * Total marks and grades
  * Semester average
  * CGPA

---

### 💾 File Handling

* Persistent storage using binary file:

  * `student_records.dat`
* Separate text files for:

  * Attendance
  * Marks
* Automatic load/save functionality

---

## 🛠️ Technologies Used

* **C Programming Language**
* Standard Libraries:

  * `stdio.h`
  * `stdlib.h`
  * `string.h`
  * `conio.h`

---

## ⚙️ How to Run

1. Compile the code:

```bash
gcc main.c -o sms
```

2. Run the program:

```bash
./sms
```

> 💡 Note: Works best on Windows due to `conio.h` and `system("cls")`.

---

## 📂 File Structure

```
📁 Project Folder
 ┣ 📄 main.c
 ┣ 📄 student_records.dat
 ┣ 📄 attendance.txt
 ┣ 📄 marks.txt
```

---

## 🚀 Future Improvements

* GUI-based interface (using C++/Java/Python)
* Database integration (MySQL / SQL Server)
* Login & authentication system
* Course enrollment limits
* Better validation and error handling

---

## 👨‍💻 Author

**Abdullah**

---

## ⭐ Contribution

Feel free to fork, improve, and submit pull requests!

---

## 📜 License

This project is open-source and free to use for educational purposes.
