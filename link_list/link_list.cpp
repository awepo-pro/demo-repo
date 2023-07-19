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
#include <string>
#include <vector>
#include "link_list.hpp"

/*
 * T_type -> any built-in type, not container

 * initialize included:
 * 		link_list();
 *		link_list(initiliazer_list<T_type> s)   
 * 		link_list(vector<T_type> s)  			(support std::move())
 *      link_list(link_list<T_type> base) 		(support std::move())
 *		
 *		assignment: void operator=(const link_list<T_type> base)
 * 
 * main fucntion included:
 * 	 time complexity O(1):
 *		bool empty();
 * 		size_t size();
 * 
 *		void push_back(T_type elem);
 * 		void push_back_range(vector<T_type> serveral_elem)	(support std::move())
 * 		void push_back_range(initializer_list<T_type s)
 *
 *		void push_front(T_type elem);
 * 		void push_back_range(vector<T_type> serveral_elem)	(support std::move())
 * 		void push_back_range(initializer_list<T_type s)
 *
 *		void pop_front();
 *		void pop_back();
 *	
 *
 * 	 time complexity O(n):
 * 		void erase(T_type old_elem);
 *  	void display(string sentence);			(support std::move())
 *		ptr_val search(T_type target);
 *		void reverse();
 *		void insert(int pos, T_type elem);
 *
 *	time complexity O(nlogn) - O(n^2):
 * 		void sort()
 * 		void unique()				// require sort() first
 */

int main() {
	std::vector<int> a {2, 3, 1, 2, 4, 5, 2, 6, 10};
	data_structures::link_list<int> A(std::move(a));
	A.display(std::move("tree A: "));

	auto t = A.front_val();

	std::cout << t << std::endl;

	A.unique();
	A.display();

	return 0;
}