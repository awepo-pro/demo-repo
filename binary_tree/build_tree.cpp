#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class binary_tree {
private:

    const vector<int> Arr;
    TreeNode* tree_root;

    // function

    // due to the implementation, the sequence of tree will
    // prefectly match with the original array by inorder
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
    
    void print_tree_BFS(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);

        while (q.size()) {
            auto t = q.front();
            q.pop();

            cout << t->val << ' ';
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
    }
};

int main() {

    return 0;
}