#include <iostream>
#include <cstring>
#include <stdio.h>
#include <chrono>

template <class T>
void print(const T &x, char sep = '\n') {
    std::cout << x << sep;
    fflush(stdout);
}

template <class T>
void log(T x, char sep = '\n') {
    #ifdef LOG
    print(x, sep);
    #endif
}

class Measure {
    std::chrono::time_point<std::chrono::steady_clock> start;
    const char *msg;
public:
    Measure(const char *msg) : msg(msg) {
        print(msg, ' ');
        print("start");
        start = std::chrono::steady_clock::now();
    }
    ~Measure() {
        print(msg, ' ');
        print("end, time:", ' ');
        print(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count());
    }
};