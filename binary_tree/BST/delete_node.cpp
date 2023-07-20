// 450. Delete Node in a BST

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (root->val > key) 
        root->left = deleteNode(root->left, key);
    else if (root->val < key) 
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            TreeNode *del = root;
            root = root->left ? root->left : root->right;
            delete del;
        } else {
            TreeNode *t = leftmost(root->right);
            root->val = t->val;
            root->right = deleteNode(root->right, t->val);
        }
    }    
    return root;
}

TreeNode *leftmost(TreeNode *root) {
    if (!root || !root->left) return root;
    return leftmost(root->left);
}
