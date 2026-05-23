# Student Information System

A robust and fully dynamic Student Information System built with C. This project demonstrates advanced memory management, data structures, and file operations.

## 🚀 Key Features

* **Dynamic Memory Allocation:** Completely eliminates static arrays. Uses `malloc` and `free` for efficient memory management, including precise dynamic string allocation for student names.
* **Linked List Architecture:** Student records are managed via a singly linked list, allowing for automatic sorted insertions (by Student ID) without any hardcoded capacity limits.
* **Binary File Serialization:** Safely saves and loads complex struct data (including dynamic pointers) to a binary `.dat` file, ensuring complete data persistence across sessions.
* **Memory Leak Protection:** Implements strict memory cleanup routines (`freeList` and double-free logic) to return all allocated heap memory to the OS before termination.

## 🛠️ How to Compile and Run

1. Open your terminal.
2. Compile the code using GCC:
   ```bash
   gcc Student_Information_System.c -o student_system
   
3. Run the game:
   ```bash
   ./hangman
