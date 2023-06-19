#include <iostream>
#include <climits>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

template <typename T>
void print(T &a) { for (auto &i : a) { cout << i << ' '; } cout << endl; }

class heap {
private:
    vector<int> Heap;

public:
    heap() {}

    void swim(int pos) {
        while (pos >= 1 && Heap[pos / 2] < Heap[pos]) {
            swap(Heap[pos / 2], Heap[pos]);
            pos /= 2;
        }
    }

    void sink(int pos) {
        while (2 * pos <= Heap.size()) {
            int i = 2 * pos;
            if (i < Heap.size() && Heap[i] < Heap[i + 1])
                i++;
            if (Heap[pos] >= Heap[i])
                break;
            swap(Heap[pos], Heap[i]);
            pos = i;
        }
    }

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

    void print() {
        for (int i = 0; i < Heap.size(); i++)
            cout << Heap[i] << ' ';
        cout << endl;
    }
};


void run_case() {
    heap heap;

    cout << "push: " << endl;
    heap.push(3);
    heap.push(5);
    heap.push(1);
    heap.push(10);
    heap.push(100);

    heap.print();
    cout << endl << "pop:" << endl;

    for (int i = 0; i < heap.size(); i++) {
        heap.pop();
        heap.print();
    }
}

int main() {
    run_case();
    return 0;
}