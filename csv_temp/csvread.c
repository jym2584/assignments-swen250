#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv.h"
#include "unit_tests.h"
bool is_end_of_field(int ch) {
	return (ch == ',') || (ch == '\n') || (ch == EOF) ;
}

int get_field(f_string field) {
	int ch;
	int i = 0;
	
	for (ch = getchar(); ch != EOF; ch = getchar()) {
		field[i] = ch; // Adds the character to the field array
		if (is_end_of_field(ch)) {
			field[i++] = '\0'; // Adds the terminator to the array
			printf("fields[%i] %s\n", i, field);
			return ch; // returns the comma, newline or EOF

		} else {
			i++; // increment to the next letter
		}

	}

	return 0;
}

csv_line get_line() {
	csv_line csv_struct;
	csv_struct.nfields = 0;
		// if get_field is the new line stopping at the newline \n or EOF
	int ch;
	bool isFalse = false; // While we haven't found our newline
	while (isFalse == false) {
		ch = get_field(csv_struct.field[csv_struct.nfields]);
		csv_struct.nfields++;
		printf("%d \n", csv_struct.nfields);
		if (ch == '\n' || ch == EOF) {
			isFalse = true;
			return csv_struct;
		}
	}
	return csv_struct;
}

int main() {
	csv_line csv_struct;
	csv_line current;

	csv_struct.nfields = 0;
	int i = 0;
	int ch;
	csv_line header ;
	header = get_line();
	printf(header.field[0]);
	current = get_line();
	printf("%d\n", current.nfields);

	return 0;

}
