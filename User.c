#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st {
	long int my_msg_type;
	char some_text[BUFSIZ];
};

int main()
{

	int running = 1;				// checks if loop should keep looping or not
	int msgid_from_user;				
	int msgid_from_calc;
	struct my_msg_st some_data_from_user;		
	struct my_msg_st some_data_from_calc;
	long int msg_to_receive = 0;
	char buffer[BUFSIZ];
	bool valid_in = true;				// checks if input is valid or not
	
	msgid_from_user = msgget((key_t)1234, 0666 | IPC_CREAT);
	msgid_from_calc = msgget((key_t)5678, 0666 | IPC_CREAT);

	if (msgid_from_user == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if (msgid_from_calc == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}


	printf("Simple Calculator\n");
	printf("List of commands:\n");
	printf("\tinsert n \t-to insert a number n to the list\n");
	printf("\tdelete n \t-to delete every number n from the list \n");
	printf("\tsum       \t-to get the sum of the numebrs in the list\n");
	printf("\tavg       \t-to get the average of the numbers in the list\n");
	printf("\tmin       \t-to get the smallest number in the list\n");
	printf("\tmid       \t-to get the median value(s) for the set of numbers\n");
	printf("\tend       \t-to exit the program\n");	

	while(running) {
		do {
			printf("Enter command: ");
			fgets(buffer, BUFSIZ, stdin);
			strcpy(some_data_from_user.some_text, buffer);				//store user input to the array of char in message struct
			
			valid_in = true;
			if(strncmp(some_data_from_user.some_text, "insert", 6) == 0) {
				if(some_data_from_user.some_text[7] == '-') {			//if the argument is negative
					if(isdigit(some_data_from_user.some_text[8])) {			// then check if the character after is a digit
						some_data_from_user.my_msg_type = 1;
					}
					else {
						printf("Error: An integer argument must be added for 'insert'.\n");
						valid_in = false;
					}
				}
				else if(isdigit(some_data_from_user.some_text[7])) {		// if the argument is an integer
					some_data_from_user.my_msg_type = 1;
				}
				else {
					printf("Error: An integer argument must be added for 'insert'.\n");
					valid_in = false;
				}
			}
			else if (strncmp(some_data_from_user.some_text, "delete", 6) == 0) {
				if(some_data_from_user.some_text[7] == '-') {			//if the argument is negative
					if(isdigit(some_data_from_user.some_text[8])) {			// then check if the character after is a digit
						some_data_from_user.my_msg_type = 2;
					}
					else {
						printf("Error: An integer argument must be added for 'delete'.\n");
						valid_in = false;
					}
				}
				else if(isdigit(some_data_from_user.some_text[7])) {		//if the argument is an integer
					some_data_from_user.my_msg_type = 2;
				}
				else {
					printf("Error: An integer argument must be added for 'delete'.\n");
					valid_in = false;
				}
			}
			else if (strncmp(some_data_from_user.some_text, "sum", 3) == 0) {
				some_data_from_user.my_msg_type = 3;
			}
			else if (strncmp(some_data_from_user.some_text, "avg", 3) == 0) {
				some_data_from_user.my_msg_type = 4;
			}
			else if (strncmp(some_data_from_user.some_text, "min", 3) == 0) {
				some_data_from_user.my_msg_type = 5;
			}
			else if (strncmp(some_data_from_user.some_text, "mid", 3) == 0) {
				some_data_from_user.my_msg_type = 6;
			}
			else if (strncmp(some_data_from_user.some_text, "end", 3) == 0) {
				some_data_from_user.my_msg_type = 7;
			}
			else {
				some_data_from_user.my_msg_type = 0;
				printf("Error: Please enter a valid command.\n");
				valid_in = false;
			}
		} while (!valid_in);	

		if (msgsnd(msgid_from_user, (void *)&some_data_from_user, MAX_TEXT, 0) == -1) {
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
		if (strncmp(buffer, "end", 3) == 0) {			//if user entered "end"
			running = 0;						// stop loop
		}
		if (running != 0) {					// if keep looping (valid command entered and it is not "end")
			if (msgrcv(msgid_from_calc, (void *)&some_data_from_calc, BUFSIZ, msg_to_receive, 0) == -1) {
				fprintf(stderr, "msgrcv failed with error: &d\n", errno);
				exit(EXIT_FAILURE);
			}
			printf("%s\n", some_data_from_calc.some_text);
		}
	}

	if (msgctl(msgid_from_calc, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}