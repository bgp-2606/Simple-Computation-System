#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include <sys/msg.h>

#include "nodecalc.h"

#define MAX_TEXT 512

struct my_msg_st {
	long int my_msg_type;
	char some_text[BUFSIZ];
};

int main()
{
	int running = 1;
	int msgid_from_user, msgid_from_calc;
	struct my_msg_st some_data_from_user, some_data_from_calc;
	long int msg_to_receive = 0;
	node_t *head = NULL;
	int result_sum, result_min;
	float result_avg;
	int *mid;
	int n;
	int time1, time2, time3, time4, time5, time6, total_time;
	struct timeval start, end;

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
	
	while(running) {
		if (msgrcv(msgid_from_user, (void *)&some_data_from_user, BUFSIZ, msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		switch(some_data_from_user.my_msg_type){
			case 1:
				// insert function
				n = atoi(&some_data_from_user.some_text[7]);
				printf("inserting %d ..\n", n);
				
				gettimeofday(&start, NULL);
				head = insert(head, n);
				gettimeofday(&end, NULL);
	
				time1 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

				sprintf(some_data_from_calc.some_text, "%d inserted to the set", n);
				some_data_from_calc.my_msg_type = 1;
				 
				break;
			case 2:
				// delete function
				if (head == NULL) {
					sprintf(some_data_from_calc.some_text, "Error: Empty set of numbers");
				}
				else {
					n = atoi(&some_data_from_user.some_text[7]);
					printf("deleting all %d ..\n", n);
	
					gettimeofday(&start, NULL);
					head = delete(head, n);
					gettimeofday(&end, NULL);
					time2 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
				
					sprintf(some_data_from_calc.some_text, "All %d deleted from set", n);
				}
				some_data_from_calc.my_msg_type = 2;		
				break;
			case 3:
				// sum function
				if (head == NULL) {
					sprintf(some_data_from_calc.some_text, "Error: Empty set of numbers");
				}
				else {
					gettimeofday(&start, NULL);
					result_sum = sum(head);
					gettimeofday(&end, NULL);
					time3 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

					printf("calculating sum.. %d\n", result_sum);
					sprintf(some_data_from_calc.some_text, "The sum of set is %d", result_sum);
				}
				some_data_from_calc.my_msg_type = 3;				
				break;
			case 4:
				// average function
				if (head == NULL) {
					sprintf(some_data_from_calc.some_text, "Error: Empty set of numbers");
				}
				else {
					gettimeofday(&start, NULL);
					result_avg = average(head);
					gettimeofday(&end, NULL);
					time4 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

					printf("calculating average.. %.2f\n", result_avg);
					sprintf(some_data_from_calc.some_text, "The average of set is %.2f", result_avg);
				}
				some_data_from_calc.my_msg_type = 4;
				break;
			case 5:
				// min function
				if (head == NULL) {
					sprintf(some_data_from_calc.some_text, "Error: Empty set of numbers");
				}
				else {
					gettimeofday(&start, NULL);
					result_min = minimum(head);
					gettimeofday(&end, NULL);
					time5 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

					printf("getting the min.. %d\n",result_min);
					sprintf(some_data_from_calc.some_text, "The smallest number in set is %d", result_min);
				}
				some_data_from_calc.my_msg_type = 5;
				break;
			case 6:
				// mid function
				if (head == NULL) {
					sprintf(some_data_from_calc.some_text, "Error: Empty set of numbers");
				}
				else {
					gettimeofday(&start, NULL);
					mid = median(head);
					gettimeofday(&end, NULL);
	
					time6 = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

					if (mid[1] == 0) {
						printf("getting the median.. %d\n", mid[0]);
						sprintf(some_data_from_calc.some_text, "The median value in set is %d", mid[0]);
					}
					else {
						printf("getting the medians.. %d, %d\n", mid[0], mid[1]);
						sprintf(some_data_from_calc.some_text, "The medians in set are %d, %d", mid[0], mid[1]);
					}
				}
				some_data_from_calc.my_msg_type = 6;
				break;
			case 7:
				//quit
				running = 0;
				break;
			default:
				//NO SUCH COMMAND
				running = 0;
				break;
		}
		
		
		if (running != 0) {
			if (msgsnd(msgid_from_calc, (void *)&some_data_from_calc, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	total_time = time1 + time2 + time3 + time4 + time5 + time6;
	printf("The average time: %d usec\n", total_time/6);

	if (msgctl(msgid_from_user, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}