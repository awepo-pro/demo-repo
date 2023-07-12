/* 
 * @brief Implementation of singly linked list 
 * 
 * It is a container-like class use to emulate link list
 * it only provides method, slight functions. 
 * All pointers are prohibited and unenouranges
 * 
 * The greatest effort applied is storing container into link list
 * but most of the method work for vector<> (ofz all the built-in type)
 * 
 * In the begining, it is thought to be a linked list like forward_list
 * as more method offered, it is more like deque<> but not doubly link list
 * worst time complexity O(n), space complexity O(1)
 */

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "LinkList_generic.hpp"

/*
 * main fucntion included:
 * 	 time complexity O(1) 
 *		bool empty();
 *		void push_back(T_container elem);
 *		void push_front(T_container elem);
 *		void pop_front();
 *		void pop_back();
 *
 * 	 time complexity O(n)
 * 		void erase(T_container old_elem);
 *  	void display();
 *		ptr_val search(T_container target);
 *		void reverse();
 *		void insert(int pos, T_container elem);
 */

int main() {
	// test for destructor
	{
		link_list::list<int, std::vector<int>> my_first_list;
		char choice;
		std::vector<int> x;
		std::string s;
		std::string line;

		do {
			std::cout << "\n1. Insert"
					  << "\n2. Delete"
					  << "\n3. Search"
					  << "\n4. Print"
					  << "\n5. Reverse"
					  << "\n6. pop front"
					  << "\n7. pop back"
					  << "\n0. Exit"
					  << "\n\nEnter you choice : ";
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
						if (my_first_list.empty()) {
							std::cout << "The list is empty!" << std::endl;
							break;
						}
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
						std::cout << "Enter the number(s) wanted to search: ";
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
						my_first_list.search(x);
						break;
					}	
				case '4' :
					my_first_list.display();
					break;
				case '5' : 
					my_first_list.reverse();
					my_first_list.display();
					break;
				case '6' :
					my_first_list.pop_front();
					my_first_list.display();
					break;
				case '7' : 
					my_first_list.pop_back();
					my_first_list.display();
					break;
				case '8' :
					{
						std::cout << "Enter the position and value wanted to add: ";
						getline(std::cin, line);
						std::istringstream ss(line);
						int N, A; 
						ss >> N;
						while (ss >> A) {
							x.push_back(A);
						}
						my_first_list.insert(N, x);
					}
				default :
					std::cout << "Please enter between 0~7" << std::endl;
					break;
			} 
			x.clear();
		} while (choice != '0');

		std::cout << "Enjoy!" << std::endl;
	}


	return 0;
}