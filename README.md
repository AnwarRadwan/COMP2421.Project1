# Polynomial Abstract Data Type (ADT)

## 📌 Description
This project implements a Polynomial Abstract Data Type (ADT) using Linked Lists and Stack data structures in C. It supports polynomial arithmetic operations such as addition, subtraction, and multiplication. The project also includes file input/output handling and a menu-driven interface for user interaction.

---

## 🧠 Data Structures Used
- Singly Linked List (to represent each polynomial term)
- Stack (to store multiple polynomials and process them in pairs)

---

## ✨ Features
- Load polynomials from a file
- Store polynomials in a stack
- Display all polynomials
- Perform polynomial operations:
  - Addition (+)
  - Subtraction (-)
  - Multiplication (*)
- Display results on screen
- Save results to output file
- Interactive menu system

---

## 📥 Input Format
Each line in the input file represents a polynomial.

### Example:
3x^5-2x^3+x^2+4
-x^2-3x^4
8x^2-9

---

## ⚙️ How It Works
- Polynomials are parsed from the input file
- Each polynomial is stored as a linked list
- All polynomials are pushed into a stack
- Operations are performed in pairs:
  - Example: (q op r) → x, then (p op x)

---

## 🖥️ Menu Options
1. Load the polynomials’ file  
2. Print the polynomials  
3. Add the polynomials  
4. Subtract the polynomials  
5. Multiply the polynomials  
6. Print the results to the screen  
7. Print the results to file  
8. Exit  

---

## 🛠️ How to Compile & Run
```bash
gcc main.c stack.c linkedlist.c polynomial.c -o polynomial
./polynomial
