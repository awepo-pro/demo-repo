#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <vector>
#include <queue>
#include <ostream>

namespace link_list {

	/*
	 * overload operator<< shows that the constructor and destructor can print out vector
	 * can't use as friend function since the argument is not the class, but the vector
	 */
	template<typename T_type>
	std::ostream &operator<<(std::ostream &os, std::vector<T_type> p) {
		if (p.empty())
			os << "the container is empty";

		for (const auto x : p)
			os << x << ' ';
		return os;
	}

	template<typename T_type>
	bool operator!=(std::vector<T_type> &a, std::vector<T_type> &b) {
		int m = a.size();
		int n = b.size();

		if (m != n)
			return true;

		for (int i = 0; i < m; i++) {
			if (a[i] != b[i]) {
				return true;
			}
		}
		return false;
	}

	/*
	 * function check if the constent of string represents digit or not
	 */
	bool isDigit(const std::string &s) {
		for (const auto c : s) {
			if (!std::isdigit(c) && c != '.') {
				return false;
			}
		}
		return true;
	}

	/*
	 * fucntion converts user input from string to floating number or integer
	 * for floating number, return double type; for integer return long type
	 */
	long parseNum(const std::string &s) {
		double ret = 0;
		bool flg = false;
		for (const char c : s) {
			if (c == '.') {
				flg = true;
			}
			ret = ret * 10 + (c - '0');
		}
		return flg ? ret : (long) ret;
	}

	/*
	 * contains the method of Node list using `class Node` as Node
	 * T_type are the value type of the node of Node list, it can be container too
	 */
	template<typename T_type>
	class list {
	private:


		/*
		 * class Node contains value, pointer to next element, like implementing ListNode
		 */
		class Node {
		private:
			T_type pvalue;						// value of the current pointer
			std::shared_ptr<Node> next_ptr;		// pointer to next element

		public:

			/*
			 * return the value of current pointer
			 */
			T_type val() { return pvalue; }

			/*
			 * return the reference to the pointer to next element
			 */
			std::shared_ptr<Node> &next() { return next_ptr; }

			Node() : pvalue({0}), next_ptr(nullptr) {
				std::cout << "no argument constructor is called!" << std::endl;
			}

			/*
			 * constructer, initalize Node list node. A message is called to confirm.
			 */
			Node(const T_type &val) : pvalue(val), next_ptr(nullptr) { 
				std::cout << "node " << pvalue << "is created" << std::endl; 
			}

			/*
			 * destructer, when the smarter is deleted, Node is deleted and a message is called to confirm"
			 */
			~Node() { std::cout << "node " << pvalue << "is deleted!" << std::endl; }

			// friend function

			void print_vector(std::vector<int> &p) {
				for (auto x : p)
					std::cout << x << ' ';
				std::cout << std::endl;
			}
		};

		using ptr_val = std::shared_ptr<Node>;			// pointer type of the Node lise

		ptr_val first;					// pointer before the first element, like dummy node
		ptr_val last;						// pointer to the actual last element

		ptr_val find_previous(T_type find_elem);
		bool empty();

	public:

		/*
		 * constructer, initialize first and last pointer 
		 */
		list() : first(std::make_shared<Node>()), last(nullptr) {}

		void push_back(T_type elem);
		void push_front(T_type elem);
		void erase(T_type old_elem);
		void display();
		ptr_val search(T_type target);
		void reverse();
	};

	// class list private function

	/*
	 * private function for refactor search() and erase()
	 * use for check whether the element in the Node list
	 */
	template<typename T_type>
	typename list<T_type>::ptr_val list<T_type>::find_previous(T_type find_elem) {
		if (empty()) {
			std::cout << "List is empty!" << std::endl;
			return nullptr;
		}

		list<T_type>::ptr_val t = first;
		while (t != last && t->next()->val() != find_elem) {
			t = t->next();
		}
		if (t == last) {
			std::cout << "no such element in Node list." << std::endl;
			return ptr_val();
		}
		return t;
	}

	/*
	 * returns true if the Nodelist is empty
	 */
	template<typename T_type>
	bool list<T_type>::empty() {
		if (last == nullptr) {
			return true;
		} else {
			return false;
		}
	}

	// public function

	/*
	 * insert element at the end of Node list
	 */
	template<typename T_type>
	void list<T_type>::push_back(T_type elem) {
		if (empty()) {
			first->next() = std::make_shared<Node>(elem);
			last = first->next();
		} else {
			last->next() = std::make_shared<Node>(elem);
			last = last->next();
		}
	}

	/*
	 * insert element at the front of Node list
	 */
	template<typename T_type>
	void list<T_type>::push_front(T_type elem) {
		if (empty()) {
			first->next() = std::make_shared<Node>(elem);
			last = first->next();
		} else {
			ptr_val t = std::make_shared<Node>(elem);
			t->next() = first->next();
			first->next() = t;
		}
	}

	/*
	 * remove the old element from the list
	 */
	template<typename T_type>
	void list<T_type>::erase(T_type old_elem) {
		list<T_type>::ptr_val t = find_previous(old_elem);
		if (t == nullptr)
			return ;

		ptr_val to_be_removed = t->next();
		t->next() = t->next()->next();
		to_be_removed.reset();

		if (t->next() == nullptr)
			last = t;
		if (first == last)
			last = nullptr;
	}

	/* 
	 * display all the element still in the Node list
	 */
	template<typename T_type>
	void list<T_type>::display() {
		if (empty()) {
			std::cout << "nothing display!" << std::endl;
			return ;
		}

		ptr_val t = first;
		while (t->next() != nullptr) {
			std::cout << t->next()->val() << std::endl;
			t = t->next();
		}
	}

	/*
	 * find whether the element in Node list and return its pointer position 
 	 */
	template<typename T_type>
	typename list<T_type>::ptr_val list<T_type>::search(T_type find_elem) {
		ptr_val find = find_previous(find_elem);
		if (find == nullptr)
			return nullptr;

		if (find->next() != nullptr)
			std::cout << "element " << find->next()->val() << " is found!" << std::endl;
		return find->next();
	}

	/*
 	 * reverse the sequence of Node list, first and last pointer still in function
 	 */
	template<typename T_type>
	void list<T_type>::reverse() {
		if (empty()) {
			std::cout << "List is empty!" << std::endl;
			return ;
		}

		ptr_val head = first->next();
		ptr_val prev = nullptr;
		ptr_val next;

		while (head) {
			next = head->next();
			head->next() = prev;
			prev = head;
			head = next;
		}

		last = first->next();
		first->next() = prev;
	}
} // namespace Node_list