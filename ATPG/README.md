Implementation of an ATPG using PODEM algorithm

The project folder contains the following:

1. Document
	Problem Statement
	Assumptions
	I/O description
	
2. Code and Demo
	C++ code- testvector.cpp
	
How to get started:

1) Run the testvector.cpp code and enter your netlist. You can refer to example netlist below or in document
Netlist:
6 OR 0 1
7 AND 2 3
8 NOT 7
9 OR 4 5
9 NOT 10
13 OR 11 12
14 AND 10 13
-1 end

2) Enter the observable/output node

3)Enter the required fault node and fault value

References:

1.Sachin Dhingra : Implementation of ATPG Using PODEM Algorithm
2. tutorialspoint.com   (Python reference)
