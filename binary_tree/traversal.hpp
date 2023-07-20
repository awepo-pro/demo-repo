#include <queue>
#include <stack>

void preorder(TreeNode *root) {
    if (!root) return ;

    cout << root->val << ' ';
    preorder(root->left);
    preorder(root->right);
}

void preorder(TreeNode *root) {
    if (!root) return;

    stack<TreeNode *> s;
    s.push(root);

    while (s.size()) {
        auto cur = s.top();
        s.pop();
        cout << cur->val << ' ';

        if (cur->right)
            s.push(cur->right);
        if (cur->left)
            s.push(cur->left);
    }
}

// further optimized
void preorder(TreeNode *root) {
    if (!root) return ;

    stack<TreeNode *> s;
    TreeNode *cur = root;

    // since root->left is printed, so only need to record root->right
    while (cur || s.size()) {
        // can't use while, since if `cur->right = nullptr`, nth (not even nullptr) push into stack
        // which cur = s.top() and s.pop() will be errors. ie: right tree right->right
        if (cur) {
            cout << cur->val << ' ';
            if (cur->right)
                s.push(cur->right);
            cur = cur->left;
        } else {
            cur = s.top();
            s.pop();
        }    
    }
}

void inorder(TreeNode *root) {
    if (!root) return ;

    inorder(root->left);
    cout << root->val << ' ';
    inorder(root->right);
}

void inorder(TreeNode *root) {
    stack<TreeNode *> s;
    TreeNode *cur = root;

    while (s.size() || cur) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        cout << cur->val << ' ';
        cur = cur->right;
    }
}

void postorder(TreeNode *root) {
    if (!root) return ;

    postorder(root->left);
    postorder(root->right);
    cout << root->val << ' ';
}

void postorder(TreeNode *root) {
    if (!root) return ;

    stack<TreeNode *> s;
    TreeNode *prev = nullptr;

    while (root || s.size()) {
        if (root) {
            s.push(root);
            root = root->left;
        } else {
            TreeNode *cur = s.top();
            // prevent infinite loops, when right node return to parent, 
            // stop go to right node again
            if (cur->right && cur->right != prev)
                root = cur->right;
            else {
                cout << cur->val << ' ';
                prev = cur;
                s.pop();
            }
        }
    }
}

void BFS(TreeNode *root) {
    if (!root) return ;

    queue<TreeNode *> q;
    q.push(root);

    while (q.size()) {
        auto t = q.front();
        q.pop();

        cout << t->val << ' ';

        if (t->left)
            q.push(t->left);
        if (t->right)
            q.push(t->right);
    }
}

