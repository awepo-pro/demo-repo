#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <vector>
#include <ostream>

namespace data_structures {

// function for user interface 

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
class link_list {
private:

	static size_t *count;

	/*
	 * class Node contains value, pointer to next element, like implementing ListNode
	 */
	class Node {
	private:
		T_type pvalue;							// value of the current pointer
		std::shared_ptr<Node> next_ptr;		// pointer to next element


	public:

		/*
		 * return the value of current pointer
		 */
		T_type &val() { return pvalue; }

		/*
		 * return the reference to the pointer to next element
		 */
		std::shared_ptr<Node> &next() { return next_ptr; }

		/*
		 * copy constructor (default constructor)
		 */
		Node(const T_type &val = 0) : pvalue(val), next_ptr(nullptr) {
			*count += 1;
		}

		Node(const T_type &val, std::shared_ptr<Node> next_node) : pvalue(val), 
														   next_ptr(next_node) {

			std::cout << *count << "th node " << pvalue << " is created! "
					  << "copy constructor with pointer is called!" << std::endl;
			*count += 1;
		}

		/*
		 * destructer, when the smarter is deleted, Node is deleted and a message is called 
		 * to confirm
		 */
		~Node() { 
			*count -= 1;
		}
	};



	std::shared_ptr<Node> find_previous(T_type find_elem);
	void destroy();

	std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> 
		serveral_to_linklist(const std::vector<T_type> &serveral_elem);

	std::shared_ptr<Node> merge(std::shared_ptr<Node> l1, std::shared_ptr<Node> l2);
	std::shared_ptr<Node> sort(std::shared_ptr<Node> head);

public:
	using node_ptr = std::shared_ptr<Node>;			// pointer type of the Node list

	node_ptr first;					// pointer before the first element, like dummy node
	node_ptr last;					// pointer to the actual last element

	/*
	 * constructer, initialize first and last pointer 
	 */
	link_list() : first(std::make_shared<Node>()), last(nullptr) {}

	/*
	 * copy constructor, initializer_list as argument
	 */
	link_list(const std::initializer_list<T_type> &serveral_node) : 
											first(std::make_shared<Node>()), last(nullptr) {

		for (auto t : serveral_node)
			push_back(t);
	}

	/*
	 * copy constructor, vector as argument
	 */
	link_list(const std::vector<T_type> &serveral_node) : first(std::make_shared<Node>()), 
														  last(nullptr) {

		for (auto t : serveral_node)
			push_back(t);
	}

	/*
	 * move constructor, vector as arguemnt
	 */
	link_list(std::vector<T_type> &&serveral_node) noexcept : first(std::make_shared<Node>()), 
															  last(nullptr) {
		for (auto t : serveral_node)
			push_back(t);
	}

	/*
	 * copy constructor, copy another tree by taking that tree as argument
	 * However, size() of nodes are shared in everything tree, which is not my expectation
	 */
	link_list(const link_list<T_type> &base) : first(std::make_shared<Node>()), last(nullptr) {
		node_ptr head = base.first;
		while (head->next() != nullptr) {
			push_back(head->next()->val());
			head = head->next();
		}
	}

	/*
	 * move constructor, get ownship of another tree
	 * that tree's first and last pointer reset
	 */
	link_list(link_list<T_type> &&base) : first(std::make_shared<Node>(0, base.first->next())),
										  last(base.last) {
		base.last.reset();
		base.first->next().reset();
	}

	/* destructor, destroy from first element, not from dummy node */
	~link_list() {
		destroy();
		delete count;
	}

	// time complexity O(1) 
	T_type front_val() { return first->next()->val(); }
	T_type last_val() { return last->val(); }
	size_t size() { return *count; }
	bool empty() const;
	void push_back(T_type elem);

	void push_back_range(const std::vector<T_type> &serveral_elem);
	void push_back_range(std::vector<T_type> &&serveral_elem);
	void push_back_range(const std::initializer_list<T_type> &serveral_elem);
	void push_back_range(typename std::vector<T_type>::iterator first, 
		typename std::vector<T_type>::iterator last);

	void push_front(T_type elem);
	void push_front_range(const std::vector<T_type> &serveral_elem);
	void push_front_range(std::vector<T_type> &&serveral_elem);
	void push_front_range(const std::initializer_list<T_type> &serveral_elem);

	void pop_front();
	void pop_back();

	// time complexity O(n)
	void erase(T_type old_elem);
	void clear();

	void display(const std::string &sentence = "");
	void display(std::string &&sentence);

