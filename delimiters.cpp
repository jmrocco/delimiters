//Juliette Rocco
//September 28th 2019
//Project 1: Matching Delimiters

#include <iostream>
#include <cassert>
#include "project_1.hpp"

//function declarations

int main();
void print_program();
bool does_delimiter_match(char del);
bool do_delimiters_nest();

//main function that calls the other functions

int main() {
	print_program();
	std::cout << does_delimiter_match('(') << std::endl;
	std::cout << does_delimiter_match('[') << std::endl;
	std::cout << does_delimiter_match('{') << std::endl;
	std::cout << do_delimiters_nest() << std::endl;

	return 0;
}

//function to print the file out
void print_program() {

	//starts reading the file
	ece150::start_reading_file();

	//until the end of the file, print each character
	//to the screen
	while (ece150::at_eof() != true) {
		std::cout << ece150::get_next_character();
	}

}

//checks to see if all the delimiters are matched
bool does_delimiter_match(char del) {
	//local variables for the counter
	// the closing bracket and the current character
	int count { 0 };
	char closing_bracket { };
	char current_char { };

	//i created a return value because it was not
	//returning false if it only had an unmatched case
	//it was only returning false for missing
	bool return_value { true };

	//checks to make sure the right delimiters were sent in
	if (del != '(' && del != '[' && del != '{') {

		return false;
	}

	//assigns the type of closing bracket
	// to look out for
	if (del == '(') {
		closing_bracket = ')';
	} else if (del == '{') {
		closing_bracket = '}';
	} else {
		closing_bracket = ']';
	}

	//starts reading the file
	ece150::start_reading_file();

	do {
		//assigns the current character
		current_char = ece150::get_next_character();

		//if its an opening delimiter
		//add to the count
		if (current_char == del) {
			count += 1;
		}

		//if it finds a closing bracket
		if (current_char == closing_bracket) {

			//and there are no opening brackets print unmatched
			if (count == 0) {
				std::cout << "Unmatched " << current_char << std::endl;

				//makes sure the return value is false
				//in the case that there is only unmatched and not missing
				return_value = false;
			}

			//subtract from the count if there are
			//opening brackets needing a closing bracket
			else {
				count -= 1;
			}
		}

	}
	//ends the loop when it is the end of the file
	while (ece150::at_eof() != true);

	//if there are opening brackets not matched
	if (count > 0) {

		//print missing and then loop to
		//print the number of missing closing
		//brackets
		std::cout << "Missing ";
		for (int k { 0 }; k < count; ++k) {
			std::cout << closing_bracket;
		}
		//return false to indicate there were
		//unmatched or missing brackets
		std::cout << std::endl;
		return false;
	}
	//return true if the file was clean and there
	//was nothing missing
	return return_value;

}

bool do_delimiters_nest() {
	//local variables
	char current_char { };
	char opener { };

	//i created a return value because it was not
	//returning false if it only had an unmatched case
	//it was only returning false for missing
	bool return_type { true };

	//initializes the table and starts reading
	//the file
	ece150::initialize_table();

	ece150::start_reading_file();

	do {
		current_char = ece150::get_next_character();

		//if it is an opening bracket it will place it in the table
		if (current_char == '{' || current_char == '[' || current_char == '(') {

			ece150::place_character(current_char);
		}

		//if it is a closing bracket...
		if (current_char == '}' || current_char == ']' || current_char == ')') {

			//determines what the matching opening bracket is for
			//the closing bracket found
			if (current_char == '}') {
				opener = '{';
			} else if (current_char == ']') {
				opener = '[';
			} else {
				opener = '(';
			}

			//if the right most character in the table
			//matches the opening bracket that is needed
			if (ece150::get_right_most_character() == opener) {

				//the right most character is deleted because it
				//was successfully nested
				ece150::erase_right_most_character();
			}

			//the right most character was not matched with the
			//closing bracket so the closing bracket is unmatched
			else {
				std::cout << "Unmatched " << current_char << std::endl;
				//makes sure the return value is false
				//in the case that there is only unmatched and not missing
				return_type = false;
			}
		}

	}
	//only loop till the end of the document
	while (ece150::at_eof() != true);

	//if the table is not empty
	if (ece150::is_table_empty() != true) {
		//create variables for opening and closing
		//bracket

		char closing_bracket { };
		char opening_bracket { };

		//print the missing statement
		std::cout << "Missing ";

		//while the table is empty...
		while (ece150::is_table_empty() != true) {

			//get the opening bracket from the table
			opening_bracket = ece150::get_right_most_character();

			//determine the closing bracket needed
			// to match the opening bracket
			if (opening_bracket == '(') {
				closing_bracket = ')';
			} else if (opening_bracket == '{') {
				closing_bracket = '}';
			} else {
				closing_bracket = ']';
			}
			//print the desired closing bracket
			//erase the right most character and loop
			std::cout << closing_bracket;
			ece150::erase_right_most_character();
		}
		//end the line after the loop is finished
		std::cout << std::endl;

		//return false because the file was not nested properly
		return false;
	}
	//return true because the file was nested properly
	return return_type;

}
