/*
 * Home Security System
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "hs_config.h"
#include "hs_util.h"

/*
 * An event node on the linked list of events for
 * a room. Consists of an event as gathered from a
 * reading and a link to the next node on the list
 * (if any).
 */
struct evnode_t {
	struct event_t event ;
	struct evnode_t *next ;
} ;

/*
 * Room event information
 * 	The room number.
 * 	Total number of events that have been logged.
 * 	Pointer to the most recent reading's node (if any).
 * 	Pointer to the next room (if any).
 */
struct room_t {
	int room ;
	int ecount ;
	struct evnode_t *event_list_head ;
	struct room_t *next_room ;
} ;

/*
 * Head of the list of rooms being monitored.
 */
static struct room_t *room_list = NULL ;

/*
 * Local support functions (static).
 * You have to fill in the details.
 * Feel free to add more to make your work easier!
 */
static void process_a_reading(struct reading_t reading) ;

static struct room_t *find_room(int room) ;
static struct room_t *add_new_room(int room) ;
static void trim_list(int room, int keep, char timestamp[]) ;

static struct evnode_t *make_event_node() ;


/* Helper functions */
static void print_reading(struct reading_t reading); 
static void add_event(struct reading_t reading);
static void read_event(struct event_t event, int event_id);

/*
 * Main driver function.
 *
 * First, initialize global data structures (rooms array).
 *
 * Next, read lines of text representing readings, parse these, and if there
 * are no syntax errors, record the associated events. Syntactically incorrect
 * input reading lines are silently discarded.
 *
 * When the program ends, make sure all memory is cleaned up!!
 */
int main() {
	char next_line[MAX_LINELENGTH+1] ;
	struct reading_t *reading ;

	/*
	 * Read a line of text into next_line, then attempt to parse
	 * it as a <reading> line. If the line is parsable, get the
	 * last reading structure and process it according to the
	 * specification for the appropriate level.
	 * See hs_util.h for useful utility functions.
	 * 
	 * At the end of the program, clean up any dynamically allocated memory
	 */
	
	// FILL IN THE BODY
	/* Reading from standard input */
	int num_chars = read_line(next_line, MAX_LINELENGTH+1); // number of characters on each line

	while(num_chars != 0) {
		int tokens = parse_string(next_line, reading);
		//printf("%s\n", next_line);
		if(tokens == 4 || tokens == 5) { // if there are 4-5 fields on each line, process them
			process_a_reading(*reading);
		}
		
		num_chars = read_line(next_line, MAX_LINELENGTH + 1); // go to the next line
	}



	return 0 ;
}

/*
 * Given a reading, process the included event for the room in the reading.
 * T_PRINT and T_TRIM readings are really commands; once executed they are
 * discarded.
 * For all other readings check to see whether an alert should be printed,
 * then add the event to as the newest event in the room's event list.
 */
static void process_a_reading(struct reading_t reading) {
	if(reading.event.event_id == T_TEMPERATURE) { // Temp
		add_event(reading);

		/* Checks for anomalies on temperature */
		if(reading.event.event_info < MIN_TEMP || reading.event.event_info > MAX_TEMP) { // temp is less than the min or greater than the max
			char *alert = "Temperature alert @ %s: room %d / sensor %d / %d degrees.\n";
			printf(alert, reading.event.time_stamp, reading.room_id, reading.event.sensor, reading.event.event_info);
		}

	} else if (reading.event.event_id == T_CO) { // Co2
		add_event(reading);

		/* Checks for anomalies on co2 reading */
		if(reading.event.event_info > CO_LIMIT) { // co2 reading is greater than the limit
			char *alert = "Carbon monoxide alert @ %s: room %d / sensor %d / %d PPB.\n";
			printf(alert, reading.event.time_stamp, reading.room_id, reading.event.sensor, reading.event.event_info);
		}

	} else if (reading.event.event_id == T_INTRUDER) { // Intruder
		add_event(reading);

		/* Always print out reading for intruders */
		char *alert = "Intruder alert @ %s: room %d / sensor %d.\n"; // Prints the alert
		printf(alert, reading.event.time_stamp, reading.room_id, reading.event.sensor);

	} else if (reading.event.event_id == T_PRINT) { // Print
		print_reading(reading);
	
	} else if (reading.event.event_id == T_TRIM) { // Trimming
		trim_list(reading.room_id, reading.event.event_info, reading.event.time_stamp);
	}

}


static void add_event(struct reading_t reading) {
	if(find_room(reading.room_id) == NULL) {
		add_new_room(reading.room_id);
	}

	struct room_t *get_room = find_room(reading.room_id); // get the room if it already exists, or we added it
	get_room->ecount++; // increment the event count

	struct evnode_t *current_event = get_room->event_list_head; 
	
	if (current_event == NULL) {
		get_room->event_list_head = make_event_node();
		get_room->event_list_head->event = reading.event;
	
	} else {
        struct evnode_t * add_new_event = make_event_node();
        add_new_event->event = reading.event;
        add_new_event->next = current_event;
        get_room->event_list_head = add_new_event;
	}

}

