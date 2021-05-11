/***
 * Functions for the DMV customer scheduling and service application.
 * Implementation file.
 ***/

#include <stdlib.h>
#include "dmv_schedule.h"

/*
 * Actual definition of the line array of service lines.
 */
struct service_line line[NLINES] ;

/*
 * Initialize the service lines so that (a) line[0] has priority 'A'
 * through line[2] having priority 'C' and (b) there are no customers
 * in any line.
 * NOTES: As usual, an empty list is signified by a NULL pointer.
 */
void init_service_lines() {
	line[0].priority = 'A';
	line[0].head_of_line = NULL;

	line[1].priority = 'B';
	line[1].head_of_line = NULL;

	line[2].priority = 'C';
	line[2].head_of_line = NULL;
}

/*
 * Return the next ticket number.
 * 	The first customer gets ticket number 1.
 *	The number increases by 1 on each call.
 * Local (static) int ticket holds the current ticket value.
 */
static int ticket = 1 ;
int next_ticket() {
	return ticket++;	// Placeholder for your code.
}

/*
 * A new customer arrives with the given <priority> and
 * <ticket_number>. The customer is placed at the end of
 * the appropriate service line.
 */
void new_customer(char priority, int ticket_number) {
	/* Initialize new customer struct */
	struct customer *new_customer = malloc(sizeof(struct customer));
	new_customer->ticket_number = ticket_number;
	new_customer->next_customer = NULL;

	/* Placing customer on the priority line */
	int priority_index = (int)priority - 65;
	struct customer *service_line = line[priority_index].head_of_line; 

	if(service_line == NULL) { // If there is nothing on the node
		line[priority_index].head_of_line = new_customer;
	
	} else { // traverse through node to put new customer on the line
		while (service_line -> next_customer != NULL) { // go to the end of the node
			service_line = service_line -> next_customer;
		}

		service_line -> next_customer = new_customer; // put the new customer at the tail of the node

	}

}

/*
 * Return the ticket number of the first customer in the
 * line for <priority> after removing the customer from the
 * associated service_line.
 *
 * Return NO_CUSTOMER if there are no customers in the indicated line.
 */
int serve_customer(char priority) {
	int priority_index = (int)priority - 65;
	
	if (line[priority_index].head_of_line == NULL) {
		return NO_CUSTOMER;
	
	} else {
		/* Getting the customer's ticket number */
		struct customer *get_customer_from_head = line[priority_index].head_of_line;
		int ticket_number = get_customer_from_head->ticket_number;
				
		/* Removing the customer from the line */
		get_customer_from_head = NULL;
		free(get_customer_from_head);

		/* Move the next customer in front of the line */
		line[priority_index].head_of_line = line[priority_index].head_of_line->next_customer;

		return ticket_number;
	}
}


/*
 * Return the ticket number of the first customer in the highest
 * priority line that has customers after removing the customer
 * from the line. 'A' is highest priority and 'C' is lowest.
 *
 * Return NO_CUSTOMER if there are no customers in any of the lines.
 *
 * Example: if there are 0 customers in the 'A' line, 3 customers in the 'B'
 *          line and 2 customers in the 'C' line, then the first customer in
 *          the 'B' line would be removed and his/her ticket number returned.
 */
int serve_highest_priority_customer() {
	if (customer_count('A') > 0) { // A has priority
		return serve_customer('A');
	}
	else if (customer_count('B') > 0) {
		return serve_customer('B');
	}
	else if (customer_count('C') > 0) {
		return serve_customer('C');
	}

	return NO_CUSTOMER;
}


/*
 * Return the number of customers in the service line for <priority>
 */
int customer_count(char priority) {
	int priority_index = (int)priority - 65;
	struct customer *service_line = line[priority_index].head_of_line; 

	int count = 0;
	while(service_line != NULL) { // traverse through the node (service line)
		service_line = service_line->next_customer;
		count++;
	}

	return count; // Placeholder for your code.
}


/*
 * Return the number of customers in all service lines.
 */
int customer_count_all() {
	return customer_count('A') + customer_count('B') + customer_count('C'); // Placeholder for your code.
}
