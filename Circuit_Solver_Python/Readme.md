Project : Solve Digital Circuits using SAT-Solver(DPLL) in python.
Project Done by Aryan Tiwari (B20AI056) and Challa Bhavani Sankar (B20EE014)

The Code is in form of a python notebook (jupyter notebook).
(the raw .py file has also been attached)

Aim: Find the Input literal values for a given circuit with specified output values (such that the corresponding CNF formula of the circuit is satisfiable)

To Run :

1) Have input file of the form given in sample_circuit.txt
2) Run the code
3) Insert the absolute path to the input file when prompted
4) The program will ask if you want to give random values to the output literals. (input 0 for No, 1 for yes)
	-> if 0 is given as input, program then asks if you would like to set all the output literal values to 1. (input 0 for No, 1 for yes)
	-> if 0 is given as input again, program then asks you to individually input the values of the various output literals as you would prefer
5) Based on your inputs, the program gives all the values of input literals that is possible which would result in the preferred output literal values
6) If program outputs "UnSatisfiable", it implies there is no combination of input literals that would result in the given value of output literals.

Note:

The program runs on DPLL algorithm for SAT-Solving.
The program also outputs the CNF (conjunctive normal form) formula of the entire circuit which is given as input by the user.
Further, Program outputs the list of input and output literals, and the list of gates.

General Working:

The program takes the circuit as an Input and converts it into a CNF formula using tseytin transformation.
This CNF is then given to DPLL which provides all possible values of literals that will satisfy the CNF.(The CNF formula is constructed such that it is satisfied only when output literals have the values that were set by the user)
Finally The program extracts the values of the input gates, and prints them as the solution.

-----------------------------------------------------------

For any queries, please write to Binod Kumar (binod@iitj.ac.in)
