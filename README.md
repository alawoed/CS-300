# CS 300: Data Structures and Algorithms

This repository contains portfolio artifacts from CS 300: Data Structures and Algorithms at Southern New Hampshire University. The projects focused on evaluating data structures, analyzing runtime and memory use, and developing a C++ advising assistance program for ABCU.

## Portfolio Artifacts

- `ProjectOne_Runtime_Analysis.md` — Run-time and memory analysis comparing a vector, hash table, and binary search tree.
- `ProjectTwo.cpp` — Working C++ advising assistance program that loads course data into a binary search tree, prints the course list in alphanumeric order, and displays individual course information and prerequisites.

## Reflection

### What was the problem you were solving in the projects for this course?

The main problem was to design and build an advising assistance program for the Computer Science department at ABCU. The program needed to load course information from a file, store the courses in an appropriate data structure, print the complete course list in alphanumeric order, and allow an advisor to search for a course and view its prerequisites. Project One focused on planning the solution and comparing data structures, while Project Two focused on implementing the final program in C++.

### How did you approach the problem? Consider why data structures are important to understand.

I first compared three possible data structures: a vector, a hash table, and a binary search tree. I considered how each structure would affect loading, searching, ordered output, and memory use. This helped me understand that choosing a data structure should be based on the operations the program needs to perform. I selected a binary search tree because an in-order traversal can produce the course list in alphanumeric order without a separate sorting step, while searches are efficient when the tree is reasonably balanced.

### How did you overcome any roadblocks you encountered while going through the activities or project?

One challenge was validating course data before placing it into the final data structure. A prerequisite can reference a course that appears later in the input file, so validating each prerequisite while reading a single line would not always work. I addressed this by first parsing the courses into a temporary collection, validating that required fields and prerequisite references were correct, and then inserting the validated courses into the binary search tree. I also used helper functions for trimming whitespace and converting course numbers to uppercase, and I tested invalid files, duplicate courses, missing prerequisites, invalid menu choices, and course searches before completing the project.

### How has your work on this project expanded your approach to designing software and developing programs?

This course strengthened the importance of designing the solution before writing the final code. Instead of choosing a structure because it was familiar, I compared its runtime, memory requirements, and behavior against the actual needs of the application. I now think more deliberately about the operations a program will perform most often and how the selected algorithm or data structure will affect performance as the amount of data grows.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I have become more deliberate about separating responsibilities into smaller functions, using descriptive names, documenting important logic, and validating input before changing the main data structure. In Project Two, the binary search tree operations, file parsing, input-cleaning helpers, course-information output, and menu logic are separated instead of being placed in one large function. This makes the program easier to read, test, modify, and reuse.