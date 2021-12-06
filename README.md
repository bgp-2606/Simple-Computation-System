# Simple-Computation-System
Statistics Computation System Using Message Queues          Version 1.0 11/28/2021
_______________________________________________________________________________________________________________

---------------------------------------------------------------------------------------------------------------
Description
---------------------------------------------------------------------------------------------------------------
	This application implements a calculator-like system using message queues. Two processes will be used:
User(client) and Calculator(server) processes. User sends commands to Calculator, then Calculator stores and
performs operations on numbers.

	This includes files User.c, Calculator.c, nodecalc.h.


---------------------------------------------------------------------------------------------------------------
Limitations
---------------------------------------------------------------------------------------------------------------
	This application only works with positive and negative integers. Other inputs will intitate an 
error statement. That said, float or double inputs are also not allowed in the program.


---------------------------------------------------------------------------------------------------------------
Usage
---------------------------------------------------------------------------------------------------------------
How to compile:
	Using a Linux-based environment, compile the two c files by using the gcc command:
		gcc User.c -o user
		gcc Calculator.c -o calc

How to run:
	To run the program after compilation, open another terminal.
	Then enter this command in one of the terminal:
		./user
	And this in the other:
		./calc

	When the User.c program starts executing, it will prompt the user to enter a command from the list
of commands printed at program startup:
	Simple Calculator
	List of commands:
		insert n	to insert a number n to the list
		delete n 	to delete every number n from the list
		sum       	to get the sum of the numebrs in the list
		avg       	to get the average of the numbers in the list
		min       	to get the smallest number in the list
		mid       	to get the median value(s) for the set of numbers
		end       	to exit the program	
	If the user enters any of the commands listed above, except command 'end', the calculator process sends 
back a message containing the return values of what the commnands asked for. For instance, when user enters 
command 'sum', the user process sends that command to the calculator process. Then after the calculator process 
executes specific operations for the command, it sends back a message to the user process that contains the sum 
of the set of numbers.
	If the user enters the command 'end', both user and calculator processes will be terminated.
	If the user enters an invalid command, error messages will be printed in the user process and the program 
will prompt the user again to enter a valid command.


---------------------------------------------------------------------------------------------------------------
Test cases
---------------------------------------------------------------------------------------------------------------
Test case 1: Inserting all positive integers

	(Inside User process terminal)		||		(Inside Calculator process terminal)
	Enter command: insert 7			||		inserting 7 ..
	7 inserted to the set			||		
	Enter command: sum			||		calculating sum.. 7
	The sum of set is 7			||
	Enter command: insert 13		||		inserting 13 ..
	13 inserted to the set			||		
	Enter command: sum			||		calculating sum.. 20
	The sum of set is 20			||		
	Enter command: avg			||		calculating average.. 10.00
	The average of set is -10.00		||
	

Test case 2: Inserting some negative integers
	(Inside User process terminal)		||		(Inside Calculator process terminal)
	Enter command: insert 7			||		inserting 7 ..
	7 inserted to the set			||
	Enter command: insert -5		||		inserting -5 ..
	-5 inserted to the set			||
	Enter command: insert 24		||		inserting 24 ..
	24 inserted to the set			||	
	Enter command: insert -10		||		inserting -10 ..
	-10 inserted to the set			||
	Enter command: sum			||		calculating sum.. 16
	The sum of set is 16			||	
	Enter command: avg			||		calcalating average.. 4.00
	The average of set is 4.00		||
	Enter command: min			||		getting the min.. -10
	The smallest number in set is -10	||
	Enter command: mid			||		getting the medians.. -5, 7
 	The medians in set are -5, 7		||


Test case 3: Deleting
	(Inside User process terminal)		||		(Inside Calculator process terminal)
	Enter command: insert 7			||		inserting 7 ..
	7 inserted to the set			||
	Enter command: insert -5		||		inserting -5 ..
	-5 inserted to the set			||
	Enter command: insert 24		||		inserting 24 ..
	24 inserted to the set			||	
	Enter command: insert -10		||		inserting -10 ..
	-10 inserted to the set			||
	Enter command: sum			||		calculating sum.. 16
	The sum of set is 16			||	
	Enter command: avg			||		calcalating average.. 4.00
	The average of set is 4.00		||
	Enter command: min			||		getting the min.. -10
	The smallest number in set is -10	||
	Enter command: mid			||		getting the medians.. -5, 7
 	The medians in set are -5, 7		||
	Enter command: insert 7			||		inserting 7..
	7 inserted to the set			||
	Enter command: sum			||		calculating sum.. 23
	The sum of set is 23			||
	Enter command: delete 7			||		deleting all 7 ..
	All 7 deleted from set			||		
	Enter command: sum			||		calculating sum.. 9
	The sum of set is 9			||


Test case 4: Entering an invalid command
	(Inside User process terminal)
	Enter command: max
	Error: Please enter a valid command.
	Enter command:
	Error: Please enter a valid command.
	Enter command: add
	Error: Please enter a valid command.
	Enter command: average
	Error: Please enter a valid command.
	Enter command:

Test case 5: Using command 'insert n' or 'delete n', but with invalid argument
	(Inside User process terminal)
	Enter command: insert	
	Error: An integer argument must be added for 'insert'.
	Enter command: insert y
	Error: An integer argument must be added for 'insert'.
	Enter command: insert -r
	Error: An integer argument must be added for 'insert'.
	Enter command: insert !
	Error: An integer argument must be added for 'insert'.
	Enter command: delete !9
	Error: An integer argument must be added for 'delete'.
	Enter command: delete
	Error: An integer argument must be added for 'delete'.
	Enter command: delete -w
	Error: An integer argument must be added for 'delete'.

Test case 6: Using command 'delete n', 'sum', 'avg', 'min', 'mid' when the set is empty
	(Inside User process terminal)
	Enter command: sum
	Error: Empty set of numbers
	Enter command: avg
	Error: Empty set of numbers
	Enter command: min
	Error: Empty set of numbers
	Enter command: mid
	Error: Empty set of numbers
	Enter command: delete 8
	Error: Empty set of numbers

Test case 7: Using command 'end'
	(Inside User process terminal)		||		(Inside Calculator process terminal)
	Enter command: end			||		The average time: 1400077 usec


---------------------------------------------------------------------------------------------------------------
Credits
---------------------------------------------------------------------------------------------------------------
	Author of User.c, Calculator.c, nodecalc.h files : Bren-Gelyn Padlan
