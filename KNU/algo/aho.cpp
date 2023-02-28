#include <bits/stdc++.h>
 
using namespace std;
 
struct node {
    static node* root;

    bool term;
    char letter;
    node* parent;
    node* _suffref;
    std::optional<node*> _output;
    map<char, node*> adj, _next;

    node(char letter = 0, node* parent = nullptr): 
        term(false), letter(letter), parent(parent), 
        _suffref(nullptr), _output(std::nullopt) {}

    void add(const string& s) {
        node* ptr = this;
        for (char c: s) {
            if (!ptr->adj.count(c))
                ptr->adj[c] = new node(c, ptr);
            ptr = ptr->adj[c];
        }
        ptr->term = true;
    }
 
    node* next(char c) {
        if (_next.count(c))
            return _next[c];
        if (adj.count(c))
            return _next[c] = adj[c];
        if (this == root)
            return _next[c] = root;
        return _next[c] = suffref()->next(c);
    }

    node* suffref() {
        if (_suffref != nullptr)
            return _suffref;
        if (this == root || parent == root)
            return _suffref = root;
        return _suffref = parent->suffref()->next(letter);
    }

    node* output() {
        if (_output != std::nullopt)
            return _output.value();
        node* suff = suffref();
        if (suff->term)
            return (_output = suff).value();
        if (suff == root)
            return nullptr;
        return (_output = suff->output()).value();
    }

    string get_word() {
        string res;
        node* ptr = this;
        while (ptr != root) {
            res += ptr->letter;
            ptr = ptr->parent;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
 
node* node::root = new node;

int main() {

    int n;
    cin >> n;
    string s;

    for (int i = 0; i < n; i++) {
        cin >> s;
        node::root->add(s);
    }

    cin >> s;
    node* ptr = node::root;
    for (char c: s) {
        ptr = ptr->next(c);
        node* out = ptr;
        while (out != nullptr) {
            if (out->term)
                cout << "Found " << out->get_word() << endl;
            out = out->output();
        }
    }

    return 0;
}
