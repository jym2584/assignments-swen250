/*
 * Skeleton implementation for the activity to parse and print
 * CSV formatted files read from standard input.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv.h"
#include "unit_tests.h"


/*
 * Returns true iff the character 'ch' ends a field. That is, ch is end of file,
 * a comma, or a newline.
 */

bool is_end_of_field(int ch) {
	return (ch == ',') || (ch == '\n') || (ch == EOF) ;
}

/*
 * Return the minimum of two inegers.
 */

int min(int x, int y) {
	return x < y ? x : y ;
}

/*
 * Read the next field from standard input. Returns the value of getchar() that
 * stopped (terminated) the field.
 */

int get_field(f_string field) {
	int ch;
	int i = 0;
	
	for (ch = getchar(); ch != EOF; ch = getchar()) {
		field[i] = ch; // Adds the character to the field array
		if (is_end_of_field(ch)) {
			field[i++] = '\0'; // Adds the terminator to the array
			//printf("fields[%i] %s\n", i, field);
			return ch; // returns the comma, newline or EOF

		} else {
			i++; // increment to the next letter
		}

	}

	return ch; // if anything else hasn't been found
}

/*
 * Read in a CSV line. No error checking is done on the number of fields or
 * the size of any one field.
 * On return, the fields have been filled in (and properly NUL-terminated), and
 * nfields is the count of the number of valid fields.
 * nfields == 0 means end of file was encountered.
 */

csv_line get_line() {
	csv_line csv_struct; // initializes fields
	csv_struct.nfields = 0;
		// if get_field is the new line stopping at the newline \n or EOF
	int ch;
	bool is_false = false; // While we haven't found our newline
	while (is_false == false) {
		ch = get_field(csv_struct.field[csv_struct.nfields]);
		printf("%s\n", csv_struct.field[csv_struct.nfields]);
		//printf("%d \n", csv_struct.nfields);
		if (ch == ',' || ch == '\n') { // If the returned characters on the arrays resulted in a comma or new line, it becomes a valid field
			csv_struct.nfields++;
		}
		if (ch == '\n' || ch == EOF) {
			is_false = true; // Once the newline or EOF is hit, the 2d array is returned based on that row
			return csv_struct;
		}
	}
	csv_struct.nfields = 0;
	return csv_struct;
}

/*
 * Print a CSV line, associating the header fields with the
 * data line fields.
 * The minimum of the number of fields in the header and the data
 * determines how many fields are printed.
 */

void print_csv(csv_line header, csv_line data) {
	//printf("header%d   data%d\n", header.nfields, data.nfields);
	int num = min(header.nfields, data.nfields); // Grabs the header fields to parse on data if there are more arrays on data than header
	int i = 0;
	if(data.nfields == 0) { // If there are no fields, we shouldn't parse through it
		return;
	}

	for (i = 0; i < num; i++) {
		printf("%s = %s\n", header.field[i], data.field[i]);
	}
}

/*
 * Driver - read a CSV line for the header then read and print data lines
 * until end of file.
 */

int main( int argc, char *argv[] ) {
	csv_line header ;
	csv_line current ;

	// LLK additional if statement to execute unit tests if program
	// name contains "test".
	if ( strstr( argv[0], "test" ) )
		return test() ;

	header = get_line() ;
	current = get_line() ;
	printf(header[1]);

		while ( current.nfields > 0 ) {
			//printf("%d", current.nfields);
			print_csv(header, current) ;
			current = get_line();
		}

	return 0 ;
}