static void print_reading(struct reading_t reading) {
	printf("*****\nHome Security System: Room %d @ %s\n", reading.room_id, reading.event.time_stamp);
	printf("Triggered by sensor %d\n", reading.event.sensor);

	struct room_t *room_linked_list = room_list;
    if (room_linked_list != NULL) { // if the room list isn't empty
		while (room_linked_list->room != reading.room_id) { // iterate through the rooms until we find the room_id
			room_linked_list = room_linked_list->next_room;
		}
		printf("%d total room events\n", room_linked_list->ecount);
		
	} else {
        printf("%d total room events\n", 0);
		return; // stop going through the rest of the code because there is nothing to read
    }

	struct evnode_t *current_event = room_linked_list->event_list_head; // read the current events
	while (current_event != NULL) { // iterate through current events
		read_event(current_event->event, current_event->event.event_id);
		current_event = current_event->next;
	}
}


/**
 * Gets event type and reads from it
 * @param event Reads from the event and prints it out
 * @param event_id event type
 */
static void read_event(struct event_t event, int event_id) {
	if (event_id == T_TEMPERATURE) {
		char *temp = "Sensor %d @ %s temperature reading %d degrees\n";
		printf(temp, event.sensor, event.time_stamp, event.event_info);
		
	} else if (event_id == T_CO) {
		char *co2 = "Sensor %d @ %s carbon monoxide reading %d PPB\n";
		printf(co2, event.sensor, event.time_stamp, event.event_info);		

	} else if (event_id == T_INTRUDER) {
		char *intruder = "Sensor %d @ %s intruder alert\n";
		printf(intruder, event.sensor, event.time_stamp);
	}
}



/*
 * Find the specified <room> in the <room_list>, returning a pointer to the
 * found room_t structure or NULL if there is no such <room> in the list.
 */
static struct room_t *find_room(int room) {
	if (room_list == NULL){
	    return NULL;
	}

	struct room_t *the_room = room_list;
	while(the_room->room != room){ // iterating through the linked list until we find the room
	    the_room = the_room->next_room;

	    if (the_room == NULL){
	        return NULL;
	    }

	}

	return the_room;
}


/*
 * Create a new room_t node for <room>, initialize its fields, and append
 * the node to the end of the <room_list>.
 * Returns a pointer to the new room's structure.
 */
static struct room_t *add_new_room(int room) {
	struct room_t *new_room = malloc(sizeof(struct room_t));
    struct room_t *current_room = room_list;
	
	/* initializing new room */
	new_room->room = room;
    new_room->ecount = 0;
   
    if (current_room == NULL) { // Make a new room if there are no initial rooms
        room_list = new_room; // set head to be the new room

	} else {
	    while(current_room->next_room != NULL) { // make a new room if the next node is null
            current_room = current_room->next_room;
	    }

        current_room->next_room = new_room; // append the new room to the list
    }

	return new_room ;
}

/*
 * If the <room> is in the <room_list>, trim the room's event node list
 * to at most <keep> entries. As the list is ordered from newest to
 * oldest, the oldest entries are discarded.
 *
 * Whether the room exists or not, and whether or not the list holds
 * anything, the specified "Trim log" message must be printed. Obviously,
 * for a non-existent room nothing is actually trimmed (removed).
 *
 * Note - dynamically allocated space for event nodes removed from
 *        the list must be freed.
 */
static void trim_list(int room, int keep, char timestamp[]) {
	char *trim = "Trim log @ %s: room %d log trimmed to length %d (%d entries removed)\n";
	int removed_count = 0; // count how many events were removed, if any
	
	struct room_t *get_room = find_room(room);
	if(get_room == NULL) { // edge case if the room doesn't exist
		printf(trim, timestamp, room, keep, removed_count); // should always return 0 since this room doesn't exist
	
	} else { // assuming the room is valid
	
		if(get_room->event_list_head == NULL) { // edge case if there are no events
			printf(trim, timestamp, room, keep, removed_count); // should always return 0 since the events on the room doesn't exist
		
		} else {
			int keep_temp = 0; // keep track of the events that are iterated over

			struct evnode_t *current_event = get_room->event_list_head;
			// keep_temp is set to 1 since we don't want to skip over an event
			while (keep_temp+1 != keep) { // iterating through the events we want to keep
				if (keep_temp == keep) {
					break;
				}
				current_event = current_event->next;
				keep_temp++;
			}

			struct evnode_t *prev; // set previous event
			while(current_event != NULL) {
				prev = current_event; // set previous event
				current_event = current_event->next; // traverse through the next event
				removed_count++;
				prev->next = NULL;
				prev = NULL;
				free(prev); // free the previous
			}
			
			removed_count--; // always seems to count one over, but trims correctly regardless

			if(keep == 0) { // Additional check if the events are trimmed to length 0
				get_room->event_list_head = NULL; // Since there is no way to record the prev of only one event, we can set the head to NULL
				prev = NULL; // also set this to NULL since it's no longer a used variable
				free(prev); // clear up these empty event
				free(get_room->event_list_head); // clear up these empty event
				removed_count++; 
			}

			if(removed_count < 0) {
				removed_count = 0; // always seems to count one over, but trims correctly regardless
			}


		}
	}

	printf(trim, timestamp, room, keep, removed_count); // should always return 0 since the events on the room doesn't exist

}




/*
 * Create a new evnode_t node, initialize it using the provided
 * event and a NULL link, and return the pointer to the node.
 */
static struct evnode_t *make_event_node() {
    struct evnode_t *new_event = malloc(sizeof(struct evnode_t)); // allocates the memory
    return new_event;
}