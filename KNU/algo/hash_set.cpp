#include <bits/stdc++.h>

struct node {
    int value;
    node *next;
};

struct linked_list {
    int size = 0;
    node *head = nullptr;

    void push_back(int value) {
        head = new node { value, head };
        size++;
    }

    ~linked_list() {
        while (head) {
            node *next = head->next;
            delete head;
            head = next;
        }
    }
};

struct hash_set {
    int capacity;
    linked_list *buckets;

    hash_set(int capacity) {
        this->capacity = capacity;
        buckets = new linked_list[capacity];
    }

    void insert(int value) {
        int index = value % capacity;
        buckets[index].push_back(value);
    }

    int shortest_list() {
        int min = INT_MAX;
        for (int i = 0; i < capacity; i++) {
            if (buckets[i].size < min) {
                min = buckets[i].size;
            }
        }
        return min;
    }

    int longest_list() {
        int max = INT_MIN;
        for (int i = 0; i < capacity; i++) {
            if (buckets[i].size > max) {
                max = buckets[i].size;
            }
        }
        return max;
    }

    ~hash_set() {
        delete[] buckets;
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int now = clock();

    int N = std::stoi(argv[1]);
    hash_set set(N / 100);
    srand(time(0));

    for (int i = 0; i < N; i++) {
        int x = rand();
        set.insert(x);
    }

    int microsecs = 1000000 * (clock() - now) / CLOCKS_PER_SEC;

    printf("tested with %d insertions\n", N);
    printf("shortest list: %d\n", set.shortest_list());
    printf("longest list: %d\n", set.longest_list());
    printf("done in %d microseconds\n", microsecs);

    return 0;
}

