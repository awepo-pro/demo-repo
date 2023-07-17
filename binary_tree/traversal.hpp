void preorder(TreeNode *root) {
    if (!root) return ;

    cout << root->val << ' ';
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode *root) {
    if (!root) return ;

    inorder(root->left);
    cout << root->val << ' ';
    inorder(root->right);
}

void postorder(TreeNode *root) {
    if (!root) return ;

    postorder(root->left);
    postorder(root->right);
    cout << root->val << ' ';
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

