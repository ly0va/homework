#include <bits/stdc++.h>

template <typename T>
struct node {
    T value;
    node *next;
};

template <typename T>
struct linked_list {
    int size = 0;
    node<T> *head = nullptr;

    void push_back(T value) {
        if (find(value)) return;
        head = new node<T> { value, head };
        size++;
    }

    ~linked_list() {
        while (head) {
            node<T> *next = head->next;
            delete head;
            head = next;
        }
    }

    bool find(T value) {
        for (node<T> *cur = head; cur; cur = cur->next) {
            if (cur->value == value) {
                return true;
            }
        }
        return false;
    }

    void remove(T value) {
        node<T> *prev = nullptr;
        for (node<T> *cur = head; cur; cur = cur->next) {
            if (cur->value == value) {
                if (prev) {
                    prev->next = cur->next;
                } else {
                    head = cur->next;
                }
                delete cur;
                size--;
                return;
            }
            prev = cur;
        }
    }
};

struct hashed_string {
    std::string str;
    long fwd_hash;
    long bck_hash;

    hashed_string(std::string str): str(str) {
        fwd_hash = 0;
        bck_hash = 0;
        for (int i = 0; i < str.size(); i++) {
            fwd_hash = (fwd_hash * 37 + str[i]) % 1000000007;
            bck_hash = (bck_hash * 37 + str[str.size() - i - 1]) % 1000000007;
        }
    }

    bool is_palindrome() const {
        return fwd_hash == bck_hash;
    }

    bool operator==(const hashed_string &other) const {
        return str == other.str;
    }
};

struct string_set {
    int capacity;
    linked_list<hashed_string> *buckets;

    string_set(int capacity) {
        this->capacity = capacity;
        buckets = new linked_list<hashed_string>[capacity];
    }

    void insert(std::string value) {
        hashed_string hashed(value);
        int index = hashed.fwd_hash % capacity;
        buckets[index].push_back(hashed);
    }

    bool find(std::string value) {
        hashed_string hashed(value);
        int index = hashed.fwd_hash % capacity;
        return buckets[index].find(hashed);
    }

    void remove(std::string value) {
        hashed_string hashed(value);
        int index = hashed.fwd_hash % capacity;
        buckets[index].remove(hashed);
    }

    void print_palindromes() {
        for (int i = 0; i < capacity; i++) {
            for (auto *node = buckets[i].head; node; node = node->next) {
                if (node->value.is_palindrome()) {
                    std::cout << node->value.str << std::endl;
                }
            }
        }
    }

    ~string_set() {
        delete[] buckets;
    }
};

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    const int N = 1000000;
    
    char op;
    std::string str;
    string_set set(N);

    while (std::cin >> op >> str) {
        switch (op) {
            case '+':
                set.insert(str);
                break;
            case '-':
                set.remove(str);
                break;
            case '?':
                std::cout << (set.find(str) ? "YES\n" : "NO\n");
                break;
            case '#':
                break;
        }
    }

    std::cout << "--Palindromes--\n";
    set.print_palindromes();

    return 0;
}

