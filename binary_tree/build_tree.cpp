#include <vector>
#include <queue>
#include <iostream>
using namespace std;

/*
         4
       /   \
      2     6  
     / \   / \
    1   3  5  7
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x = 0) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class binary_tree {
private:

    const vector<int> Arr;
    TreeNode* tree_root;

    // function

    // due to the implementation, the sequence of tree will
    // prefectly match with the original array by inorder
    // if the vector passed is in ascending order,
    // it build a binary search tree!
    TreeNode* build_tree(int low, int high) {
        if(low > high) return nullptr;

        int mid = (low + high) / 2;
        TreeNode* pnode = new TreeNode(Arr[mid]);

        pnode->left = build_tree(low, mid - 1);
        pnode->right = build_tree(mid + 1, high);

        return pnode;
    }

public:
 
    TreeNode* root() { return tree_root; };

    binary_tree(vector<int> &a) : Arr(a) {
        tree_root = build_tree(0, Arr.size() - 1);
    }
};


int main() {
    vector<int> A = {1, 2, 3, 4, 5, 6, 7};
    binary_tree tree(A);

    // postorder(tree.root());
   
    return 0;
}


