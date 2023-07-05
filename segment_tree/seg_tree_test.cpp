/*
 * v = vertex(always start from 1, not 0), 
 * although tl = tree left boundary, tr = tree right boundary and tree.size() == 4 * array.size(), tl = 0 and tr = array.size() - 1
 * [tl ... tr] => [0 ... tree.size() * 4 - 1]
 * l = range left boundary, r = range right boundary (user defined)
 */

#include <iostream>
#include <climits>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

template<typename A, typename B, typename C> ostream &operator<<(ostream &os, const tuple<A, B, C> &p) { auto &[a, b, c] = p; return os << '(' << a << ", " << b << ", " << c << ')'; }
template<typename A, typename B> ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &con) { for (auto &it : con) { cout << it << ' '; } return os; };

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }


struct seg_tree {
    int N, _tl, _tr; 
    const int vertex = 1;
    vector<int> array;
    vector<int> tree;

    seg_tree(vector<int> &A) : N(4 * A.size()), array(A), tree(N, INT_MAX), _tl(0), _tr(A.size() - 1) {
        build(vertex, _tl, _tr);
    }

    void print_tree(string s = "tree: ") {
        cout << s << ": ";
        for (int i = 1; i < N; i++) {
            if (tree[i] == INT_MAX)
                break;
            cout << tree[i] << ' ';
        }
        cout << endl;
    }

    // this method use concept of divide and conquer
    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = array[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            tree[v] = tree[v*2] + tree[v*2+1];
        }
    }

    inline int _query(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return 0;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return _query(v*2, tl, tm, l, min(r, tm))
               + _query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    int query(int l, int r) {
        return _query(1, _tl, _tr, l, r);
    }


    inline void _update_tree(int pos, int new_val, int tl, int tr, int v) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                _update_tree(pos, new_val, tl, tm, v * 2);
            else
                _update_tree(pos, new_val, tm+1, tr, v * 2 + 1);
            tree[v] = tree[v*2] + tree[v*2+1];
        }
    }

    void update_array(int pos, int new_val) {
        assert(pos < N);

        array[pos] = new_val;

        _update_tree(pos, new_val, _tl, _tr, vertex);
    }
};

/*
 * built tree inside initialization
 *
 * method:
 * print_tree(string s = "tree: ")
 * query(left, right)
 * update_array(position, new value)
 */

int main() {
    ifstream in("testcase.txt");
    if (!in) {
        cerr << "Can't open";
    }

    int N;
    vector<int> A;
    string number, array;

    while (getline(in, number)) {
        N = stoi(number);

        getline(in, array);
        istringstream word(array);

        int b;
        for (int i = 0; i < N; i++) {
            word >> b;
            A.push_back(b);
        }
    }

    seg_tree my_first_tree(A);                         // convert array to segment tree
    cout << "N: " << N << endl;
    cout << "array: " << my_first_tree.array << endl;

    my_first_tree.print_tree();

    cout << "sum: " 
         << my_first_tree.query(0, 3) << endl;

    my_first_tree.update_array(2, 3);
    cout << "new array: " << my_first_tree.array << endl;
    my_first_tree.print_tree("new_tree");

    return 0;
}