/*
 * This is a max heap including following method:
 *      - push()
 *      - pop()
 *      - top()
 *      - size()
 *      - empty()
 *
 * inspired by book "leetcode c++ version" page 95, mentu-cpp-main/堆（优先队列）/heop(1).cpp in github.
 *
 */

#include <iostream>
#include "heap.hpp"

template <typename T>
void print(T &a) { for (auto &i : a) { cout << i << ' '; } cout << endl; }

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

        if (heap.empty()) {
            break;
        }

        print(heap);
    }

    return 0;
}