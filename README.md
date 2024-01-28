# grade-system
## Introduction
The system tracks the exercise points for a course. The course has six exercise rounds, for which points are tracked. For each student registered to the course, the system is required to store 
- Student number, which is a string that can contain at most 6 characters.
- First name, which is a string that can have arbitrary length.
- Last name, which is a string that can have arbitrary length.

## How to use the system
If some part of this guide is denoted as "...", please switch to the code view to see full content.

The system works by command line in terminal in the form of <command> <argument-1> <argument-2> ... <new-line>. 
The commands are:
1. Add student command, which add a new student to the database. Initially the student has 0 points for all exercises.
- Format: A <student-number> <surname> <name>
- Example: A 234567 Jones Jack

2. Update points command, which updates the exercise round points of a student.
- Format: U <student-number> <round> <points>
- Example: U 234567 2 6

3. Print database command, which displays the database content.
- Format: L
- Output: <student-number> <surname> <name> <exercise-1> ... <exercise-6> <total-points>

4. Save to file command, which saves the database to a text file.
- Format: W <filename>
- Output: <student-number> <surname> <name> <exercise-1> ... <exercise-6> <total-points>

5. Load from file command, which loads students from a text file saved using Save to file command. It assumes the stored students are on a separate line in the format specified above.
- Format: O <filename>

6. Quit program command, which releases all allocated memory and exits the program.
- Format: Q

## Credit
This project is developed under the guidance and as part of the course ELEC-A7100 Basic course in C programming: 2023 Spring.
