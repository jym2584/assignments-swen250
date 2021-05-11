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
 * Room event information
 * 	Total number of events that have been logged
 * 	Index of the newest event (if any)
 * 	Index of the oldest event (if any)
 * 	Buffer of (up to) MAX_EVENTS most recent events
 */
struct room_t {
	int event_count ;
	int newest ;
	int oldest ;
	struct event_t buffer[MAX_EVENTS] ;
} ;

/*
 * Rooms being monitored.
 */
#define MAX_ROOMS (5)
static struct room_t rooms[MAX_ROOMS] ;

/*
 * Local support functions (static).
 * Feel free to add more to make your work easier!
 */
static void process_a_reading(struct reading_t reading) ;
static void init_rooms() ; 

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
 */



int main()
{
	char next_line[MAX_LINELENGTH+1] ;
	struct reading_t *reading ;

	init_rooms() ;
	/*
	 * Read a line of text into next_line, then attempt to parse
	 * it as a reading line. If the line is parsable, process it according to the
	 * specification for the appropriate level.
	 * See hs_util.h for useful utility functions
	 */
	/* Your code here */

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
 * T_PRINT readings are really commands; once executed they are discarded.
 * For all other readings check to see whether an alert should be printed,
 * then add the event as the newest event in the room's circular buffer.
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
	}
}

/*
 * Initialize the information on all rooms so that no rooms
 * have any events associated with them.
 */
static void init_rooms()
{
	int room_id ;

	/*
	 * Initialize rooms array so that all rooms have no
	 * events associated with them.
	 */

	for( room_id = 0 ; room_id < MAX_ROOMS ; room_id++ ) {
		rooms[room_id].event_count = 0 ;
		rooms[room_id].newest = 0 ;
		rooms[room_id].oldest = 0 ;
	}
}

//Add helper functions here

/**
 * Adds the events to the rooms based on the given reading
 * I would make this a bit more readable but I can't seem to use:
 * 		struct room_t room = rooms[reading.room_id]; // grabbing room ID from reading
 * for some reason. I can recall having issues with the struct not updating whenever I set or increment something.
 * 
 * @param reading struct based on standard input
 * 
 */
static void add_event(struct reading_t reading) {
	rooms[reading.room_id].event_count++; // increment the event count

	if (rooms[reading.room_id].newest != (MAX_ROOMS-1)) { // Increment the index of newest, assuming the array hasn't already been filled
		rooms[reading.room_id].newest = rooms[reading.room_id].event_count - 1; // Set newest to count - 1

	} else { // Prevent incrementing the 'index' of newest if the array is already filled

		/**
		*	'Shifts' every element to the left before adding the new element
		*	Eg: [4, 5, 6, 7, 8]
		*	want to add 10
		*	
		*	After result: [5, 6, 7, 8, 10]
		*/
		for(int i = 0; i < MAX_ROOMS - 1; i++) {
			rooms[reading.room_id].buffer[i] = rooms[reading.room_id].buffer[i+1];
		}

	}

	rooms[reading.room_id].buffer[rooms[reading.room_id].newest] = reading.event; // Adds the latest event to the array

	if(rooms[reading.room_id].buffer[rooms[reading.room_id].newest].event_id == T_INTRUDER) { // If the event ID is Intruder
		rooms[reading.room_id].buffer[rooms[reading.room_id].newest].event_info = 0; // Set the event info to 0 because there is no additional event information to share
	}

	/* Debugging */
	//struct room_t room = rooms[reading.room_id]; // grabbing room ID from reading
	//printf("Room %d (Event Count: %d)\n", reading.room_id, room.event_count);
	//printf("   - Sensor: %d\n   - Timestamp: %s\n   - Event info (if applicable) %d\n", room.buffer[room.newest].sensor, room.buffer[room.newest].time_stamp, room.buffer[room.newest].event_info);
	//printf("   - First Index: %d\n   - Latest: %d\n", room.oldest, room.newest);
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

/**
 * Prints out the current events 
 * @param reading takes in the current line and reads from taht
 */
static void print_reading(struct reading_t reading) {
	printf("*****\nHome Security System: Room %d @ %s\n", reading.room_id, reading.event.time_stamp);
	printf("Triggered by sensor %d\n", reading.event.sensor);
	printf("%d total room events\n", rooms[reading.room_id].event_count);

	for(int i = rooms[reading.room_id].newest; i >= rooms[reading.room_id].oldest; i--) { // Printing each event from newest to oldest
		read_event(rooms[reading.room_id].buffer[i], rooms[reading.room_id].buffer[i].event_id);
	}

}