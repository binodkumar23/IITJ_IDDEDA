dpllStressTest.py:
    This File generates a random CNF(conjuctive normal form) as per the no. of literals and no. of clauses given by the User(which is displayed) and then solves the CNF by the DPLL agorithm.
The DPLL function returns two things:
(i) True/False based on CNF is satisfiable or not respectively.
(ii) if satisfiable:
	The values for which it is satisfiable
     else:
	None

dpllCircuitSolve.py:
    This code asks for an input file(which is needed to be stored in the circuits folder) name that contains the circuit which is needed to be evaluted. 
 Then the user needs to decide if Output literals should have values given by user or some random values. If user decide to give input manually then value for each literal will be asked.
 Then a CNF for the Circuit file is generated and printed. That CNF is then solved by the DPLL algorithm.
 The DPLL function returns two things:
(i) True/False based on CNF is satisfiable or not respectively.
(ii) if satisfiable:
	The values for which it is satisfiable
     else:
	None
	
------------------------------------------------------------------------------------------------

Program written by: Ronak Mohata (B20EE053) and Krishna Mohan (B20EE031)

------------------------------------------------------------------------------------------------

For queries, please contact Binod Kumar (binod@iitj.ac.in)
	
