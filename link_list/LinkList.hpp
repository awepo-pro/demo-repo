#include <iostream>
#include <memory>
#include <string>
// #include <initializer_list>

namespace link_list {

	/*
	 * function check if the constent of string represents digit or not
	 */
	bool isDigit(const std::string &s) {
		for (const auto c : s) {
			if (!std::isdigit(c)) {
				return false;
			}
		}
		return true;
	}

	/*
	 * class link contains value, pointer to next element, like implementing ListNode
	 */
	class link {
	private:
		int pvalue;							// value of the current pointer
		std::shared_ptr<link> next_ptr;		// pointer to next element

	public:

		/*
		 * return the value of current pointer
		 */
		int val() { return pvalue; }

		/*
		 * return the reference to the pointer to next element
		 */
		std::shared_ptr<link> &next() { return next_ptr; }

		/*
		 * constructer, initalize link list node
		 */
		explicit link(int val = 0) : pvalue(val), next_ptr(nullptr) {}
	};

	/*
	 * contains the method of link list using `class link` as Node
	 */
	class list {
	private:

		std::shared_ptr<link> first;					// pointer before the first element, like dummy node
		std::shared_ptr<link> last;						// pointer to the actual last element

		std::shared_ptr<link> find_previous(int find_elem);
		bool empty();

	public:

		/*
		 * constructer, initialize first and last pointer 
		 */
		list() : first(std::make_shared<link>()), last(nullptr) {}

		void push_back(int elem);
		void push_front(int elem);
		void erase(int old_elem);
		void display();
		std::shared_ptr<link> search(int target);
		void reverse();
	};

	// private function

	/*
	 * private function for refactor search() and erase()
	 * use for check whether the element in the link list
	 */
	std::shared_ptr<link> list::find_previous(int find_elem) {
		if (empty()) {
			std::cout << "List is empty!" << std::endl;
			return nullptr;
		}

		std::shared_ptr<link> t = first;
		while (t != last && t->next()->val() != find_elem) {
			t = t->next();
		}
		if (t == last) {
			std::cout << "no such element in link list." << std::endl;
			return nullptr;
		}
		return t;
	}

	/*
	 * returns true if the linklist is empty
	 */
	bool list::empty() {
		if (last == nullptr) {
			return true;
		} else {
			return false;
		}
	}

	// public function

	/*
	 * insert element at the end of link list
	 */
	void list::push_back(int elem) {
		if (empty()) {
			first->next() = std::make_shared<link>(elem);
			last = first->next();
		} else {
			last->next() = std::make_shared<link>(elem);
			last = last->next();
		}
	}

	/*
	 * insert element at the front of link list
	 */
	void list::push_front(int elem) {
		if (empty()) {
			first->next() = std::make_shared<link>(elem);
			last = first->next();
		} else {
			std::shared_ptr<link> t = std::make_shared<link>(elem);
			t->next() = first->next();
			first->next() = t;
		}
	}

	/*
	 * remove the old element from the list
	 */
	void list::erase(int old_elem) {
		std::shared_ptr<link> t = find_previous(old_elem);
		if (t == nullptr)
			return ;

		std::shared_ptr<link> to_be_removed = t->next();
		t->next() = t->next()->next();
		to_be_removed.reset();

		if (t->next() == nullptr)
			last = t;
		if (first == last)
			last = nullptr;
	}

	/* 
	 * display all the element still in the link list
	 */
	void list::display() {
		if (empty()) {
			std::cout << "nothing display!" << std::endl;
			return ;
		}

		std::shared_ptr<link> t = first;
		while (t->next() != nullptr) {
			std::cout << t->next()->val() << "\t";
			t = t->next();
		}
	}

	/*
	 * find whether the element in link list and return its pointer position 
 	 */
	std::shared_ptr<link> list::search(int find_elem) {
		std::shared_ptr<link> find = find_previous(find_elem);
		if (find != nullptr)
			return nullptr;

		if (find->next() != nullptr)
			std::cout << "element is found!" << std::endl;
		return find->next();
	}

	/*
 	 * reverse the sequence of link list, first and last pointer still in function
 	 */
	void list::reverse() {
		if (empty()) {
			std::cout << "List is empty!" << std::endl;
			return ;
		}

		std::shared_ptr<link> head = first->next();
		std::shared_ptr<link> prev = nullptr;
		std::shared_ptr<link> next;

		while (head) {
			next = head->next();
			head->next() = prev;
			prev = head;
			head = next;
		}

		last = first->next();
		first->next() = prev;
	}
} // namespace link_list