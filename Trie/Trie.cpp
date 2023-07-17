class Trie {
private:

    struct Node {
        Node *childNode[26];
        bool isVal;

        Node() : isVal(false) {
            for (int i = 0; i < 26; i++)
                childNode[i] = nullptr;
        }
    };

    Node *root;

public:

    Trie() : root(new Node()) {}

    void insert(string word) {
        Node *temp = root;
        for (const char c : word) {
            if (!temp->childNode[c - 'a'])
                temp->childNode[c - 'a'] = new Node();
            temp = temp->childNode[c - 'a'];
        }
        temp->isVal = true;
    }

    bool search(string word) {
        Node *temp = root;
        for (const char c : word) {
            if (!temp) break;

            temp = temp->childNode[c - 'a'];
        }
        return temp ? temp->isVal : false;
    }

    bool with_prefix(string prefix) {
        Node *temp = root;
        for (const char c : prefix) {
            if (!temp) break;

            temp = temp->childNode[c - 'a'];
        }
        return temp;
    }
};