/* 
 * @brief Implementation of singly linked list 
 * 
 * Allows user to insert (front or back) and remove element
 * Allows user search element and display the link list
 * Allows user reverse the link list
 */

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "LinkList_generic.hpp"

/*
 * main fucntion included:
 * 	bool empty();
 *	void push_back(int elem);
 *	void push_front(int elem);
 *	void erase(int old_elem);
 *	void display();
 *	std::shared_ptr<link> search(int target);
 *	void reverse();
 */

int main() {
	// test for destructor
	{
		link_list::list<std::vector<int>> my_first_list;
		char choice;
		std::vector<int> x;
		std::string s;
		std::string line;

		do {
			std::cout << "\n1. Insert";
			std::cout << "\n2. Delete";
			std::cout << "\n3. Search";
			std::cout << "\n4. Print";
			std::cout << "\n5. Reverse";
			std::cout << "\n0. Exit";
			std::cout << "\n\nEnter you choice : ";
			std::cin >> choice;

			// eatline(), cannot use cin or getline successively
			while (getchar() != '\n') {
				std::cout << "stop" << std::endl;
				continue;
			}

			switch(choice) {
				case '0' : 
					std::cout << "Quitting the program..." << std::endl;
					break;
				case '1' : 
					{
						std::cout << "Enter the insert number(s): ";
						getline(std::cin, line);
						std::istringstream ss(line);

						while (ss >> s) {
							if (link_list::isDigit(s)) {
								auto receive = link_list::parseNum(s);
								x.push_back(receive);
							} else {
								std::cout << "Invalid input!" << std::endl;
							}
						}
						my_first_list.push_back(x);
						break;
					}
				case '2' : 
					{
						std::cout << "Enter the delete number(s): ";
						getline(std::cin, line);
						std::istringstream ss(line);

						while (ss >> s) {
							if (link_list::isDigit(s)) {
								auto receive = link_list::parseNum(s);
								x.push_back(receive);
							} else {
								std::cout << "Invalid input!" << std::endl;
							}
						}
						my_first_list.erase(x);
						break;
					}
				case '3' :
					{
						getline(std::cin, line);
						std::istringstream ss(line);
						std::cout << "Enter the number(s) wanted to search: ";

						while (ss >> s) {
							std::cin >> s;
							if (link_list::isDigit(s)) {
								auto receive = link_list::parseNum(s);
								x.push_back(receive);
							} else {
								std::cout << "Invalid input!" << std::endl;
							}
							my_first_list.search(x);
						}
						break;
					}	
				case '4' : 
					my_first_list.display();
					break;
				case '5' : 
					my_first_list.reverse();
					break;
				default :
					std::cout << "Please enter between 0~5" << std::endl;
					break;
			} 
			x.clear();
		} while (choice != '0');

		std::cout << "Enjoy!" << std::endl;
	}


	return 0;
}