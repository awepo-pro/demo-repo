/*
 * This is a max heap including following method:
 *      - push()
 *      - pop()
 *      - top()
 *      - size()
 *
 * inspired by book "leetcode c++ version" page 95, mentu-cpp-main/堆（优先队列）/heop(1).cpp in github.
 *
 */

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

template <typename T>
void print(T &a) { for (auto &i : a) { cout << i << ' '; } cout << endl; }

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

    // friend function

    friend void print(max_heap &H) {
        for (int i = 0; i < H.Heap.size(); i++)
            cout << H.Heap[i] << ' ';
        cout << endl;
    }
};

int main() {
    max_heap<int> heap;

    cout << "push: " << endl;
    heap.push(3);
    heap.push(5);
    heap.push(1);
    heap.push(10);
    heap.push(100);
    heap.push(44);
    heap.push(66);
    heap.push(190);

    print(heap);

    cout << endl << "pop:" << endl;
    int N = heap.size();

    // don't directly `for (int i = 0; i < heap.size(); i++)` since heap.size() is changing as well
    for (int i = 0; i < N; i++) {
        heap.pop();

        if (heap.size() == 0) {
            cout << "heap empty" << endl;
            break;
        }

        print(heap);
    }

    return 0;
}