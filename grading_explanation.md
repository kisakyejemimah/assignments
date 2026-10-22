# Grading Multiple-Choice Questions

## 1. What the program does

It grades a multiple-choice test for **8 students** answering **10
questions**. Each student's answers are stored in a table (a 2D
array), the correct answers are stored in a separate list (a 1D
array), and the program compares each student's row against that
answer key, counting how many they got right, then prints each
student's score.

Running it produces:

```
Student 0's correct count is 7
Student 1's correct count is 6
Student 2's correct count is 5
Student 3's correct count is 4
Student 4's correct count is 8
Student 5's correct count is 7
Student 6's correct count is 7
Student 7's correct count is 7
```

---

## 2. OOP concepts used — an honest note

Like the credit-card program, this is written in a **purely
procedural** style — one `main()` function, no classes, no objects.
It is a good example of **array-based data organisation**, but it
does **not** demonstrate object-oriented programming as written. If
your assignment specifically asks you to show OOP concepts, this
program would need restructuring — for example:

```cpp
class ExamGrader {
private:
    char answers[8][10]; // encapsulated: hidden from outside code
    char key[10];

public:
    ExamGrader(/* constructor to load answers + key */);
    int gradeStudent(int studentIndex); // public interface
};
```

That would demonstrate:
- **Encapsulation** — the answer arrays become private data, only
  reachable through the class's own methods.
- **Abstraction** — calling `gradeStudent(3)` hides *how* grading
  happens behind one clean function call.
- **Information hiding** — outside code can't directly poke at or
  corrupt the raw arrays; it must go through the public interface.

As submitted, none of that is present — worth flagging to your
lecturer/group if the brief explicitly requires class-based OOP
rather than array/function-based procedural code.

---

## 3. The algorithm, step by step

This is a classic **nested-loop comparison** pattern:

1. **Set up the data.** Store all students' answers in a 2D array
   `answers[student][question]`, and the correct answers in a 1D
   array `key[question]`.
2. **Loop over every student** (outer loop, 0 to 7).
3. **For each student, reset a counter** (`correctCount = 0`) — this
   must happen *inside* the outer loop so each student starts fresh.
4. **Loop over every question** for that student (inner loop, 0 to 9).
5. **Compare** `answers[student][question]` to `key[question]`. If
   they match, increment `correctCount`.
6. **After the inner loop finishes**, print that student's total —
   this print statement sits *outside* the inner loop but *inside*
   the outer loop, so it runs once per student, not once per question.

This is essentially a **linear search / tally pattern** repeated once
per row of a 2D array — one of the most common building blocks in
introductory programming.

---

## 4. Line-by-line walkthrough

```cpp
#include <iostream>
using namespace std;
```
Brings in input/output tools (`cout`) and lets us skip writing `std::`
everywhere.

```cpp
const int NUM_STUDENTS = 8;
const int NUM_QUESTIONS = 10;
```
Named constants instead of "magic numbers" — if the class size or
test length changes later, you edit these two lines instead of
hunting through the whole file for stray `8`s and `10`s.

```cpp
char answers[NUM_STUDENTS][NUM_QUESTIONS] = { ... };
```
A **2D array**: think of it as a grid with 8 rows (one per student)
and 10 columns (one per question). `answers[2][5]` means "student 2's
answer to question 5". Each entry is a `char` holding a letter grade
like `'A'`.

```cpp
char key[NUM_QUESTIONS] = {'D', 'B', 'D', 'C', 'C', 'D', 'A', 'E', 'A', 'D'};
```
A **1D array** holding the correct answer for each of the 10
questions — `key[0]` is the answer to question 0, and so on.

```cpp
for (int student = 0; student < NUM_STUDENTS; student++) {
```
Outer loop: runs once for each of the 8 students, `student` taking
values 0 through 7.

```cpp
    int correctCount = 0;
```
A fresh counter for **this student only**. Declared inside the outer
loop so it resets to 0 before grading each new student.

```cpp
    for (int question = 0; question < NUM_QUESTIONS; question++) {
```
Inner loop: runs once for each of the 10 questions, for the current
student.

```cpp
        if (answers[student][question] == key[question]) {
            correctCount++;
        }
    }
```
The actual grading logic: compare this student's answer to this
question against the correct answer. If they're equal, add 1 to the
running total. `correctCount++` is shorthand for
`correctCount = correctCount + 1`.

```cpp
    cout << "Student " << student << "'s correct count is "
         << correctCount << endl;
}
```
After the inner loop has checked all 10 questions for this student,
print their final score. This line is indented to be *inside* the
outer loop but *outside* the inner loop — that placement is critical
(see Section 5).

```cpp
return 0;
```
Signals to the operating system that the program finished without
errors.

---

## 5. Common mistakes / error points to watch for

- **Misplacing the `cout` line.** If it's accidentally indented one
  level deeper (inside the inner loop), the program prints a running
  total after *every question* instead of once per student — 80 lines
  of output instead of 8.
- **Forgetting to reset `correctCount`.** If `int correctCount = 0;`
  is moved outside the outer loop (declared once, before all
  students), the count keeps accumulating across students instead of
  restarting — student 1's score would include student 0's correct
  answers too.
- **Swapping the loop bounds.** Using `NUM_QUESTIONS` in the outer
  loop and `NUM_STUDENTS` in the inner loop (or mixing up `student`
  and `question` as array indices) causes an **out-of-bounds array
  access** — reading memory that doesn't belong to the array, which is
  undefined behaviour and can crash or silently corrupt data.
- **Off-by-one errors.** Using `<=` instead of `<` in either loop
  condition (e.g. `student <= NUM_STUDENTS`) reads one row/column past
  the end of the array — again undefined behaviour, since valid
  indices only go from 0 to size−1.
- **Case sensitivity.** `'A' == 'a'` is `false` in C++ — if a
  student's answers were ever entered in lowercase while the key uses
  uppercase (or vice versa), every comparison would silently fail even
  though the "answer" is conceptually correct.
- **Mismatched array/key sizes.** If a new question is added to
  `key[]` but `NUM_QUESTIONS` isn't updated (or vice versa), the
  program either loses data (some questions never get checked) or
  reads garbage memory beyond the array's actual size.
- **Confusing rows and columns.** `answers[student][question]` and
  `answers[question][student]` compile equally fine but mean
  completely different things — swapping them silently produces wrong
  (but plausible-looking) results rather than an error.

---

