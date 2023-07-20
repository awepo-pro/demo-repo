
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
#include "link_list_user.hpp"

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
 * 		void push_front_range(vector<T_type> serveral_elem)	(support std::move())
 * 		void push_front_range(initializer_list<T_type s)
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
 * 		void unique()				// require sort() first
 *
 *	time complexity O(nlogn) - O(n^2):
 * 		void sort()
 */

int main() {
    std::cout << "initialize listA and push some elements in it" << std::endl;

    data_structures::link_list<double> listA;
    listA.push_back(1.2);
    listA.push_back(4.5);
    listA.push_back(3.4);
    listA.push_back(40.2234);
    listA.display("listA constains: ");

    std::cout << std::endl << "delete elements in listA " << std::endl;
    listA.pop_back();
    listA.pop_back();
    listA.display();

    std::cout << "the size of listA: ----------------------------------" << listA.size() << std::endl;
    
    std::cout << "clear listA" << std::endl;
    listA.clear();
    listA.display();

    std::cout << "---------------------------------------" << std::endl 
              << std::endl;

    std::vector<int> integer_vector = {4, 3, 4, 5, 6, 2, 6, 7};
    std::cout << "convert a vector into singly linked list" << std::endl;
	data_structures::link_list<int> integer_list(integer_vector);
    integer_list.display();

    std::cout << "insert a branch of elements in integer_list " << std::endl;
    integer_list.push_back_range({10, 11, 23, 4, 55, 100});
    integer_list.display("integer_list contains: ");
    // std::move()
    std::vector<int> integer_vector_B = {100, 200, 200, 200, 500, 600};
    integer_list.push_back_range(std::move(integer_vector_B));
    integer_list.display("integer_list contains: ");

    std::cout << "remove duplicated element" << std::endl;
    integer_list.unique();
    integer_list.display("integer_list contains: "); 
    std::cout << "sort and unique" << std::endl;
    integer_list.sort();
    integer_list.unique();
    integer_list.display("integer_list contains: ");

    std::cout << "insert elements at front:" << std::endl;
    integer_list.push_front(100);
    integer_list.push_front(200);
    integer_list.push_front_range({4, 5, 6, 7});
    integer_list.display("integer_list contains: ");

    std::cout << "remove elements from front and back" << std::endl;
    integer_list.pop_front();
    integer_list.pop_back();
    integer_list.display("integer_list contains: ");
    integer_list.pop_front();
    integer_list.pop_front();
    integer_list.display(std::move("integer_list contains: "));

    std::cout << "remove specific elements" << std::endl;
    integer_list.erase(100);
    integer_list.erase(200);
    integer_list.erase(3);
    integer_list.display(std::move("integer_list contains: "));

    std::cout << "sort link list" << std::endl;
    integer_list.sort();
    integer_list.display();

    std::cout << "search elements in link list" << std::endl;
    if (integer_list.search(200) == nullptr)
        std::cout << "200 is not in link list" << std::endl;
    else
        std::cout << "found 200 !" << std::endl;


    std::cout << "clear integer_list" << std::endl
              << "----------------------------------------" << std::endl
              << std::endl;
    integer_list.clear();
    std::cout << integer_list << std::endl;

	return 0;
}
