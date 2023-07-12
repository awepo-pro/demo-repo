/*
 * the element deleted by itself, vector<int> destructor is called out of contral
 */
#include <iostream>
#include <vector>
#include "LinkList_generic.hpp"

int main() {
	{
		link_list::list<std::vector<int>, std::vector<std::vector<int>>> my_list;

		std::vector<std::vector<int>> p (1, std::vector<int>(5, 1));
		std::vector<std::vector<int>> d (1, std::vector<int>(5, 2));
		std::vector<std::vector<int>> e (1, std::vector<int>(5, 3));
		std::vector<std::vector<int>> f (1, std::vector<int>(5, 9));

		
		my_list.push_back(p);
		my_list.insert(11, d);
		my_list.insert(1, e);
		my_list.push_back(f);
		// my_list.push_back(std::vector<std::vector<int>>(1, std::vector<int>(5, 8)));
		my_list.display();

	}
	return 0;
}