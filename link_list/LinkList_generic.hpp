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
	std::ostream &operator<<(std::ostream &os, const std::vector<T_type> &p) {
		if (p.empty())
			os << "the vector is empty";

		for (const auto x : p)
			os << x << ' ';
		return os;
	}

	/*
	 * overload operator<< use for print queue
	 * since the operation of queue, the container is copied
	 */
	template<typename T_type>
	std::ostream &operator<<(std::ostream &os, std::queue<T_type> q) {
		if (q.empty())
			os << "the queue is empty";

		while (q.size()) {
			auto t = q.top();
			q.pop();
			std::cout << t << ' ';
		}
		return os;
	}

	/* 
	 * overload operator<<, print pair<A, B>. 
	 * A and B can be different type
	 */
	template<typename T, typename S>
	std::ostream &operator<<(std::ostream &os, const std::pair<T, S> &p){
		return os << '(' << p.first << ", " << p.second << ')'; 
	}

	/*
	 * compare each elements between vectors
	 */
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
	 * compare each elements between queue
	 */
	template<typename T_type>
	bool operator!=(std::queue<T_type> a, std::queue<T_type> b) {
		int m = a.size();
		int n = b.size();

		if (m != n)
			return true;

		while (a.size()) {
			auto A = a.top();
			auto B = b.top();

			if (A != B)
				return false;
		}
		return true;
	}

	/*
	 * compare elements between pair<>
	 */
	template<typename A, typename B>
	bool operator!=(const std::pair<A, B> &a, const std::pair<A, B> &b) {
		return (a.first == b.first) && (a.second == b.second);
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
	template<typename T_type, typename T_container = std::vector<T_type>>
	class list {
	private:

		static size_t count;

		/*
		 * class Node contains value, pointer to next element, like implementing ListNode
		 */
		class Node {
		private:
			T_container pvalue;						// value of the current pointer
			std::shared_ptr<Node> next_ptr;		// pointer to next element


		public:

			/*
			 * return the value of current pointer
			 */
			T_container val() { return pvalue; }

			/*
			 * return the reference to the pointer to next element
			 */
			std::shared_ptr<Node> &next() { return next_ptr; }

			/*
			 * default constructor
			 */
			Node() : pvalue({0}), next_ptr(nullptr) {
				if (count == 0)
					std::cout << "no argument constructor is called!" << std::endl;
				else
					std::cout << count << "th node " << pvalue << "is created!" << std::endl;
				count++;
			}

			/*
			 * copy constructer, initalize Node list node. A message is called to confirm.
			 */
			Node(const T_container &val) : pvalue(val), next_ptr(nullptr) { 
				std::cout << "const & constructor is called" << std::endl;
				std::cout << count << "th node " << pvalue << "is created" << std::endl; 
				count++;
			}

			/*
			 * move constructor, move ownship to other pointer with copy
			 */
			Node(T_container &&val) noexcept : pvalue(std::move(val)), next_ptr(nullptr) {
				std::cout << "move constructor is called" << std::endl;
				std::cout << count << "th node " << pvalue << "is created" << std::endl;
				count++;
			}

			Node(const std::initializer_list<T_container> &val) : pvalue(val), next_ptr(nullptr) {
				std::cout << "initializer list constructor is called" << std::endl;
				std::cout << count << "th node " << pvalue << "is created" << std::endl;
				count++;
			}

			/*
			 * destructer, when the smarter is deleted, Node is deleted and a message is called to confirm"
			 */
			~Node() { 
				count--;
				if (count == 0)
					std::cout << "the list's element are all released!" << std::endl;
				else
					std::cout << count << "th node " << pvalue << "is deleted!" << std::endl; 
			}
		};

		using ptr_val = std::shared_ptr<Node>;			// pointer type of the Node lise

		ptr_val first;					// pointer before the first element, like dummy node
		ptr_val last;					// pointer to the actual last element

		ptr_val find_previous(T_container find_elem);

	public:

		/*
		 * constructer, initialize first and last pointer 
		 */
		list() : first(std::make_shared<Node>()), last(nullptr) {}

		/* destructor, doing nth */
		~list() {}

		size_t size() { return count; }

		// time complexity O(1) 
		bool empty();
		void push_back(T_container elem);
		void push_front(T_container elem);
		void pop_front();
		void pop_back();

		// time complexity O(n)
		void erase(T_container old_elem);
		void display();
		ptr_val search(T_container target);
		void reverse();
		void insert(int pos, T_container elem);
	};

	/*
	 * count use to count the number of elements
	 */
	template<typename T_type, typename T_container>
	size_t list<T_type, T_container>::count = 0;

	// class list private function

	/*
	 * private function for refactor search() and erase()
	 * use for check whether the element in the Node list
	 */
	template<typename T_type, typename T_container>
	typename list<T_type, T_container>::ptr_val list<T_type, T_container>::find_previous(T_container find_elem) {
		if (empty()) {
			std::cout << "List is empty!" << std::endl;
			return nullptr;
		}

		list<T_type, T_container>::ptr_val t = first;
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
	template<typename T_type, typename T_container>
	bool list<T_type, T_container>::empty() {
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
	template<typename T_type, typename T_container>
	void list<T_type, T_container>::push_back(T_container elem) {
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
	template<typename T_type, typename T_container>
	void list<T_type, T_container>::push_front(T_container elem) {
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
	template<typename T_type, typename T_container>
	void list<T_type, T_container>::erase(T_container old_elem) {
		list<T_type, T_container>::ptr_val t = find_previous(old_elem);
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
	template<typename T_type, typename T_container>
	void list<T_type, T_container>::display() {
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
	template<typename T_type, typename T_container>
	typename list<T_type, T_container>::ptr_val list<T_type, T_container>::search(T_container find_elem) {
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
	template<typename T_type, typename T_container>
	void list<T_type, T_container>::reverse() {
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

	/*
	 * remove the element at the head of link list
	 */
	template<typename T_type, typename T_container>
	void list<T_type, T_container>::pop_front() {
		if (empty()) {
			std::cout << "List is empty!" << std::endl;
			return ;
		}

		ptr_val to_be_removed = first->next();
		// it means there is only one element
		if (last == to_be_removed)
			last = nullptr;

		first->next() = first->next()->next();

		// resetted pointer is known, so it might not be nullptr
		to_be_removed.reset();
	}

	/*
	 * remove the element at the end of link list
	 * not using find_previous(last->val) since there are possibly duplicates
	 */
	template<typename T_type, typename T_container>
	void list<T_type, T_container>::pop_back() {
		if (empty()) {
			std::cout << "list is empty!" << std::endl;
			return ;
		}

		ptr_val t = first;
		while (t->next() != last) 
			t = t->next();

		ptr_val to_be_removed = last;
		last = t;
		to_be_removed.reset();

		last->next() = nullptr;
	}

	template<typename T_type, typename T_container>
	void list<T_type, T_container>::insert(int pos, T_container elem) {
		std::cout << "normal insert is called" << std::endl;	
		if (pos >= size()) {
			push_back(elem);
			return ;
		}

		ptr_val t = first;
		while (pos--) {
			t = t->next();
		}

		t->next() = std::make_shared<Node>(elem);
		last = t->next();
		std::cout << "last: " << last->val() << std::endl;
	}
} // namespace Node_list