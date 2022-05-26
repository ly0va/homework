#include <bits/stdc++.h>

using namespace std;

int with_mutex() {
    int value = 0;
    std::mutex value_mutex;

    auto increment = [&](int& x) {
        int i = 1000000;
        while (i--) {
             std::lock_guard<std::mutex> guard(value_mutex);
             ++x;
        }
    };

    std::thread t0(increment, std::ref(value));
    std::thread t1(increment, std::ref(value));

    t0.join();
    t1.join();

    return value;
}

int using_atomics() {
    std::atomic_int value(0);

    auto increment = [](atomic_int& x) {
        int i = 1000000;
        while (i--) x.fetch_add(1);
    };

    std::thread t0(increment, std::ref(value));
    std::thread t1(increment, std::ref(value));

    t0.join();
    t1.join();

    return value.load();
}

int no_protection() {
    int value = 0;

    auto increment = [](int& x) { 
        int i = 1000000;
        while (i--) ++x;
    };

    std::thread t0(increment, std::ref(value));
    std::thread t1(increment, std::ref(value));

    t0.join();
    t1.join();

    return value;
}

int main(int argc, char **argv) {
    clock_t now;
    int result;

    now = clock();
    result = no_protection();
    printf("Incrementing a shared value (no protection) yielded: %d in %.3f sec\n", result, double(clock() - now) / CLOCKS_PER_SEC);

    now = clock();
    result = with_mutex();
    printf("Incrementing a shared value (with mutex)    yielded: %d in %.3f sec\n", result, double(clock() - now) / CLOCKS_PER_SEC);

    now = clock();
    result = using_atomics();
    printf("Incrementing a shared value (using atomics) yielded: %d in %.3f sec\n", result, double(clock() - now) / CLOCKS_PER_SEC);

    return 0;
}

