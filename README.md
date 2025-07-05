# Sudoku-Solution-Checker
Input text document 9x9 grid of sudoku solution to check. Program uses multithreading with mutex to check solution properly. If solution invalid, it tells you what's wrong with it. 

To compile my program please use the provided makefile by using the make command. 

To run my program use ./mssv <solution.txt> <delay 1-10> where you can choose between 4 different solutions, 1 and 2 are valid, 3 and 4 are invalid. The delay can be between 1 and 10. i.e. "./mssv solution1.txt 1". 

Provided solution.txt and solution2.txt are valid, solution3.txt and solution4.txt are invalid. 

Example of solution3.txt

![picture](https://github.com/user-attachments/assets/d4953c99-a431-4d4e-85b2-74b082006485)


