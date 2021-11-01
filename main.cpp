#include "polynomial.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vld.h>



// Test whether there are any (non-whitespace) characters left in the stream
bool empty(std::istream& in) {
	char c;
	if (in >> c) {
		in.putback(c);
		return false;
	}
	else {
		return true;
	}
}

// Read one polynomial at a time
// Print out each polynomial found
int main() {


	std::string line;
	Polynomial p;
	Polynomial sum;
	//
	// TODO: Initialize p as necessary
	//
	while (std::getline(std::cin, line)) {
		// Make a stream just for this one line
		std::istringstream strIn(line);
		if (!empty(strIn)) {
			strIn >> p;

			if (strIn && empty(strIn)) {

				if (sum == NULL) {
					sum = p;
				}
				else {
					sum = sum + p;
				}

			}
			else {
				std::cerr << "Error: " << line << std::endl;
			}
		}
	}
	std::cout << sum << std::endl;
}