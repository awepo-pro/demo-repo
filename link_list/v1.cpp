// Link List initialization and reverse operation

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// template<typename T>
class LinkList {
private:

    // strcuture
    
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode() : val(0), next(nullptr) {}
    };    
    
    
    ListNode *dummy = new ListNode;
    ListNode *back_ptr = dummy;     // use for push_back(), instead of loop over the link list each time
    
    bool reverse_flag = false;
    int count = 0;
    
    // function
    
    void destroy() {
        ListNode *head;
        if (!reverse_flag) {
            head = dummy->next;
        } else {
            head = back_ptr;
        }
        
        while (head) {
            cout << head->val << " has destroyed!" << endl;
            ListNode *tmp = head;
            head = head->next;
            delete(tmp);
        }
        back_ptr = dummy;
        cout << "all node has destoryed, except dummy node!!!" << endl;
    }
    
public:
    LinkList() {}
    
    ~LinkList() { destroy(); }
    
    void push_back(int val) {
        ListNode *pnode = new ListNode(val);
        back_ptr->next = pnode;
        
        cout << back_ptr->val << " has created!" << endl;
        
        back_ptr = back_ptr->next;
        count++;
    }
    
    void push_front(int val) {
        ListNode *pnode = new ListNode(val);
        pnode->next = dummy->next;
        dummy->next = pnode;
        cout << dummy->next->val << " has created!" << endl;
        count++;
    }
    
    void print_list() {
        ListNode *head = !reverse_flag ? dummy->next : back_ptr;
        
        cout << "tree: ";
        
        while (head) {
            cout << head->val << ' ';
            head = head->next;
        }
        cout << endl;
    }    
    
    // due to the push(), back_ptr always points to the end of linklist with value, not nullptr
    ListNode* reverse() {
        ListNode *head = !reverse_flag ? dummy->next : back_ptr;
    
        ListNode *prev = nullptr;
        while (head) {
            ListNode *next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        
        reverse_flag = reverse_flag ? false : true;
        return prev;
    }
    
    void insert(int pos, int val) {
        ListNode *head = dummy->next;
        while (--pos && head->next) {
            head = head->next;
        }
        ListNode *pnode = new ListNode(val);
        pnode->next = head->next;
        head->next = pnode;
        cout << head->next->val << " has created!" << endl;
    }
    
    bool pop_back() {
        ListNode *head = dummy->next;
        while (head->next && head->next->next) {
            head = head->next;
        }
        head->
        delete(back_ptr);
        
    }
    
    int size() {
        return count;
    }
    
    bool empty() {
        return count != 0;
    }
};

//ListNode *reverse_recursive(ListNode *head, ListNode *prev = nullptr) {
//    if (!head) {
//        return prev;
//    }
//    
//    ListNode *next = head->next;
//    head->next = prev;
//    return reverse_recursive(next, head);
// }

int main() {
    LinkList L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(10);
    
    L.insert(1, 12);
    L.insert(10, 100);
    L.print_list();
    
    return 0;
}

/*
int main() {
    ListNode *dummy = new ListNode;
    init(dummy);
    
    cout << "original list: ";
    print_list(dummy->next);
    
    cout << "reverse list: ";
    ListNode *back_dummy = new ListNode;
    back_dummy->next = reverse(dummy->next);
    print_list(back_dummy->next);
    
    cout << "reverse recursively: ";
    reverse_recursive(back_dummy->next);
    print_list(dummy->next);
    
    destroy(dummy->next);
    cout << "all ListNode Have destroyed! except dummy point." << endl;
    return 0;
}
*/
