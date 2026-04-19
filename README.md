# Assignment-4A: Academic Institution Application
### Language: Python 3 | Database: MySQL

---

## Prerequisites

- Python 3.x installed
- MySQL Server running (via MySQL Workbench)
- MySQL database `academic_insti` copy loaded

---

## Step 1 — Load the Database

Open **MySQL Workbench**, connect as root

---

## Step 2 — Install Python Dependency

Open Command Prompt and run:

```
pip install mysql-connector-python
```

---

## Step 3 — Run the Application

```
python acad_insti_app.py
```

You should see:
```
Connected to 'academic_insti_assn' successfully.

    Academic Institution — Main Menu
  1.  Add / Update Course  (Even 2006)
  2.  Enroll Student       (Even 2006)
  3.  Exit
Enter choice [1-3]:
```

---

## Features

### Feature 1 — Add / Update Course (Even Semester, 2006)

Takes the following inputs from the user:


- Department ID
- Course ID 
- Teacher ID
- Classroom 

**Validations performed:**
- Department ID is checked against the `department` table
- Course ID is checked against the `course` table with matching `deptNo`
- Teacher ID is checked against the `professor` table with matching `deptNo`

**Database action:**
- If the record does **not** exist → `INSERT` into `teaching`
- If the record **already exists** → `UPDATE` the classroom

---

### Feature 2 — Enroll Student (Even Semester, 2006)

Takes the following inputs from the user:
- Department ID 
- Student Roll No 
- Course ID 

**Validations performed:**
- Department ID exists in `department` table
- Roll No exists in `student` table
- Course belongs to the given department
- Course is scheduled in `teaching` for Even 2006
- Student is not already enrolled in the same course for Even 2006
- All prerequisite courses must be passed (grade ≠ `U`) in `enrollment`

**Database action:**
- If all checks pass → `INSERT` into `enrollment` with `grade = NULL`

> A student is considered to have **passed** a prerequisite if their grade is anything **except U**.

---

## Sample Test Inputs

### Task 1 — Add Course

```
Enter choice [1-3]: 1
Task 1: Add/Update a course for even semester 2006
Enter Department ID: 9
Department: Comp. Sci.
Enter Course ID: cs635
Course: Algorithms
Enter Teacher(professor) ID: cs07
Teacher: Ramanujam
Enter Classroom: cs25
[Success] Teaching record updated — classroom changed to 'cs25'.
```
---


### Task 2 — Enroll Student (Prerequisites Not Passed)

```
Enter choice [1-3]: 2
  TASK 2 — Student Enrollment  (Even Semester, 2006)
Enter Department ID: 9
Department: Comp. Sci.
Enter Student Roll No: 4S001
Student: Mahesh
Enter Course ID to enroll in: CS630
Course: DL
No prerequisites for this course.

[Success] Student '4S001' enrolled in course 'CS630' for Even 2006.
```

---

### Task 2 — Already Enrolled

```
Enter choice [1-3]: 2
  TASK 2 — Student Enrollment  (Even Semester, 2006)
Enter Department ID: 9
Department: Comp. Sci.
Enter Student Roll No: 7M001
Student: Rakesh
Enter Course ID to enroll in: cs635
Course: Algorithms
[Info] Student is already enrolled in this course for Even 2006.
```

---


## Database Configuration

The connection settings are defined at the top of `acad_insti_app.py`:
> Make sure to change the DB config settings before running the code.
