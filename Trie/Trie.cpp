/* 
 * also known as prefix tree
 */
class Trie {
private:
    struct Node {
        vector<Node *> child;
        bool isVal;

        Node() : isVal(false), child(26, nullptr) {}
    };

    Node *root;
public:
    Trie() : root(new Node()) { }
    
    void insert(string word) {
        Node *temp = root;
        for (const char c : word) {
            if (!temp->child[c - 'a'])
                temp->child[c - 'a'] = new Node();
            temp = temp->child[c - 'a'];
        }    
        temp->isVal = true;
    }
    
    bool search(string word) {
        Node *temp = root;
        for (const char c : word) {
            if (!temp->child[c - 'a'])
                return false;
            temp = temp->child[c - 'a'];
        }
        return temp->isVal;
    }
    
    bool startsWith(string prefix) {
        Node *temp = root;
        for (const char c : prefix) {
            if (!temp->child[c - 'a'])
                return false;
            temp = temp->child[c - 'a'];
        }
        return true;
    }
};
