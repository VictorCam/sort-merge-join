# sort-merge-join algorithms
 sort merge join algorithms for CS440

## To compile main3.cpp:
---
- g++ -std=c++11 main3.cpp
- ./a.out

## To compile main4.cpp: 
---
- g++ -std=c++11 main4.cpp
- ./a.out 

## Description of Assignment:
---

main3.cpp) Sort-merge Join Algorithms: Consider the following relations:
Dept (did (integer), dname (string), budget (double), managerid (integer))
Emp (eid (integer), ename (string), age (integer), salary (double))
Fields of types integer, double, and string occupy 4, 8, and 40 bytes, respectively. Each block can
fit at most one tuple of an input relation. There are at most 22 blocks available to the join
algorithm in the main memory. Implement the optimized sort-merge join algorithm for
Dept ./Dept.managerid=Emp.eid Emp in C++.

- Each input relation is stored in a separate CSV file, i.e., each tuple is in a separate line and
fields of each record are separated by commas.
- The result of the join must be stored in a new CSV file. The files that store relations Dept
and Emp are Dept.csv and Emp.csv, respectively.
- Your program must assume that the input files are in the current working directory, i.e., the
one from which your program is running.
- The program must store the result in a new CSV file with the name join.csv in the current
working directory.

---
    
main4.cpp) External Memory Sorting: Consider the following relation:
Emp (eid (integer), ename (string), age (integer), salary (double))
Fields of types integer, double, and string occupy 4, 8, and 40 bytes, respectively. Each block can
fit at most one tuple of an input relation. There are at most 22 blocks available to the sort
algorithm in the main memory. Implement the multi-pass multi-way sorting for the relation Emp
in C++. The sorting should be based on the attribute ’eid’.

- The input relation is stored in a CSV file, i.e., each tuple is in a separate line and fields of
each record are separated by commas.
- The result of the sort must be stored in a new CSV file. The file that stores the relation
Emp are Emp.csv.

- Your program must assume that the input file is in the current working directory, i.e., the
one from which your program is running.
- The program must store the result in a new CSV file with the name EmpSorted.csv in the
current working directory.