#include <climits>
#include <vector>
using namespace std;

/*
 * using index to locate each node, even though using the size of the heap has the same effect,
 * the arguments of swim() and sink() should accept the same type. 
 */

template <typename heap_type>
class max_heap {
private:
    vector<heap_type> Heap;

    void sink(int pos) {
        while (2 * pos <= Heap.size()) {
            int i = 2 * pos;

            /*
             * swap the element should be the child who is larger, so that it become the parent
             * of another child if swap()
             */

            if (i < Heap.size() && Heap[i] < Heap[i + 1])
                i++;

            /*
             * the larger children node has been found, so only compare with the largest child 
             * to determine whether swap() or not
             */

            if (Heap[pos] >= Heap[i])
                break;
            swap(Heap[pos], Heap[i]);
            pos = i;
        }
    }

    void swim(int pos) {
        while (pos && Heap[(pos - 1) / 2] < Heap[pos]) {
            swap(Heap[(pos - 1) / 2], Heap[pos]);
            pos = (pos - 1) / 2;
        }
    }

public:
    max_heap() {}

    void push(int val) {
        Heap.push_back(val);
        swim(Heap.size() - 1);
    } 

    void pop() {
        Heap[0] = Heap.back();
        Heap.pop_back();
        sink(0);
    }

    int size() {
        return Heap.size();
    }

    int top() {
        if (Heap.size() == 0)
            return INT_MAX;
        return Heap[0];
    }

    bool empty() {
        if (!Heap.size()) {
            cout << "heap is empty" << endl;
            return true;
        }
        return false;
    }

    // friend function

    friend void print(max_heap &H) {
        for (int i = 0; i < H.Heap.size(); i++)
            cout << H.Heap[i] << ' ';
        cout << endl;
    }
};
