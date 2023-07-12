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
#include "LinkList.hpp"

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
	link_list::list my_first_list;
	int choice = 0;
	int x = 0;
	std::string s;

	do {
		std::cout << "\n1. Insert";
		std::cout << "\n2. Delete";
		std::cout << "\n3. Search";
		std::cout << "\n4. Print";
		std::cout << "\n5. Reverse";
		std::cout << "\n0. Exit";
		std::cout << "\n\nEnter you choice : ";
		std::cin >> choice;

		switch(choice) {
			case 0 : 
				std::cout << "Quitting the program..." << std::endl;
				break;
			case 1 : 
				std::cout << "Enter the insert number: ";
				std::cin >> s;
				if (link_list::isDigit(s)) {
					x = std::stoi(s);
					my_first_list.push_back(x);
				} else {
					std::cout << "Invalid input!" << std::endl;
				}
				break;
			case 2 :
				std::cout << "Enter the delete number: ";
				std::cin >> s;
				if (link_list::isDigit(s)) {
					x = std::stoi(s);
					my_first_list.erase(x);
				} else {
					std::cout << "Invalid input!" << std::endl;
				}
				break;
			case 3 :
				std::cout << "Enter the number wanted to search: ";
				std::cin >> s;
				if (link_list::isDigit(s)) {
					x = std::stoi(s);
					my_first_list.search(x);
				} else {
					std::cout << "Invalid input!" << std::endl;
				}
				break;
			case 4 : 
				my_first_list.display();
				break;
			case 5 : 
				my_first_list.reverse();
				break;
			default :
				std::cout << "Please enter between 0~5" << std::endl;
				break;
		} 
	} while (choice != 0);

	std::cout << "Enjoy!" << std::endl;
	return 0;
}