	node_ptr search(T_type target);
	void reverse();
	void insert(int pos, T_type elem);

	// time complexity O(nlogn) to O(n^2), space complexity O(logn) 
	void sort();		// merge sort
	void unique();		// require sorted list

	// operator function

	void operator=(const link_list<T_type> &b);

	// friend function

	/*
	 * for using template in friend function, necessarily add another template since the 
	 * class link_list template is not inherited in friend function.
	 * However, this method still doesn't work in clang. (only for gcc)
	 *
	 * Or, you can add as prototype before class link_list.
	 * reference: 
	 * https://stackoverflow.com/questions/54501190/templates-linker-error-on-friend-function
	 */
	template<typename A_type>
	friend std::ostream &operator<<(std::ostream &os, const link_list<A_type> &base);
};

template<typename T_type>
size_t *link_list<T_type>::count = new size_t(0);

/*
 * data_structures function
 * convert link list into string for testing program
 */
template<typename T_type>
std::string linklist_to_string(const link_list<T_type> &base) {
	typename link_list<T_type>::node_ptr head = base.first->next();
	std::string ret;

	while (head != base.last) {
		ret += std::to_string(head->val());
		ret += ' ';
		head = head->next();
	}

	ret += std::to_string(head->val());
	return ret;
}

// class link_list private function

/*
 * private function for refactor search() and erase()
 * use for check whether the element in the Node list
 */
template<typename T_type>
typename link_list<T_type>::node_ptr link_list<T_type>::find_previous(T_type find_elem) {
	if (empty()) {
		return nullptr;
	}

	link_list<T_type>::node_ptr t = first;
	while (t != last && t->next()->val() != find_elem) {
		t = t->next();
	}
	if (t == last) {
		return nullptr;
	}
	return t;
}

template<typename T_type>
void link_list<T_type>::destroy() {
	node_ptr t = first->next();
	first->next() = nullptr;
	while (t != last) {
		// std::cout << t->val() << " is removed" << std::endl;
		node_ptr removed = t;
		t = t->next();
		removed->next() = nullptr;

		// std::cout << removed.use_count(s) << std::endl;

		removed.reset();
	}
	last = nullptr;
	t.reset();
	first.reset();
}

/*
 * convert a vector into link list
 * return its pair<first_ptr, last_ptr>
 */
template<typename T_type>
std::pair<typename link_list<T_type>::node_ptr, typename link_list<T_type>::node_ptr> 
link_list<T_type>::serveral_to_linklist(const std::vector<T_type> &serveral_elem) {

	node_ptr head = std::make_shared<Node>(serveral_elem[0]), t = head;

	for (int i = 1; i < serveral_elem.size(); i++) {
		t->next() = std:: make_shared<Node>(serveral_elem[i]);
		t = t->next();
	}

	return std::make_pair(head, t);
}

template<typename T_type>
typename link_list<T_type>::node_ptr link_list<T_type>::merge(node_ptr l1, node_ptr l2) {
	if (l1 == nullptr && l2 == nullptr) return nullptr;
	if (l1 == nullptr) return l2;
	if (l2 == nullptr) return l1;

	node_ptr dummy = std::make_shared<Node>();
	node_ptr cur = dummy;

	while (l1 != nullptr && l2 != nullptr) {
		if (l1->val() < l2->val()) {
			cur->next() = l1;
			l1 = l1->next();
		} else {
			cur->next() = l2;
			l2 = l2->next();
		}
		cur = cur->next();
	}

	if (l1 != nullptr)
		cur->next() = l1;
	else
		cur->next() = l2;
	return dummy->next();
}

/*
 * sinec `first` as argument, first->val() = 0 is also sorted in the function.
 * so first must stay at front, it can only sort ascending order and the number of 
 * elements in link listmust be >= 0
 */
template<typename T_type>
typename link_list<T_type>::node_ptr link_list<T_type>::sort(node_ptr head) {
	if (head == nullptr || head->next() == nullptr) return head;

	node_ptr slow = head;
	node_ptr fast = head->next();

	while (fast != nullptr && fast->next() != nullptr) {
		slow = slow->next();
		fast = fast->next()->next();
	}

	fast = slow->next();
	slow->next() = nullptr;

	return merge(sort(head), sort(fast));
}

// public function

/*
 * returns true if the link list is empty
 */
template<typename T_type>
bool link_list<T_type>::empty() const {
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
template<typename T_type>
void link_list<T_type>::push_back(T_type elem) {
	if (empty()) {
		first->next() = std::make_shared<Node>(elem);
		last = first->next();
	} else {
		last->next() = std::make_shared<Node>(elem);
		last = last->next();
	}
}

/*
 * insert elements (vector as argument) at the end of link list
 */
template<typename T_type>
void link_list<T_type>::push_back_range(const std::vector<T_type> &serveral_elem) {
	if (serveral_elem.empty()) return ;

	int start = 0;
	if (empty()) {
		first->next() = std::make_shared<Node>(serveral_elem[0]);
		last = first->next();
		start = 1;
	} 

	for (int i = start; i < serveral_elem.size(); i++)
		push_back(serveral_elem[i]);
}

/*
 * insert elements (move vector as arguement) at the end of link list
 */
template<typename T_type>
void link_list<T_type>::push_back_range(std::vector<T_type> && serveral_elem) {
	if (serveral_elem.empty()) return ;

	int start = 0;
	if (empty()) {
		first->next() = std::make_shared<Node>(serveral_elem[0]);
		last = first->next();
		start = 1;
	} 

	for (int i = start; i < serveral_elem.size(); i++)
		push_back(serveral_elem[i]);
}

/*
 * insert elements (initializer_list as arguemt) at the end of link list
 */
template<typename T_type>
void link_list<T_type>::push_back_range(const std::initializer_list<T_type> &serveral_elem) {
	std::vector<T_type> store(serveral_elem);
	if (store.empty()) return ;

	int start = 0;
	if (empty()) {
		first->next() = std::make_shared<Node>(store[0]);
		last = first->next();
		start = 1;
	} 

	for (int i = start; i < store.size(); i++)
		push_back(store[i]);
}

template<typename T_type>
void link_list<T_type>::push_back_range(typename std::vector<T_type>::iterator a, 
										typename std::vector<T_type>::iterator b) {
	if (first == last) return ;

	typename std::vector<T_type>::iterator start = a;
	if (empty()) {
		first->next() = std::make_shared<Node>(*start);
		last = first->next();
		start++;
	}

	while (start != b) {
		push_back(*start++);
	} 
}

/*
 * insert element at the front of link list
 */
template<typename T_type>
void link_list<T_type>::push_front(T_type elem) {
	if (empty()) {
		first->next() = std::make_shared<Node>(elem);
		last = first->next();
	} else {
		node_ptr t = std::make_shared<Node>(elem);
		t->next() = first->next();
		first->next() = t;
	}
}

/*
 * insert a branch of elements at the front of link list
 */
template<typename T_type>
void link_list<T_type>::push_front_range(const std::vector<T_type> &serveral_elem) {
	if (serveral_elem.empty()) return ;

	std::pair<node_ptr, node_ptr> ptr = serveral_to_linklist(serveral_elem);

	if (first->next() == nullptr)
		last = ptr.second;

	ptr.second->next() = first->next();
	first->next() = ptr.first;
}

/*
 * insert a branch of elements at the front of link list, take move vector as argument
 */
template<typename T_type>
void link_list<T_type>::push_front_range(std::vector<T_type> &&serveral_elem) {
	if (serveral_elem.empty()) return ;

	std::pair<node_ptr, node_ptr> ptr = serveral_to_linklist(serveral_elem);

	if (first->next() == nullptr)
		last = ptr.second;

	ptr.second->next() = first->next();
	first->next() = ptr.first;
}

/*
 * insert a branch of elements at the front of link list, take initializer_list as argument
 */
template<typename T_type>
void link_list<T_type>::push_front_range(const std::initializer_list<T_type> &serveral_elem) {
	std::vector<int> store(serveral_elem);
	if (store.empty()) return ;

	std::pair<node_ptr, node_ptr> ptr = serveral_to_linklist(store);

	if (first->next() == nullptr)
		last = ptr.second;

	ptr.second->next() = first->next();
	first->next() = ptr.first;
}

/*
 * insert element at user-desired position in the link list
 */
template<typename T_type>
void link_list<T_type>::insert(int pos, T_type elem) {
	if (pos >= size()) {
		push_back(elem);
		return ;
	}

	node_ptr t = first;
	while (pos--) {
		t = t->next();
	}

	/* uses `Node(const T_type &val, std::shared_ptr<Node> next_node) : pvalue(val), 
	 * next_ptr(next_node)`
	 */
	node_ptr to_be_inserted = std::make_shared<Node>(elem, t->next());
	t->next() = to_be_inserted;
}

/* 
 * display all the element still in the Node list
 */
template<typename T_type>
void link_list<T_type>::display(const std::string &sentence) {
	if (empty()) {
		std::cout << "link list is empty!" << std::endl;
		return ;
	}

	node_ptr t = first;
	std::cout << sentence;
	while (t->next() != nullptr) {
		std::cout << t->next()->val() << ' ';
		t = t->next();
	}
	std::cout << '\n';
}

template<typename T_type>
void link_list<T_type>::display(std::string &&sentence) {
	if (empty()) {
		std::cout << "link list is empty!" << std::endl;
		return ;
	}

	node_ptr t = first;
	std::cout << sentence;
	while (t->next() != nullptr) {
		std::cout << t->next()->val() << ' ';
		t = t->next();
	}
	std::cout << '\n';
}

/*
 * find whether the element in Node list and return its pointer position 
 */
template<typename T_type>
typename link_list<T_type>::node_ptr link_list<T_type>::search(T_type find_elem) {
	node_ptr find = find_previous(find_elem);
	if (find == nullptr) {
		return nullptr;
	}

	// find never reach last, so find->next() != nullptr
	return find->next();
}

/*
 * reverse the sequence of Node list, first and last pointer still in function
 */
template<typename T_type>
void link_list<T_type>::reverse() {
	if (empty()) {
		return ;
	}

	node_ptr head = first->next();
	node_ptr prev = nullptr;
	node_ptr next;

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
 * remove the all old element int the link list
 */
template<typename T_type>
void link_list<T_type>::erase(T_type old_elem) {
	link_list<T_type>::node_ptr t = find_previous(old_elem);

	while (t != nullptr) {
		node_ptr to_be_removed = t->next();
		t->next() = t->next()->next();
		if (t->next() == nullptr)
			last = t;
		if (first == last)
			last = nullptr;

		// shared number = 1
		to_be_removed.reset();

		t = find_previous(old_elem);
	}
}

/*
 * remove the element at the head of link list
 */
template<typename T_type>
void link_list<T_type>::pop_front() {
	if (empty()) {
		return ;
	}

	node_ptr to_be_removed = first->next();
	// it means there is only one element
	if (last == to_be_removed)
		last = nullptr;

	first->next() = first->next()->next();

	// resetted pointer is known, so it might not be nullptr
	// ensure shared number = 1
	to_be_removed.reset();
}

/*
 * remove the element at the end of link list
 * not using find_previous(last->val) since there are possibly duplicates
 */
template<typename T_type>
void link_list<T_type>::pop_back() {
	if (empty()) {
		return ;
	}

	node_ptr t = first;
	while (t->next() != last) 
		t = t->next();

	node_ptr to_be_removed = last;
	last = t;

	// very important!!! since shared pointer require shared_number = 0 if 
	// want to reset(), that means next() can't point to to_be_removed!
	// otherwise, destructor won't call. use use_count() to find the shared number
	last->next() = nullptr;
	if (first == last) 
		last = nullptr;

	to_be_removed.reset();
}

/*
 * delete all the nodes except `first` in link list, `last` = nullptr
 */
template<typename T_type>
void link_list<T_type>::clear() {
	if (empty()) return ;

	while (!empty())
		pop_back();
}

/* 
 * sort the link list in ascending order
 */
template<typename T_type>
void link_list<T_type>::sort() {
	sort(first);
}

template<typename T_type>
void link_list<T_type>::unique() {
	if (empty()) return ;

	node_ptr head = first->next();
	while (head && head->next()) {
		while (head->val() == head->next()->val()) {
			node_ptr to_be_removed = head->next();
			head->next() = head->next()->next();
			to_be_removed.reset();
		}
		head = head->next();
	}
}

// operator function

/*
 * assign linked list A to linked list B
 */
template<typename T_type>
void link_list<T_type>::operator=(const link_list<T_type> &b) {
	node_ptr head = b.first;

	while (head->next() != nullptr) {
		push_back(head->next()->val());
		head = head->next();
	}
}

// friend function

/*
 * print linked list in operator<<, act like display()
 */
template<typename A_type>
std::ostream &operator<<(std::ostream &os, const link_list<A_type> &base) {
	if (base.empty()) {
		std::cout << "the link list is empty" << std::endl;
		return os;
	}

	for (typename link_list<A_type>::node_ptr t = base.first->next(); t != nullptr; 
		t = t->next()) {
		os << t->val() << ' ';
	}		
	return os;
}
} // namespace data_structures
